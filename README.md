# 🎬 Movie Ticket Booking System (Low-Level Design in C++)

A modular, robust, object-oriented **Movie Ticket Booking System** implemented in modern C++ adhering strictly to **Low-Level Design (LLD)** and **SOLID** principles.

---

## 📌 Project Overview

This project simulates a cinema ticketing platform (similar to BookMyShow, PVR, or INOX). It enables customers to browse movies, choose showtimes, view tier-based seat availability (`SILVER`, `GOLD`, `PLATINUM`), complete bookings with various payment methods, generate formatted tickets, and cancel reservations.

---

## ✨ Features

- **Movie Catalogue:** Browse currently screening movies with language and duration details.
- **Show Scheduling:** View showtimes across multiple auditorium screens.
- **Visual Seating Matrix:** Real-time seat layout showing `AVAILABLE [ ]` and `BOOKED [X]` seats grouped by tier.
- **Atomic Multi-Seat Booking:** Select multiple seats in a single transaction. If any seat is unavailable or payment fails, no seats are booked.
- **Tier-Based Dynamic Pricing:**
  - `SILVER`: ₹150
  - `GOLD`: ₹250
  - `PLATINUM`: ₹400
- **Pluggable Payment Processing (Open-Closed Principle):** Supports UPI, Credit/Debit Card, Cash, and failed payment simulations.
- **Formatted Ticket Generation:** Generates comprehensive confirmation receipts with unique booking IDs.
- **Booking Cancellation:** Reverts booked seats back to `AVAILABLE` state in real-time.
- **Robust Input Handling:** Gracefully handles invalid inputs and boundary edge cases without crashing.

---

## 🏛️ Architecture & Class Structure

The codebase is organized into modular single-responsibility units:

```
movie_ticket_system/
├── 01_Movie.cpp            # Movie entity (title, language, duration)
├── 02_Seat.cpp             # Physical seat entity (seat number, tier)
├── 03_Screen.cpp           # Cinema screen containing physical seats
├── 04_Cinema.cpp           # Multiplex entity managing screens
├── 05_Show.cpp             # Temporal screening linking Movie, Screen & Time
├── 06_ShowSeat.cpp         # Real-time seat state (AVAILABLE / BOOKED) for a show
├── 07_Customer.cpp         # Customer profile (name, phone)
├── 08_Booking.cpp          # Booking record with transaction status
├── 09_Payment.cpp          # Abstract payment interface (Strategy Pattern)
├── 10_PaymentTypes.cpp     # Concrete payment implementations (UPI, Card, Cash)
├── 11_PriceCalculator.cpp  # Pricing computation service
├── 12_TicketPrinter.cpp    # Ticket formatting and console printer
├── 13_BookingService.cpp   # Core domain orchestrator & state manager
├── main.cpp                # CLI entry point and menu loop
├── ASSIGNMENT_1_SUBMISSION.md # Comprehensive assignment report & design analysis
├── .gitignore              # Git ignore rules
└── README.md               # Project documentation
```

---

## 🎯 Object-Oriented & SOLID Principles Applied

| Principle | Implementation Details |
| :--- | :--- |
| **Single Responsibility (SRP)** | Each class has one clear concern (e.g., `TicketPrinter` formats output, `PriceCalculator` computes totals, `ShowSeat` manages state). |
| **Open-Closed Principle (OCP)** | New payment gateways (e.g., `NetBankingPayment`, `CryptoPayment`) can be added by extending the `Payment` base class without modifying `BookingService`. |
| **Liskov Substitution (LSP)** | All payment subclasses (`UpiPayment`, `CardPayment`, `CashPayment`) can interchangeably substitute `Payment*`. |
| **Interface Segregation (ISP)** | Compact, focused class interfaces with minimal coupling. |
| **Dependency Inversion (DIP)** | `BookingService` depends on abstract `Payment` interfaces rather than hard-coded concrete implementations. |

---

## 🚀 How to Build and Run

### Prerequisites
- Any modern C++ compiler supporting C++11 or higher (`g++`, `clang++`, or `MSVC`).

### Compilation

Using **GCC (g++)**:
```bash
g++ -std=c++11 main.cpp -o movie_booking
```

Using **Clang**:
```bash
clang++ -std=c++11 main.cpp -o movie_booking
```

Using **MSVC (Developer Command Prompt)**:
```cmd
cl /EHsc /std:c++14 main.cpp /Fe:movie_booking.exe
```

### Execution

**Windows:**
```cmd
.\movie_booking.exe
```

**Linux / macOS:**
```bash
./movie_booking
```

---

## 📋 Sample Walkthrough

```text
===== MOVIE TICKET BOOKING =====
1. Movies  2. Book  3. Cancel  4. My tickets  0. Exit
Choose: 1

[1] Inception       English   148 min
[2] Interstellar    English   169 min
[3] Stree 2         Hindi     147 min

Choose: 2
Choose movie: 1
[1] Screen 1  10:00 AM
[2] Screen 2  02:00 PM
Choose show: 1

--- SEAT LAYOUT (Screen 1) ---
[SILVER]   A1:[ ] A2:[ ] A3:[ ] A4:[ ] 
[GOLD]     B1:[ ] B2:[ ] B3:[ ] B4:[ ] 
[PLATINUM] C1:[ ] C2:[ ] C3:[ ] C4:[ ] 

Seats (e.g. A1,B2): A1,B2
Pay by: 1.UPI  2.Card  3.Cash  4.Simulate Failure > 1
Enter UPI ID: user@okhdfcbank
Processing UPI payment of Rs. 400.00... Success!

========================================
             CINEMA TICKET              
========================================
 Booking ID:  BK-1001
 Status:      CONFIRMED
 Customer:    Hemant (9876543210)
 Movie:       Inception (English, 148 min)
 Cinema:      PVR Cinemas | Screen 1
 Show Time:   10:00 AM
 Seats:       A1 (SILVER), B2 (GOLD)
 Total Paid:  Rs. 400.00
========================================
```

---

## 📄 Documentation

For the complete low-level design document including Noun-Verb analysis, Class Responsibility tables, and requirement traceabilities, refer to [ASSIGNMENT_1_SUBMISSION.md](ASSIGNMENT_1_SUBMISSION.md).

---

## 👤 Author

- **Hemant** (`hemuh877@gmail.com`)
