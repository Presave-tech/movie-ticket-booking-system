#pragma once
#include <string>

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: Payment
// Responsibility: The payment contract - defines pure virtual payment interface.

class Payment {
public:
    virtual ~Payment() {}

    // OOP Concept: Abstraction - pure virtual method forming payment interface contract
    virtual bool pay(double amount) = 0;

    virtual std::string getMethodName() const = 0;
};
