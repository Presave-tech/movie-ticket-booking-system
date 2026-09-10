#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "01_Movie.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: BookingService
// Responsibility: The orchestrator - runs the booking flow end to end.

class BookingService {
private:
    Cinema cinema;
    std::vector<Movie> movies;
    std::vector<Show> shows;
    std::vector<Booking> bookings;
    PriceCalculator priceCalculator;
    TicketPrinter ticketPrinter;

    void initializeCinemaAndScreens() {
        cinema = Cinema("PVR Cinemas");

        Screen screen1(1, "Screen-1");
        // Row A: SILVER
        screen1.addSeat(Seat("A1", SeatType::SILVER));
        screen1.addSeat(Seat("A2", SeatType::SILVER));
        screen1.addSeat(Seat("A3", SeatType::SILVER));
        screen1.addSeat(Seat("A4", SeatType::SILVER));
        // Row B: GOLD
        screen1.addSeat(Seat("B1", SeatType::GOLD));
        screen1.addSeat(Seat("B2", SeatType::GOLD));
        screen1.addSeat(Seat("B3", SeatType::GOLD));
        // Row C: PLATINUM
        screen1.addSeat(Seat("C1", SeatType::PLATINUM));
        screen1.addSeat(Seat("C2", SeatType::PLATINUM));

        Screen screen2(2, "Screen-2");
        screen2.addSeat(Seat("A1", SeatType::SILVER));
        screen2.addSeat(Seat("A2", SeatType::SILVER));
        screen2.addSeat(Seat("B1", SeatType::GOLD));
        screen2.addSeat(Seat("B2", SeatType::GOLD));
        screen2.addSeat(Seat("C1", SeatType::PLATINUM));

        cinema.addScreen(screen1);
        cinema.addScreen(screen2);
    }

    void initializeMoviesAndShows() {
        movies.push_back(Movie("3 Idiots", "Hindi", 170));
        movies.push_back(Movie("Interstellar", "English", 169));

        Screen* s1 = cinema.getScreen(1);
        Screen* s2 = cinema.getScreen(2);

        shows.push_back(Show(1, &movies[0], s1, "06:00 PM"));
        shows.push_back(Show(2, &movies[0], s2, "09:00 PM"));
        shows.push_back(Show(3, &movies[1], s1, "01:30 PM"));
        shows.push_back(Show(4, &movies[1], s2, "05:00 PM"));

        // Demo seed: Pre-book A2 and B3 in Show 1 as shown in demo diagram
        ShowSeat* a2 = shows[0].getShowSeat("A2");
        if (a2) a2->bookSeat();
        ShowSeat* b3 = shows[0].getShowSeat("B3");
        if (b3) b3->bookSeat();
    }

public:
    BookingService() {
        initializeCinemaAndScreens();
        initializeMoviesAndShows();
    }

    const std::vector<Movie>& getMovies() const {
        return this->movies;
    }

    std::vector<Show*> getShowsForMovie(int movieIndex) {
        std::vector<Show*> result;
        if (movieIndex < 0 || movieIndex >= static_cast<int>(movies.size())) {
            return result;
        }
        for (size_t i = 0; i < shows.size(); ++i) {
            if (shows[i].getMovie()->getTitle() == movies[movieIndex].getTitle()) {
                result.push_back(&shows[i]);
            }
        }
        return result;
    }

    // Helper: validate requested seat strings, display breakdown and total price
    bool validateAndCalculatePrice(Show* show, const std::vector<std::string>& seatCodes, 
                                   std::vector<ShowSeat*>& selectedSeats, double& totalAmount) {
        selectedSeats.clear();
        totalAmount = 0.0;
        
        for (size_t i = 0; i < seatCodes.size(); ++i) {
            ShowSeat* seat = show->getShowSeat(seatCodes[i]);
            if (seat == nullptr) {
                std::cout << "Error: Seat " << seatCodes[i] << " does not exist.\n";
                std::cout << "Booking rejected. No seats were changed.\n";
                return false;
            }
            // Edge Case 1: Booking an already booked seat
            if (!seat->isAvailable()) {
                std::cout << "Error: Seat " << seatCodes[i] << " is already BOOKED.\n";
                std::cout << "Booking rejected. No seats were changed.\n";
                return false;
            }
            selectedSeats.push_back(seat);
        }

        // Display pricing breakdown
        std::cout << "\n";
        for (size_t i = 0; i < selectedSeats.size(); ++i) {
            double price = priceCalculator.getSeatPrice(selectedSeats[i]->getSeatType());
            std::cout << selectedSeats[i]->getSeatNumber() << " " 
                      << selectedSeats[i]->getSeatTypeString() << " Rs." 
                      << static_cast<int>(price) << "\n";
        }
        totalAmount = priceCalculator.calculateTotal(selectedSeats);
        std::cout << "TOTAL     Rs." << static_cast<int>(totalAmount) << "\n";
        return true;
    }

    // OOP Concept: Association - Customer interacts with BookingService
    bool confirmBookingWithPayment(Customer& customer, Show* show, 
                                  const std::vector<ShowSeat*>& selectedSeats, 
                                  double totalAmount, Payment* payment) {
        if (show == nullptr || payment == nullptr || selectedSeats.empty()) {
            std::cout << "Error: Invalid booking parameters.\n";
            return false;
        }

        // OOP Concept: Runtime Polymorphism - invoking payment through Payment* base pointer
        bool paymentSuccessful = payment->pay(totalAmount);

        // Edge Case 2: Failed payment
        if (!paymentSuccessful) {
            std::cout << "Payment failed! Booking NOT confirmed. Seats remain available.\n";
            return false;
        }

        // Lock/Book all seats after successful payment
        for (size_t i = 0; i < selectedSeats.size(); ++i) {
            selectedSeats[i]->bookSeat();
        }

        Booking newBooking(&customer, show, selectedSeats, totalAmount);
        bookings.push_back(newBooking);
        ticketPrinter.printTicket(newBooking);
        return true;
    }

    // Edge Case 3: Cancelling a booking releases seats to AVAILABLE
    bool cancelBooking(const std::string& bookingId) {
        for (size_t i = 0; i < bookings.size(); ++i) {
            if (bookings[i].getBookingId() == bookingId) {
                if (bookings[i].getStatus() == "CANCELLED") {
                    std::cout << "Booking " << bookingId << " is already cancelled.\n";
                    return false;
                }
                const std::vector<ShowSeat*>& seats = bookings[i].getBookedSeats();
                for (size_t j = 0; j < seats.size(); ++j) {
                    if (seats[j] != nullptr) {
                        seats[j]->cancelSeat();
                    }
                }
                bookings[i].cancelBooking();
                std::cout << "Booking " << bookingId << " cancelled successfully! Seats are now AVAILABLE.\n";
                return true;
            }
        }
        std::cout << "Error: Booking ID " << bookingId << " not found.\n";
        return false;
    }

    void displayAllBookings() const {
        if (bookings.empty()) {
            std::cout << "No bookings found.\n";
            return;
        }
        for (size_t i = 0; i < bookings.size(); ++i) {
            ticketPrinter.printTicket(bookings[i]);
        }
    }
};
