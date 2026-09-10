#pragma once
#include <string>

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Seat
// Responsibility: Represents one physical seat with a number and type (SILVER/GOLD/PLATINUM).

enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

class Seat {
private:
    // OOP Concept: Encapsulation - seat properties are private
    std::string seatNumber;
    SeatType seatType;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    Seat() {
        this->seatNumber = "";
        this->seatType = SeatType::SILVER;
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword - distinguishes member variables from parameters
    Seat(std::string seatNumber, SeatType seatType) {
        this->seatNumber = seatNumber;
        this->seatType = seatType;
    }

    std::string getSeatNumber() const {
        return this->seatNumber;
    }

    SeatType getSeatType() const {
        return this->seatType;
    }

    std::string getSeatTypeString() const {
        if (this->seatType == SeatType::SILVER) return "SILVER";
        if (this->seatType == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};
