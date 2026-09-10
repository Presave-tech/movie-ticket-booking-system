#pragma once
#include <vector>
#include "06_ShowSeat.cpp"

// Course: B.Tech CSE | Subject: System Design (TCS-504)
// Class: PriceCalculator
// Responsibility: Calculates ticket pricing based on seat types.

class PriceCalculator {
public:
    // Clean Code: Constants instead of magic numbers
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    double getSeatPrice(SeatType seatType) const {
        if (seatType == SeatType::SILVER) return SILVER_PRICE;
        if (seatType == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    // OOP Concept: Compile-Time Polymorphism - Overloaded method taking vector of ShowSeat pointers
    double calculateTotal(const std::vector<ShowSeat*>& seats) const {
        double total = 0.0;
        for (size_t i = 0; i < seats.size(); ++i) {
            if (seats[i] != nullptr) {
                total += getSeatPrice(seats[i]->getSeatType());
            }
        }
        return total;
    }

    // OOP Concept: Compile-Time Polymorphism - Overloaded method taking individual category counts
    double calculateTotal(int silverCount, int goldCount, int platinumCount) const {
        return (silverCount * SILVER_PRICE) + (goldCount * GOLD_PRICE) + (platinumCount * PLATINUM_PRICE);
    }
};
