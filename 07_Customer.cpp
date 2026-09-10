#pragma once
#include <string>

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Customer
// Responsibility: Stores customer identity information (name and phone number).

class Customer {
private:
    // OOP Concept: Encapsulation
    std::string name;
    std::string phoneNumber;

public:
    // OOP Concept: Compile-Time Polymorphism - Default Constructor
    Customer() {
        this->name = "Guest";
        this->phoneNumber = "0000000000";
    }

    // OOP Concept: Compile-Time Polymorphism - Parameterized Constructor
    // OOP Concept: this Keyword
    Customer(std::string name, std::string phoneNumber) {
        this->name = name;
        this->phoneNumber = phoneNumber;
    }

    std::string getName() const {
        return this->name;
    }

    std::string getPhoneNumber() const {
        return this->phoneNumber;
    }
};
