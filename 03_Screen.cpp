#pragma once
#include <string>
#include <vector>
#include "02_Seat.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Screen
// Responsibility: Represents one auditorium with a screen number, and owns its seats.

class Screen {
private:
    int screenNumber;
    std::string screenName;
    // OOP Concept: Composition - Screen owns its physical seats (lifetime bound)
    std::vector<Seat> seats;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    Screen() {
        this->screenNumber = 0;
        this->screenName = "";
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword
    Screen(int screenNumber, std::string screenName) {
        this->screenNumber = screenNumber;
        this->screenName = screenName;
    }

    void addSeat(const Seat& seat) {
        this->seats.push_back(seat);
    }

    int getScreenNumber() const {
        return this->screenNumber;
    }

    std::string getScreenName() const {
        return this->screenName;
    }

    const std::vector<Seat>& getSeats() const {
        return this->seats;
    }
};
