#pragma once
#include <iostream>
#include <string>
#include "09_Payment.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Classes: UpiPayment, CardPayment, CashPayment
// Responsibility: Implements concrete payment methods.

// OOP Concept: Inheritance - UpiPayment derives from Payment base class
class UpiPayment : public Payment {
public:
    // OOP Concept: Runtime Polymorphism - overridden method for dynamic dispatch
    bool pay(double amount) override {
        std::cout << "[UPI] Rs." << static_cast<int>(amount) << " paid successfully\n";
        return true;
    }

    std::string getMethodName() const override {
        return "UPI";
    }
};

// OOP Concept: Inheritance - CardPayment derives from Payment base class
class CardPayment : public Payment {
public:
    // OOP Concept: Runtime Polymorphism - overridden method for dynamic dispatch
    bool pay(double amount) override {
        std::cout << "[Card] Rs." << static_cast<int>(amount) << " paid successfully\n";
        return true;
    }

    std::string getMethodName() const override {
        return "Card";
    }
};

// OOP Concept: Inheritance - CashPayment derives from Payment base class
class CashPayment : public Payment {
public:
    // OOP Concept: Runtime Polymorphism - overridden method for dynamic dispatch
    bool pay(double amount) override {
        std::cout << "[Cash] Rs." << static_cast<int>(amount) << " paid successfully\n";
        return true;
    }

    std::string getMethodName() const override {
        return "Cash";
    }
};

// OOP Concept: Inheritance - FailedPayment simulates payment gateway failure
class FailedPayment : public Payment {
public:
    // OOP Concept: Runtime Polymorphism - returns false to trigger rollback
    bool pay(double amount) override {
        std::cout << "[Payment Gateway] Transaction declined for Rs." << static_cast<int>(amount) << "\n";
        return false;
    }

    std::string getMethodName() const override {
        return "FailedPayment";
    }
};

