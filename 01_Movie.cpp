#pragma once
#include <string>

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Movie
// Responsibility: Stores movie title, language, and duration - nothing else.

class Movie {
private:
    // OOP Concept: Encapsulation - attributes are private
    std::string title;
    std::string language;
    int durationMinutes;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    Movie() {
        this->title = "";
        this->language = "";
        this->durationMinutes = 0;
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword - refers to the current object's attributes
    Movie(std::string title, std::string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }

    // Intention-revealing getters
    std::string getTitle() const {
        return this->title;
    }

    std::string getLanguage() const {
        return this->language;
    }

    int getDurationMinutes() const {
        return this->durationMinutes;
    }
};
