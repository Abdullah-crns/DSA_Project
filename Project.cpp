#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <map>
using namespace std;

// Base class for Tickets
class Ticket {
protected:
    string ticketType; // Type of ticket (Train, Bus, Concert, etc.)
public:
    Ticket(string type) : ticketType(type) {}
    virtual void displayOptions() = 0; // Display ticket options
    virtual void bookTicket() = 0; // Book a ticket
    virtual void cancelTicket() = 0; // Cancel a ticket
    virtual void showDetails() = 0; // Show specific details of the ticket type
    virtual ~Ticket() {} // Virtual destructor
};

class TrainTicket : public Ticket {
public:
    TrainTicket() : Ticket("Train") {}

    void displayOptions() override {
        cout << "Displaying train station table...\n";
        cout << "-------------------------------------\n";
        cout << "| CITY      | DISTANCE | DEPARTURE TIME  | DEPARTURE DATE |\n";
        cout << "| ISLAMABAD | 300 km   | 10:00 AM        | 2024-12-10     |\n";
        cout << "| LAHORE    | 500 km   | 02:00 PM        | 2024-12-11     |\n";
        cout << "| KARACHI   | 1200 km  | 05:00 PM        | 2024-12-12     |\n";
        cout << "| PESHAWAR  | 200 km   | 08:00 AM        | 2024-12-13     |\n";
        cout << "-------------------------------------\n";
    }

    void bookTicket() override {
        cout << "Booking a train ticket...\n";
        // Placeholder for booking logic (e.g., input for choosing the city, date, and time)
        cout << "Please select a city from the available options.\n";
    }

    void cancelTicket() override {
        cout << "Canceling a train ticket...\n";
        // Placeholder for cancellation logic (e.g., request for ticket details)
        cout << "Enter your ticket number to cancel your reservation.\n";
    }

    void showDetails() override {
        cout << "Showing train ticket details...\n";
        // Placeholder for train-specific details (e.g., departure info, seat info, etc.)
        cout << "Ticket Type: " << ticketType << endl;
        cout << "Departure City: Islamabad\n";
        cout << "Arrival City: Lahore\n";
        cout << "Departure Date: 2024-12-10\n";
        cout << "Departure Time: 10:00 AM\n";
        cout << "Seat Number: A1\n";
    }
};

// Bus Ticket class
class BusTicket : public Ticket {
public:
    BusTicket() : Ticket("Bus") {}

    void displayOptions() override {
        cout << "Displaying bus station table...\n";
        // Placeholder for showing bus station details
    }

    void bookTicket() override {
        cout << "Booking a bus ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override {
        cout << "Canceling a bus ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override {
        cout << "Showing bus ticket details...\n";
        // Placeholder for bus-specific details
    }
};

// Concert Ticket class
class ConcertTicket : public Ticket {
public:
    ConcertTicket() : Ticket("Concert") {}

    void displayOptions() override {
        cout << "Displaying concert options...\n";
        // Placeholder for concert options
    }

    void bookTicket() override {
        cout << "Booking a concert ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override {
        cout << "Canceling a concert ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override {
        cout << "Showing concert ticket details...\n";
        // Placeholder for concert-specific details
    }
};

// Cricket Match Ticket class
class CricketMatchTicket : public Ticket {
public:
    CricketMatchTicket() : Ticket("Cricket Match") {}

    void displayOptions() override {
        cout << "Displaying cricket match options...\n";
        // Placeholder for cricket match options
    }

    void bookTicket() override {
        cout << "Booking a cricket match ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override {
        cout << "Canceling a cricket match ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override {
        cout << "Showing cricket match ticket details...\n";
        // Placeholder for cricket match-specific details
    }
};

// Movie Ticket class
class MovieTicket : public Ticket {
public:
    MovieTicket() : Ticket("Movie") {}

    void displayOptions() override {
        cout << "Displaying movie options...\n";
        // Placeholder for movie options
    }

    void bookTicket() override {
        cout << "Booking a movie ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override {
        cout << "Canceling a movie ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override {
        cout << "Showing movie ticket details...\n";
        // Placeholder for movie-specific details
    }
};

// Main function
int main() {
    int choice;

    while (true) {
        cout << "\n--- Ticket Reservation System ---\n";
        cout << "1. Train Ticket\n";
        cout << "2. Bus Ticket\n";
        cout << "3. Concert Ticket\n";
        cout << "4. Cricket Match Ticket\n";
        cout << "5. Movie Ticket\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        Ticket* ticket = nullptr;

        switch (choice) {
            case 1:
                ticket = new TrainTicket();
                break;
            case 2:
                ticket = new BusTicket();
                break;
            case 3:
                ticket = new ConcertTicket();
                break;
            case 4:
                ticket = new CricketMatchTicket();
                break;
            case 5:
                ticket = new MovieTicket();
                break;
            case 6:
                cout << "Exiting the system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
                continue;
        }

        // Menu for each ticket type
        int ticketChoice;
        do {
            cout << "\n--- " << " Ticket Menu ---\n";
            cout << "1. Display Options\n";
            cout << "2. Book Ticket\n";
            cout << "3. Cancel Ticket\n";
            cout << "4. Show Details\n";
            cout << "5. Back to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> ticketChoice;

            switch (ticketChoice) {
                case 1:
                    ticket->displayOptions();
                    break;
                case 2:
                    ticket->bookTicket();
                    break;
                case 3:
                    ticket->cancelTicket();
                    break;
                case 4:
                    ticket->showDetails();
                    break;
                case 5:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (ticketChoice != 5);

        delete ticket; // Free allocated memory
    }

    return 0;
}
