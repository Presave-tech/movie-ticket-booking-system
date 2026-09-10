#pragma once
#include <string>
#include "02_Seat.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: ShowSeat
// Responsibility: Represents the booking status of ONE seat FOR ONE specific show (AVAILABLE / BOOKED).

enum class SeatStatus {
    AVAILABLE,
    BOOKED
};

class ShowSeat {
private:
    std::string seatNumber;
    SeatType seatType;
    // OOP Concept: Encapsulation - seatStatus is private and only modified via validation methods
    SeatStatus seatStatus;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    ShowSeat() {
        this->seatNumber = "";
        this->seatType = SeatType::SILVER;
        this->seatStatus = SeatStatus::AVAILABLE;
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword
    ShowSeat(std::string seatNumber, SeatType seatType) {
        this->seatNumber = seatNumber;
        this->seatType = seatType;
        this->seatStatus = SeatStatus::AVAILABLE;
    }

    bool isAvailable() const {
        return this->seatStatus == SeatStatus::AVAILABLE;
    }

    // Encapsulation validation method to book seat
    bool bookSeat() {
        if (this->seatStatus == SeatStatus::AVAILABLE) {
            this->seatStatus = SeatStatus::BOOKED;
            return true;
        }
        return false;
    }

    // Encapsulation validation method to release/cancel seat
    void cancelSeat() {
        this->seatStatus = SeatStatus::AVAILABLE;
    }

    std::string getSeatNumber() const {
        return this->seatNumber;
    }

    SeatType getSeatType() const {
        return this->seatType;
    }

    SeatStatus getSeatStatus() const {
        return this->seatStatus;
    }

    std::string getSeatTypeString() const {
        if (this->seatType == SeatType::SILVER) return "SILVER";
        if (this->seatType == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};
