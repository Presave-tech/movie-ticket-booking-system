#pragma once
#include <string>
#include <vector>
#include "03_Screen.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Cinema
// Responsibility: Represents the theatre and owns its screens.

class Cinema {
private:
    std::string cinemaName;
    // OOP Concept: Composition - Cinema owns its screens
    std::vector<Screen> screens;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    Cinema() {
        this->cinemaName = "PVR Cinemas";
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword
    Cinema(std::string cinemaName) {
        this->cinemaName = cinemaName;
    }

    void addScreen(const Screen& screen) {
        this->screens.push_back(screen);
    }

    std::string getCinemaName() const {
        return this->cinemaName;
    }

    const std::vector<Screen>& getScreens() const {
        return this->screens;
    }

    Screen* getScreen(int screenNumber) {
        for (size_t index = 0; index < this->screens.size(); ++index) {
            if (this->screens[index].getScreenNumber() == screenNumber) {
                return &this->screens[index];
            }
        }
        return nullptr;
    }
};
