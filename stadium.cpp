#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <unordered_map>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;
// ===========================
// Data Structures Definition
// ===========================

// Linked List for sections or seating rows
struct SectionNode
{
    string sectionName;
    pair<int, int> rowRange; // Row range for the section
    pair<int, int> colRange; // Column range for the section
    SectionNode *next;
    SectionNode(string name, pair<int, int> rows, pair<int, int> cols)
        : sectionName(name), rowRange(rows), colRange(cols), next(nullptr) {}
};

// =========================
// Main System Class
// =========================
class StadiumTicketReservation
{
private:
    SectionNode *sectionHead;                 // Linked List for sections
    vector<vector<bool>> seats;               // 2D array for seat booking
    unordered_map<int, string> reservations;  // Hashmap for ticket storage
    stack<pair<int, int>> undoStack;          // Stack for undo functionality
    map<string, pair<int, int>> sectionSeats; // Map for max and booked seats

public:
    // Constructor
    StadiumTicketReservation();

    // Core Functionalities
    void addSection(string sectionName, pair<int, int> rowRange, pair<int, int> colRange, int maxSeats); // Add sections with row/col ranges
    void displaySections();                                                                              // Display sections with seat info
    void initializeSeats(int rows, int cols);                                                            // Initialize seats (2D array)
    void bookSeat(string sectionName, int row, int col, string name);                                    // Book seat
    void cancelSeat(string sectionName, int row, int col);                                               // Cancel seat
    void undoLastBooking();                                                                              // Undo last booking
    void viewReservations();                                                                             // View all reservations
    bool isSeatInSection(SectionNode *section, int row, int col);                                        // Validate seat location
    string getClosestSectionName(string sectionName);                                                    // Get closest section name
    int levenshteinDistance(const string &s1, const string &s2);                                         // Calculate Levenshtein distance
};

// ===========================
// Method Definitions
// ===========================

StadiumTicketReservation::StadiumTicketReservation() : sectionHead(nullptr) {}

// Add Section with fixed seating capacity
void StadiumTicketReservation::addSection(string sectionName, pair<int, int> rowRange, pair<int, int> colRange, int maxSeats)
{
    SectionNode *newNode = new SectionNode(sectionName, rowRange, colRange);
    if (!sectionHead)
    {
        sectionHead = newNode;
    }
    else
    {
        SectionNode *temp = sectionHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
    sectionSeats[sectionName] = {maxSeats, 0}; // {maxSeats, bookedSeats}
}

// Display Sections with Seat Info
void StadiumTicketReservation::displaySections()
{
    if (!sectionHead)
    {
        cout << "No sections available.\n";
        return;
    }
    SectionNode *temp = sectionHead;
    while (temp)
    {
        string name = temp->sectionName;
        auto [maxSeats, bookedSeats] = sectionSeats[name];
        int availableSeats = maxSeats - bookedSeats;
        cout << "Section: " << name << " | Total Seats: " << maxSeats
             << " | Booked: " << bookedSeats
             << " | Available: " << availableSeats
             << " | Rows: " << temp->rowRange.first << "-" << temp->rowRange.second
             << " | Columns: " << temp->colRange.first << "-" << temp->colRange.second << endl;
        temp = temp->next;
    }
}

// Initialize Seats (2D Array)
void StadiumTicketReservation::initializeSeats(int rows, int cols)
{
    seats = vector<vector<bool>>(rows, vector<bool>(cols, false));
}

// Check if Seat is in Section
bool StadiumTicketReservation::isSeatInSection(SectionNode *section, int row, int col)
{
    return row >= section->rowRange.first && row <= section->rowRange.second &&
           col >= section->colRange.first && col <= section->colRange.second;
}

// Book Seat
void StadiumTicketReservation::bookSeat(string sectionName, int row, int col, string name)
{
    SectionNode *temp = sectionHead;
    while (temp && temp->sectionName != sectionName)
        temp = temp->next;

    if (!temp)
    {
        string closestSection = getClosestSectionName(sectionName);
        cout << "Section not found. Did you mean: " << closestSection << "?\n";
        return;
    }

    if (!isSeatInSection(temp, row, col))
    {
        cout << "Error: Seat (" << row << ", " << col << ") is not in the " << sectionName << " section.\n";
        return;
    }

    if (sectionSeats[sectionName].second >= sectionSeats[sectionName].first)
    {
        cout << "No seats available in this section.\n";
        return;
    }

    if (seats[row][col])
    {
        cout << "Error: Seat already booked.\n";
        return;
    }

    seats[row][col] = true;
    undoStack.push({row, col});
    int ticketID = row * 100 + col; // Generate a unique ticket ID
    reservations[ticketID] = name;
    sectionSeats[sectionName].second++; // Increment booked seats
    cout << "Seat successfully booked in " << sectionName << " for " << name
         << ". Ticket ID: " << ticketID << ".\n";
}

// Cancel Seat
void StadiumTicketReservation::cancelSeat(string sectionName, int row, int col)
{
    SectionNode *temp = sectionHead;
    while (temp && temp->sectionName != sectionName)
        temp = temp->next;

    if (!temp)
    {
        string closestSection = getClosestSectionName(sectionName);
        cout << "Section not found. Did you mean: " << closestSection << "?\n";
        return;
    }

    int ticketID = row * 100 + col;
    if (reservations.find(ticketID) == reservations.end())
    {
        cout << "No reservation found for the seat.\n";
        return;
    }

    seats[row][col] = false;
    reservations.erase(ticketID);
    sectionSeats[sectionName].second--; // Decrement booked seats
    cout << "Seat canceled successfully in section " << sectionName << ".\n";
}

// Undo Last Booking
void StadiumTicketReservation::undoLastBooking()
{
    if (undoStack.empty())
    {
        cout << "No booking to undo.\n";
        return;
    }
    pair<int, int> lastBooking = undoStack.top();
    undoStack.pop();
    seats[lastBooking.first][lastBooking.second] = false;
    int ticketID = lastBooking.first * 100 + lastBooking.second;

    if (reservations.find(ticketID) == reservations.end())
    {
        cout << "Error: Unable to undo booking.\n";
        return;
    }

    string sectionName;
    for (auto &section : sectionSeats)
    {
        if (section.second.second > 0) // If bookings exist in section
        {
            section.second.second--;
            sectionName = section.first;
            break;
        }
    }

    reservations.erase(ticketID);
    cout << "Last booking undone for ticket ID: " << ticketID << " in section " << sectionName << ".\n";
}

// View Reservations
void StadiumTicketReservation::viewReservations()
{
    if (reservations.empty())
    {
        cout << "No reservations available.\n";
        return;
    }
    for (const auto &entry : reservations)
    {
        cout << "Ticket ID: " << entry.first << ", Name: " << entry.second << endl;
    }
}

// Calculate Levenshtein Distance
int StadiumTicketReservation::levenshteinDistance(const string &s1, const string &s2)
{
    const size_t m = s1.size();
    const size_t n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));

    for (size_t i = 0; i <= m; ++i)
        dp[i][0] = i;
    for (size_t j = 0; j <= n; ++j)
        dp[0][j] = j;

    for (size_t i = 1; i <= m; ++i)
    {
        for (size_t j = 1; j <= n; ++j)
        {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }

    return dp[m][n];
}

// Get Closest Section Name
string StadiumTicketReservation::getClosestSectionName(string sectionName)
{
    string closestSection;
    int minDistance = numeric_limits<int>::max();

    for (const auto &section : sectionSeats)
    {
        int distance = levenshteinDistance(sectionName, section.first);
        if (distance < minDistance)
        {
            minDistance = distance;
            closestSection = section.first;
        }
    }

    return closestSection;
}

// ===========================
// Main Function
// ===========================
int main()
{
    StadiumTicketReservation system;

    // Initialize seats
    system.initializeSeats(20, 20);

    // Add sections with fixed capacities
    system.addSection("North Wing", {0, 4}, {0, 9}, 50);
    system.addSection("East Wing", {5, 9}, {10, 19}, 50);
    system.addSection("West Wing", {10, 14}, {0, 9}, 50);
    system.addSection("South Wing", {15, 19}, {10, 19}, 50);
    // Main Function Continued
    int choice;
    string sectionName, name;
    int row, col;

    while (true)
    {
        cout << "\n===== Stadium Ticket Reservation System =====\n";
        cout << "1. Display Sections\n";
        cout << "2. Book Seat\n";
        cout << "3. Cancel Seat\n";
        cout << "4. Undo Last Booking\n";
        cout << "5. View Reservations\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.displaySections();
            break;

        case 2:
            cout << "Enter section name: ";
            cin.ignore();              // Ignore any leftover newline character in the input buffer
            getline(cin, sectionName); // Read the full section name, even if it contains spaces
            cout << "Enter row number: ";
            cin >> row;
            cout << "Enter column number: ";
            cin >> col;
            cout << "Enter your name: ";
            cin.ignore();       // To discard any newline left over from the previous input
            getline(cin, name); // Read the full name, including spaces
            system.bookSeat(sectionName,row,col,name);
            break;

        case 3:
            cout << "Enter section name: ";
            cin.ignore();              // Ignore any leftover newline character in the input buffer
            getline(cin, sectionName);
            cout << "Enter row number: ";
            cin >> row;
            cout << "Enter column number: ";
            cin>>col;
            system.cancelSeat(sectionName, row, col);
            break;

        case 4:
            system.undoLastBooking();
            break;

        case 5:
            system.viewReservations();
            break;

        case 6:
            cout << "Exiting the system.\n";
            return 0;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
