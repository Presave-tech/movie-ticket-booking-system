#pragma once
#include <string>
#include <vector>
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Booking
// Responsibility: Holds booking details (booking id, which show, which seats, total amount, status).

class Booking {
private:
    // OOP Concept: Static Members - shared across all objects to generate unique IDs
    inline static int nextBookingNumber = 1001;

    std::string bookingId;
    // OOP Concept: Aggregation - Booking refers to Customer
    Customer* customer;
    // OOP Concept: Aggregation - Booking refers to a Show (does not own the Show's lifetime)
    Show* show;
    // OOP Concept: Aggregation - Booking references ShowSeats
    std::vector<ShowSeat*> bookedSeats;
    // OOP Concept: Encapsulation - totalAmount and status are private
    double totalAmount;
    std::string status; // "CONFIRMED", "CANCELLED", "FAILED"

public:
    Booking() {
        this->bookingId = "";
        this->customer = nullptr;
        this->show = nullptr;
        this->totalAmount = 0.0;
        this->status = "FAILED";
    }

    // OOP Concept: this Keyword
    Booking(Customer* customer, Show* show, const std::vector<ShowSeat*>& seats, double totalAmount) {
        this->bookingId = "BK" + std::to_string(nextBookingNumber++);
        this->customer = customer;
        this->show = show;
        this->bookedSeats = seats;
        this->totalAmount = totalAmount;
        this->status = "CONFIRMED";
    }

    std::string getBookingId() const {
        return this->bookingId;
    }

    Customer* getCustomer() const {
        return this->customer;
    }

    Show* getShow() const {
        return this->show;
    }

    const std::vector<ShowSeat*>& getBookedSeats() const {
        return this->bookedSeats;
    }

    double getTotalAmount() const {
        return this->totalAmount;
    }

    std::string getStatus() const {
        return this->status;
    }

    void confirmBooking() {
        this->status = "CONFIRMED";
    }

    void cancelBooking() {
        this->status = "CANCELLED";
    }

    void failBooking() {
        this->status = "FAILED";
    }
};
