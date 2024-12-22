#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <list>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Struct to represent seats
struct Stadium_Seats
{
    string seat_no; // Seat number
    bool isBooked;  // Seat booked status
};

// Struct to represent a section
struct Stadium_section
{
    string name;
    string location;
    Stadium_Seats seats[250];
    bool isBooked;
    double price; // Price for booking this section
};

// Struct to represent a reservation
// Struct to represent a reservation
struct Stadium_Reservation
{
    string name;
    string gender;
    int age; // Added age field
    string ticketID;
    string time;
    string singer_name;
    string type;
    string date;
    string location;
    string section_Name; // Stadium_section name where the reservation is made
    string seatNumber;   // Seat number reserved
};

// Struct to represent a stadium
struct Stadium
{
    string Team1;
    string Team2;
    bool isBooked;
    string name;
    string type;
    string date;
    string time;
    string venue;
    double price;
    list<Stadium_Reservation> reservations; // List of reservations for this stadium
    vector<Stadium_section> sections;       // Halls associated with this stadium

    // Constructor to initialize sections
    Stadium()
    {
        sections.resize(5);
        sections[0] = {"BRONZE SECTION", venue, {}, false, 500};    // Platinum Stadium_section
        sections[1] = {"SILVER SECTION", venue, {}, false, 800};    // Gold Stadium_section
        sections[2] = {"GOLD SECTION", venue, {}, false, 1000};     // Silver Stadium_section
        sections[3] = {"PLATINUM SECTION", venue, {}, false, 2000}; // Bronze Stadium_section
        sections[4] = {"VIP SECTION", venue, {}, false, 2500};      // VIP Stadium_section
    }
};

// Class to manage the stadium graph
class StadiumGraph
{
private:
    unordered_map<string, Stadium> stadiums; // Map of stadium name to Stadium object

public:
    // Constructor
    StadiumGraph() {}

    // Add a stadium to the graph
    void addMatch(const string &Team1, const string &Team2, const string &name, const string &type, const string &date, const string &time, const string &venue)
    {
        // Check if a match with the same name already exists
        if (stadiums.find(name) != stadiums.end() && stadiums.find(time) != stadiums.end())
        {
            cout << "A MATCH AT '" << name << " ALREADY EXISTS AT THIUS TIME.\n";
            return; // Exit the function to prevent duplicate entries
        }

        // Create a new Stadium object
        Stadium newStadium;
        newStadium.isBooked = false; // Initialize booking status
        newStadium.Team1 = Team1;    // Set Team 1
        newStadium.Team2 = Team2;    // Set Team 2
        newStadium.name = name;      // Set match name
        newStadium.type = type;      // Set match type
        newStadium.date = date;      // Set match date
        newStadium.time = time;      // Set match time
        newStadium.venue = venue;    // Set match venue

        // Add the new stadium (match) to the graph
        stadiums[name] = newStadium;
    }

    // Display all stadiums
    void displayUpcomingMatches()
    {
        if (stadiums.empty())
        {
            cout << "No Concerts available.\n";
            return;
        }
        cout << "========================================\n";
        cout << "          UPCOMING MATCHES:\n";
        cout << "========================================\n";
        for (const auto &pair : stadiums)
        {
            const Stadium &stadium = pair.second;
            cout << "========================================\n";
            cout << "STADIUM               :" << stadium.name << "\n";
            cout << "MATCH CATEGORY        :" << stadium.type << "\n";
            cout << "TEAM 1                :" << stadium.Team1 << "\n";
            cout << "TEAM 2                :" << stadium.Team2 << "\n";
            cout << "DATE                  :" << stadium.date << "\n";
            cout << "TIME                  :" << stadium.time << "\n";
            cout << "CITY                  :" << stadium.venue << "\n";
            cout << "========================================\n";
        }
    }
    // Delete a match (stadium) from the graph
    // Delete a match (stadium) from the graph based on stadium name and date
    // Reserve a ticket for a stadium
    void reserveTicket(const string &stadiumName, const string &name, const string &gender, int age)
    {
        if (stadiums.find(stadiumName) == stadiums.end())
        {
            cout << "Stadium not found.\n";
            return;
        }

        Stadium &stadium = stadiums[stadiumName];

        // Check if any seat or section is already booked
        if (stadium.isBooked || std::any_of(stadium.sections.begin(), stadium.sections.end(), [](const Stadium_section &section)
                                            { return section.isBooked; }))
        {
            cout << "There is already a booking for this event.\n";
            return;
        }

        int choice;
        cout << "========================================\n";
        cout << "           Choose booking type:\n";
        cout << "========================================\n";
        cout << "1. Book Entire Event\n";
        cout << "2. Book a Stadium_section\n";
        cout << "3. Book a Seat\n";
        cout << "========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Book entire event'
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 50; j++)
                {
                    if (stadium.sections[i].seats[j].isBooked)
                    {
                        cout << " A Seat is already booked here\n";
                        return;
                    }
                }
            }
            stadium.isBooked = true;
            {
                string ticketID = to_string(rand() % 10000); // Generate a random ticket ID
                cout << "Event booked successfully for " << stadiumName << ".\n";
                cout << "========================================\n";
                cout << "           RESERVATION DETAILS\n";
                cout << "========================================\n";
                cout << "| STADIUM:        | " << name << endl;
                cout << "| TICKET ID:      | " << ticketID << endl;
                cout << "| GENDER:         | " << gender << endl;
                cout << "| AGE:            | " << age << endl;
                cout << "| CITY:           | " << stadium.venue << endl;
                cout << "| MATCH DATE:     | " << stadium.date << endl;
                cout << "| MATCH TIME:     | " << stadium.time << endl;
                cout << "========================================\n";

                // Create a reservation entry
                Stadium_Reservation reservation;
                reservation.name = name;
                reservation.ticketID = ticketID;
                reservation.gender = gender;
                reservation.age = age;
                reservation.time = stadium.time;
                reservation.date = stadium.date;
                reservation.location = stadium.venue;
                stadium.reservations.push_back(reservation); // Add reservation to stadium
            }
            break;

        case 2:
        { // Book a section
            // Check if the event is already booked
            if (stadium.isBooked)
            {
                cout << "There is already a booking for this event.\n";
                return;
            }

            cout << "Available Halls:\n";
            for (size_t i = 0; i < stadium.sections.size(); ++i)
            {
                cout << i + 1 << ". " << stadium.sections[i].name << " - Price: " << stadium.sections[i].price << "\n";
            }
            int hallChoice;
            cout << "Select a section to book: ";
            cin >> hallChoice;

            if (hallChoice < 1 || hallChoice > stadium.sections.size() || stadium.sections[hallChoice - 1].isBooked)
            {
                cout << "Invalid choice or section already booked.\n";
                return;
            }

            Stadium_Reservation reservation;
            reservation.name = name;
            reservation.gender = gender;
            reservation.age = age;
            reservation.ticketID = to_string(rand() % 10000);                 // Generate a random ticket ID
            reservation.section_Name = stadium.sections[hallChoice - 1].name; // Set section name
            stadium.reservations.push_back(reservation);                      // Add reservation to stadium

            stadium.sections[hallChoice - 1].isBooked = true;
            cout << "Stadium_section " << stadium.sections[hallChoice - 1].name << " booked successfully.\n";
            cout << "========================================\n";
            cout << "           RESERVATION DETAILS\n";
            cout << "========================================\n";
            cout << "| STADIUM:        | " << name << endl;
            cout << "| TICKET ID:      | " << reservation.ticketID << endl;
            cout << "| GENDER:         | " << gender << endl;
            cout << "| AGE:            | " << age << endl;
            cout << "| SECTION NAME:   | " << reservation.section_Name << endl;
            cout << "| MATCH DATE:     | " << stadium.date << endl;
            cout << "| MATCH VENUE:    | " << stadium.venue << endl;
            cout << "| MATCH TIME:     | " << stadium.time << endl;
            cout << "========================================\n";
            break;
        }

        case 3:
        { // Book a seat
            // Check if the event is already booked
            if (stadium.isBooked)
            {
                cout << "There is already a booking for this event.\n";
                return;
            }

            cout << "Available Halls:\n";
            for (size_t i = 0; i < stadium.sections.size(); ++i)
            {
                cout << i + 1 << ". " << stadium.sections[i].name << " - Price: " << stadium.sections[i].price << "\n";
            }
            int hallChoice;
            cout << "Select a section to book a seat: ";
            cin >> hallChoice;

            if (hallChoice < 1 || hallChoice > stadium.sections.size() || stadium.sections[hallChoice - 1].isBooked)
            {
                cout << "Invalid choice or section already booked.\n";
                return;
            }

            Stadium_section &selectedSection = stadium.sections[hallChoice - 1];
            cout << "========================================\n";
            cout << "AVAILABLE SEATS IN  " << selectedSection.name << ":\n";
            cout << "========================================\n";

            // Display available seats
            for (int i = 0; i < 50; i++)
            {
                selectedSection.seats[i].seat_no = to_string(i + 1); // Assign seat numbers
            }
            for (int i = 0; i < 50; ++i)
            {
                if (!selectedSection.seats[i].isBooked)
                {
                    cout << selectedSection.seats[i].seat_no << " | "; // Print available seat numbers
                }
                if (i == 10 || i == 20 || i == 30 || i == 40)
                {
                    cout << "\n"; // New line for better readability
                }
            }
            cout << "\n"; // New line for better readability

            cout << "ENTER SEAT NUMBER TO BOOK: ";
            string seatNumber;
            cin >> seatNumber;

            // Check if the seat number is valid
            bool seatFound = false;
            for (int i = 0; i < 50; ++i)
            {
                if (selectedSection.seats[i].seat_no == seatNumber)
                {
                    if (!selectedSection.seats[i].isBooked)
                    {
                        selectedSection.seats[i].isBooked = true;
                        cout << "Seat " << seatNumber << " booked successfully in " << selectedSection.name << ".\n";
                        seatFound = true;

                        // Create a reservation entry
                        Stadium_Reservation reservation;
                        reservation.name = name;
                        reservation.gender = gender;
                        reservation.age = age;
                        reservation.ticketID = to_string(rand() % 10000); // Generate a random ticket ID
                        reservation.section_Name = selectedSection.name;  // Set section name
                        reservation.seatNumber = seatNumber;              // Set seat number
                        stadium.reservations.push_back(reservation);      // Add reservation to stadium

                        cout << "========================================\n";
                        cout << "           RESERVATION DETAILS\n";
                        cout << "========================================\n";
                        cout << "| STADIUM:        | " << name << endl;
                        cout << "| TICKET ID:      | " << reservation.ticketID << endl;
                        cout << "| GENDER:         | " << gender << endl;
                        cout << "| AGE:            | " << age << endl;
                        cout << "| SECTION NAME:   | " << reservation.section_Name << endl;
                        cout << "| SEAT NUMBER:    | " << reservation.seatNumber << endl;
                        cout << "| MATCH DATE:     | " << stadium.date << endl;
                        cout << "| MATCH VENUE:    | " << stadium.venue << endl;
                        cout << "| MATCH TIME:     | " << stadium.time << endl;
                        cout << "========================================\n";
                        break;
                    }
                    else
                    {
                        cout << "Seat " << seatNumber << " is already booked.\n";
                        return;
                    }
                }
            }
            if (!seatFound)
            {
                cout << "Invalid seat number.\n";
            }
            break;
        }

        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    // Display reservations for a stadium
    // Display reservations for a stadium
    void displayReservations(const string &ticketID = "")
    {
        if (ticketID.empty())
        {
            cout << "No ticket ID provided.\n";
            return;
        }

        bool found = false; // Flag to check if the reservation is found

        // Iterate through all stadiums to find the reservation by ticket ID
        for (const auto &concertPair : stadiums)
        {
            const Stadium &stadium = concertPair.second;

            for (const auto &reservation : stadium.reservations)
            {
                if (reservation.ticketID == ticketID)
                {
                    // Print ticket-like format
                    cout << "========================================\n";
                    cout << "               TICKET\n";
                    cout << "========================================\n";
                    cout << "| TICKET ID:      | " << reservation.ticketID << "\n";
                    cout << "| STADIUM:        | " << reservation.name << "\n";
                    cout << "| GENDER:         | " << reservation.gender << "\n";
                    cout << "| AGE:            | " << reservation.age << "\n";
                    cout << "| TEAM 1:         | " << stadium.Team1 << endl;
                    cout << "| TEAM 2:         | " << stadium.Team2 << endl;
                    cout << "| MATCH NAME:     | " << stadium.name << "\n";
                    cout << "| MATCH THEME:    | " << stadium.type << "\n";
                    cout << "| VENUE:          | " << stadium.venue << "\n"; // Assuming venue is a field in Stadium
                    cout << "| SECTION:        | " << reservation.section_Name << "\n";
                    cout << "| SEAT:           | " << reservation.seatNumber << "\n";
                    cout << "| DATE:           | " << stadium.date << "\n"; // Date and time of the reservation
                    cout << "| TIME:           | " << stadium.time << "\n"; // Date and time of the reservation
                    cout << "========================================\n";
                    found = true; // Set the flag to true
                    break;        // Exit the inner loop
                }
            }
            if (found)
                break; // Exit the outer loop if found
        }

        if (!found)
        {
            cout << "No reservation found for ticket ID " << ticketID << ".\n";
        }
    }

    // Delete a reservation by ticket ID
    void deleteReservation(const string &stadiumName, const string &ticketID)
    {
        if (stadiums.find(stadiumName) == stadiums.end())
        {
            cout << "Stadium not found.\n";
            return;
        }

        Stadium &stadium = stadiums[stadiumName];
        auto it = stadium.reservations.begin();
        while (it != stadium.reservations.end())
        {
            if (it->ticketID == ticketID)
            {
                it = stadium.reservations.erase(it); // Remove reservation
                cout << "Stadium_Reservation with ticket ID " << ticketID << " deleted successfully.\n";
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Ticket ID not found in reservations.\n";
    }
    // Delete a match using a unique identifier (stadium name and date)
    // Delete a match using a unique identifier (stadium name and date)
    void deleteMatch(const string &stadiumName)
    {
        // Iterate through the stadiums to find and delete the match
        auto it = stadiums.find(stadiumName); // Find by stadium name
        if (it != stadiums.end())
        {
            stadiums.erase(it); // Remove the stadium from the map
            cout << "Match AT '" << stadiumName << "' deleted successfully.\n";
        }
        else
        {
            cout << "Stadium not found.\n";
        }
    }
};

// Main function to interact with the user
int main()
{
    StadiumGraph graph;
    graph.addMatch("India", "Pakistan ", "GADDAFI-STADIUM", "Cricket", "2025-01-10", "10:00", "Mumbai    ");
    graph.addMatch("India", "Australia", "ADELEDE OVAL", "Cricket", "2025-03-12", "10:00", "Delhi     ");
    graph.addMatch("India", "England  ", "MCG", "Cricket", "2025-01-14", "10:00", "Rawalpindi");

    int roleChoice;
    string stadium_to_delete;
    string date_to_delete;
    do
    {
        cout << "\n1. Admin Panel\n2. User Panel\n3. Exit\nSelect your role: ";
        cin >> roleChoice;

        if (roleChoice == 1)
        {
            int adminChoice;
            do
            {
                cout << "========================================\n";
                cout << "|             ADMIN PANEL:             |\n";
                cout << "========================================\n";
                cout << "1. ADD MATCH \n2. DISPLAY MATCHES\n3. DELETE MATCH DATA \n 4.EXIT\nSELECT AN OPTION: ";
                cin >> adminChoice;

                switch (adminChoice)
                {
                case 1:
                {
                    string name, type, date, time, venue, Team1, Team2;
                    cout << "Enter stadium name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter Team1: ";
                    getline(cin, Team1);
                    cout << "Enter Team2: ";
                    getline(cin, Team2);
                    cout << "Enter match type: ";
                    getline(cin, type);
                    cout << "Enter match date (YYYY-MM-DD): ";
                    getline(cin, date);
                    cout << "Enter match time (HH:MM): ";
                    getline(cin, time);
                    cout << "Enter match venue: ";
                    getline(cin, venue);
                    graph.addMatch(Team1, Team2, name, type, date, time, venue);

                    cout << "MATCH" << Team1 << "vs" << Team2 << " ADDED SUCCESSFULLY .\n"; // Confirmation message
                    break;
                }
                case 2:
                    graph.displayUpcomingMatches();
                    break;
                case 3:
                    cout << "ENTER THE NAME OF THE STADIUM ";
                    cin.ignore();
                    getline(cin, stadium_to_delete);
                    graph.deleteMatch(stadium_to_delete);
                    break;
                case 4:
                    cout << "Exiting admin panel.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (adminChoice != 3);
        }
        else if (roleChoice == 2)
        {
            int userChoice;
            do
            {
                cout << "========================================\n";
                cout << "         MATCH TICKET RESERVATION        \n";
                cout << "========================================\n";
                cout << "1. Reserve Ticket\n2. View Reservations\n3. Delete Stadium_Reservation\n4. Exit\n";
                cout << "Select an option: ";
                cin >> userChoice;

                switch (userChoice)
                {
                case 1:
                {
                    graph.displayUpcomingMatches();
                    string stadiumName, name, gender;
                    int age;
                    cout << "Enter stadium name: ";
                    cin.ignore();
                    getline(cin, stadiumName);
                    cout << "Enter your name: ";
                    getline(cin, name);
                    cout << "Enter your gender: ";
                    getline(cin, gender);
                    cout << "Enter your age: ";
                    cin >> age;

                    graph.reserveTicket(stadiumName, name, gender, age);
                    break;
                }
                case 2:
                {
                    string TicketID;
                    cout << "Enter ticket ID to view reservations: ";
                    cin.ignore();
                    getline(cin, TicketID);
                    graph.displayReservations(TicketID);
                    break;
                }
                case 3:
                {
                    string stadiumName, ticketID;
                    cout << "Enter stadium name to delete reservation: ";
                    cin.ignore();
                    getline(cin, stadiumName);
                    cout << "Enter ticket ID to delete: ";
                    getline(cin, ticketID);
                    graph.deleteReservation(stadiumName, ticketID);
                    break;
                }
                case 4:
                    cout << "Exiting user panel.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (userChoice != 4);
        }
        else if (roleChoice != 3)
        {
            cout << "Invalid role chosen (admin/customer)\n";
        }
    } while (roleChoice != 3);
}
