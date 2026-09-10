#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "08_Booking.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: TicketPrinter
// Responsibility: Format and print a booking ticket - printing only (SRP).

class TicketPrinter {
public:
    void printTicket(const Booking& booking) const {
        std::cout << "\n================ TICKET ================\n";
        std::cout << "Booking ID : " << booking.getBookingId() << "\n";
        
        if (booking.getShow() != nullptr && booking.getShow()->getMovie() != nullptr) {
            std::cout << "Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
            std::cout << "Screen     : " << booking.getShow()->getScreen()->getScreenName() 
                      << "  " << booking.getShow()->getStartTime() << "\n";
        }
        
        std::cout << "Seats      : ";
        const std::vector<ShowSeat*>& seats = booking.getBookedSeats();
        for (size_t i = 0; i < seats.size(); ++i) {
            std::cout << seats[i]->getSeatNumber();
            if (i + 1 < seats.size()) {
                std::cout << ", ";
            }
        }
        std::cout << "\n";
        
        std::cout << "Amount     : Rs." << static_cast<int>(booking.getTotalAmount()) 
                  << "    Status: " << booking.getStatus() << "\n";
        std::cout << "========================================\n\n";
    }
};
