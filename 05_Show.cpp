#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Show
// Responsibility: Represents one screening = a Movie on a Screen at a specific time; owns its ShowSeats.

class Show {
private:
    int showId;
    // OOP Concept: Aggregation - Show borrows a Movie (Movie exists independently)
    Movie* movie;
    // OOP Concept: Aggregation - Show borrows a Screen
    Screen* screen;
    std::string startTime;
    // OOP Concept: Composition - Show owns its ShowSeats for this specific screening
    std::vector<ShowSeat> showSeats;

public:
    Show() {
        this->showId = 0;
        this->movie = nullptr;
        this->screen = nullptr;
        this->startTime = "";
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword
    Show(int showId, Movie* movie, Screen* screen, std::string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        initializeShowSeats();
    }

    void initializeShowSeats() {
        if (this->screen == nullptr) return;
        const std::vector<Seat>& physicalSeats = this->screen->getSeats();
        this->showSeats.clear();
        for (size_t index = 0; index < physicalSeats.size(); ++index) {
            this->showSeats.push_back(ShowSeat(physicalSeats[index].getSeatNumber(), physicalSeats[index].getSeatType()));
        }
    }

    int getShowId() const {
        return this->showId;
    }

    Movie* getMovie() const {
        return this->movie;
    }

    Screen* getScreen() const {
        return this->screen;
    }

    std::string getStartTime() const {
        return this->startTime;
    }

    std::vector<ShowSeat>& getShowSeats() {
        return this->showSeats;
    }

    const std::vector<ShowSeat>& getShowSeats() const {
        return this->showSeats;
    }

    ShowSeat* getShowSeat(const std::string& seatNumber) {
        for (size_t index = 0; index < this->showSeats.size(); ++index) {
            if (this->showSeats[index].getSeatNumber() == seatNumber) {
                return &this->showSeats[index];
            }
        }
        return nullptr;
    }

    void displaySeatLayout() const {
        if (this->screen == nullptr || this->movie == nullptr) return;

        std::cout << "\n" << this->screen->getScreenName() << "  " << this->startTime 
                  << " | " << this->movie->getTitle() << "\n";

        std::cout << "SILVER   ";
        for (size_t i = 0; i < this->showSeats.size(); ++i) {
            if (this->showSeats[i].getSeatType() == SeatType::SILVER) {
                std::string status = this->showSeats[i].isAvailable() ? "[ ]" : "[X]";
                std::cout << this->showSeats[i].getSeatNumber() << status << " ";
            }
        }
        std::cout << "\nGOLD     ";
        for (size_t i = 0; i < this->showSeats.size(); ++i) {
            if (this->showSeats[i].getSeatType() == SeatType::GOLD) {
                std::string status = this->showSeats[i].isAvailable() ? "[ ]" : "[X]";
                std::cout << this->showSeats[i].getSeatNumber() << status << " ";
            }
        }
        std::cout << "\nPLATINUM ";
        for (size_t i = 0; i < this->showSeats.size(); ++i) {
            if (this->showSeats[i].getSeatType() == SeatType::PLATINUM) {
                std::string status = this->showSeats[i].isAvailable() ? "[ ]" : "[X]";
                std::cout << this->showSeats[i].getSeatNumber() << status << " ";
            }
        }
        std::cout << "\n\n( [ ] = available  [X] = booked )\n";
    }
};
