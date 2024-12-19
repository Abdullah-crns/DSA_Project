#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <map>
using namespace std;

// Base class for Tickets
class Ticket
{
protected:
    string ticketType; // Type of ticket (Train, Bus, Concert, etc.)
public:
    Ticket(string type) : ticketType(type) {}
    virtual void displayOptions() = 0; // Display ticket options
    virtual void bookTicket() = 0;     // Book a ticket
    virtual void cancelTicket() = 0;   // Cancel a ticket
    virtual void showDetails() = 0;    // Show specific details of the ticket type
    virtual ~Ticket() {}               // Virtual destructor
};

class TrainTicket : public Ticket
{
public:
    TrainTicket() : Ticket("Train") {}

    void displayOptions() override
    {
        cout << "Displaying train station table...\n";
        cout << "-------------------------------------\n";
        cout << "| CITY      | DISTANCE | DEPARTURE TIME  | DEPARTURE DATE |\n";
        cout << "| ISLAMABAD | 300 km   | 10:00 AM        | 2024-12-10     |\n";
        cout << "| LAHORE    | 500 km   | 02:00 PM        | 2024-12-11     |\n";
        cout << "| KARACHI   | 1200 km  | 05:00 PM        | 2024-12-12     |\n";
        cout << "| PESHAWAR  | 200 km   | 08:00 AM        | 2024-12-13     |\n";
        cout << "-------------------------------------\n";
    }

    void bookTicket() override
    {
        cout << "Booking a train ticket...\n";
        // Placeholder for booking logic (e.g., input for choosing the city, date, and time)
        cout << "Please select a city from the available options.\n";
    }

    void cancelTicket() override
    {
        cout << "Canceling a train ticket...\n";
        // Placeholder for cancellation logic (e.g., request for ticket details)
        cout << "Enter your ticket number to cancel your reservation.\n";
    }

    void showDetails() override
    {
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
class BusTicket : public Ticket
{
public:
    BusTicket() : Ticket("Bus") {}

    void displayOptions() override
    {
        cout << "Displaying bus station table...\n";
        // Placeholder for showing bus station details
    }

    void bookTicket() override
    {
        cout << "Booking a bus ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override
    {
        cout << "Canceling a bus ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override
    {
        cout << "Showing bus ticket details...\n";
        // Placeholder for bus-specific details
    }
};

// Concert Ticket class
class ConcertTicket : public Ticket
{
public:
    ConcertTicket() : Ticket("Concert") {}

    void displayOptions() override
    {
        cout << "Displaying concert options...\n";
        // Placeholder for concert options
    }

    void bookTicket() override
    {
        cout << "Booking a concert ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override
    {
        cout << "Canceling a concert ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override
    {
        cout << "Showing concert ticket details...\n";
        // Placeholder for concert-specific details
    }
};

// Cricket Match Ticket class
class CricketMatchTicket : public Ticket
{
public:
    CricketMatchTicket() : Ticket("Cricket Match") {}

    void displayOptions() override
    {
        cout << "Displaying cricket match options...\n";
        // Placeholder for cricket match options
    }

    void bookTicket() override
    {
        cout << "Booking a cricket match ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override
    {
        cout << "Canceling a cricket match ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override
    {
        cout << "Showing cricket match ticket details...\n";
        // Placeholder for cricket match-specific details
    }
};

// Movie Ticket class
class MovieTicket : public Ticket
{
public:
    MovieTicket() : Ticket("Movie") {}

    void displayOptions() override
    {
        cout << "Displaying movie options...\n";
        // Placeholder for movie options
    }

    void bookTicket() override
    {
        cout << "Booking a movie ticket...\n";
        // Placeholder for booking logic
    }

    void cancelTicket() override
    {
        cout << "Canceling a movie ticket...\n";
        // Placeholder for cancellation logic
    }

    void showDetails() override
    {
        cout << "Showing movie ticket details...\n";
        // Placeholder for movie-specific details
    }
};

// Main function
int main()
{
    int choice;

    do
    {
        cout << "---------------------------------------------\n";
        cout << " WELCOME TO THE TICKETING RESERVATION SYSTEM \n";
        cout << "---------------------------------------------\n";
        cout << "1. ADMIN PANEL\n";
        cout << "2. USER PANEL\n";
        cout << "3. EXIT\n";
        cout << "SELECT AN OPTION: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Admin Panel
            string username, password;
            cout << "WELCOME TO ADMIN PANEL\n";
            cout << "ENTER USERNAME: ";
            cin >> username;
            cout << "ENTER PASSWORD: ";
            cin >> password;
            if (username != "admin" || password != "xerox_123")
            {
                cout << "INVALID CREDENTIALS. ACCESS DENIED.\n";
                break;
            }
            else
            {
                int adminChoice;
                do
                {
                    cout << "ACCESS GRANTED.\n";
                    cout << "=============================================\n";
                    cout << "1. CONCERT TICKET MANAGEMENT\n";
                    cout << "2. TRAIN TICKET MANAGEMENT\n";
                    cout << "3. BUS TICKET MANAGEMENT\n";
                    cout << "4. CRICKET MATCH TICKET MANAGEMENT\n";
                    cout << "5. MOVIE TICKET MANAGEMENT\n";
                    cout << "6. EXIT\n";
                    cout << "SELECT AN OPTION: ";
                    cin >> adminChoice;

                    switch (adminChoice)
                    {
                    case 1:
                        cout << "Managing Concert Tickets...\n";
                        // Add logic here
                        break;
                    case 2:
                        cout << "Managing Train Tickets...\n";
                        // Add logic here
                        break;
                    case 3:
                        cout << "Managing Bus Tickets...\n";
                        // Add logic here
                        break;
                    case 4:
                        cout << "Managing Cricket Match Tickets...\n";
                        // Add logic here
                        break;
                    case 5:
                        cout << "Managing Movie Tickets...\n";
                        // Add logic here
                        break;
                    case 6:
                        cout << "Exiting Admin Panel...\n";
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                        break;
                    }
                } while (adminChoice != 6);
            }
            break;
        }
        case 2:
            cout << "USER PANEL UNDER CONSTRUCTION.\n";
            break;
        case 3:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
