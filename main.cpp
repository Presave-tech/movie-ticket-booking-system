#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include "10_PaymentTypes.cpp"
#include "13_BookingService.cpp"

// Course: B.Tech CSE | Semester: 5 | Subject: System Design (TCS-504)
// Assignment 1: Movie Ticket Booking System
// File: main.cpp (Console Menu and Flow Orchestration)

void printMainMenu() {
    std::cout << "\n===== MOVIE TICKET BOOKING =====\n";
    std::cout << "1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit\n";
    std::cout << "Choose: ";
}

std::vector<std::string> parseSeatList(const std::string& input) {
    std::vector<std::string> seats;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, ',')) {
        size_t start = item.find_first_not_of(" \t\r\n");
        size_t end = item.find_last_not_of(" \t\r\n");
        if (start != std::string::npos && end != std::string::npos) {
            seats.push_back(item.substr(start, end - start + 1));
        }
    }
    return seats;
}

void handleListMovies(BookingService& service) {
    const std::vector<Movie>& movies = service.getMovies();
    std::cout << "\n";
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " 
                  << movies[i].getTitle() << "\t" 
                  << movies[i].getLanguage() << "\t" 
                  << movies[i].getDurationMinutes() << " min\n";
    }
}

void handleBookingFlow(BookingService& service, Customer& customer) {
    handleListMovies(service);
    const std::vector<Movie>& movies = service.getMovies();

    std::cout << "\nChoose movie: ";
    int movieChoice = 0;
    if (!(std::cin >> movieChoice) || movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid movie choice.\n";
        return;
    }

    std::vector<Show*> shows = service.getShowsForMovie(movieChoice - 1);
    if (shows.empty()) {
        std::cout << "No shows available for this movie.\n";
        return;
    }

    for (size_t i = 0; i < shows.size(); ++i) {
        std::cout << "[" << (i + 1) << "] " 
                  << shows[i]->getScreen()->getScreenName() << "  " 
                  << shows[i]->getStartTime() << "\n";
    }

    std::cout << "Choose show: ";
    int showChoice = 0;
    if (!(std::cin >> showChoice) || showChoice < 1 || showChoice > static_cast<int>(shows.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid show choice.\n";
        return;
    }

    Show* selectedShow = shows[showChoice - 1];
    selectedShow->displaySeatLayout();

    std::cout << "Seats (e.g. A1,B2): ";
    std::string seatInput;
    if (!(std::cin >> seatInput)) {
        return;
    }
    std::vector<std::string> seatCodes = parseSeatList(seatInput);

    if (seatCodes.empty()) {
        std::cout << "Error: No seat numbers entered.\n";
        return;
    }

    std::vector<ShowSeat*> selectedSeats;
    double totalAmount = 0.0;
    bool seatsValid = service.validateAndCalculatePrice(selectedShow, seatCodes, selectedSeats, totalAmount);
    if (!seatsValid) {
        return;
    }

    std::cout << "\nPay by: 1.UPI  2.Card  3.Cash  4.Simulate Failure > ";
    int paymentChoice = 0;
    if (!(std::cin >> paymentChoice) || paymentChoice < 1 || paymentChoice > 4) {
        if (std::cin.eof()) return;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid payment choice. Booking aborted.\n";
        return;
    }

    // OOP Concept: Abstraction & Runtime Polymorphism via base pointer Payment*
    Payment* paymentMethod = nullptr;
    UpiPayment upi;
    CardPayment card;
    CashPayment cash;
    FailedPayment failedPayment;

    if (paymentChoice == 1) paymentMethod = &upi;
    else if (paymentChoice == 2) paymentMethod = &card;
    else if (paymentChoice == 3) paymentMethod = &cash;
    else paymentMethod = &failedPayment;

    service.confirmBookingWithPayment(customer, selectedShow, selectedSeats, totalAmount, paymentMethod);
}

void handleCancellation(BookingService& service) {
    std::cout << "Enter Booking ID to cancel (e.g. BK1001): ";
    std::string bookingId;
    if (std::cin >> bookingId) {
        service.cancelBooking(bookingId);
    }
}

int main() {
    BookingService bookingService;
    Customer currentCustomer("Kaushal", "9876543210");

    int choice = -1;
    while (choice != 0) {
        printMainMenu();
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) {
                break;
            }
            // Edge Case 4: Invalid input handling without crashing
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice! Please enter a number from the menu.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handleListMovies(bookingService);
                break;
            case 2:
                handleBookingFlow(bookingService, currentCustomer);
                break;
            case 3:
                handleCancellation(bookingService);
                break;
            case 4:
                bookingService.displayAllBookings();
                break;
            case 0:
                std::cout << "Thank you for using Movie Ticket Booking System!\n";
                break;
            default:
                std::cout << "Invalid menu option. Please try again.\n";
                break;
        }
    }

    return 0;
}
