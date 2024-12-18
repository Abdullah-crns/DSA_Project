#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;

// Structure for each station node in the linked list
struct Station
{
    string city_name;
    int index;
    Station *next;
};

// Structure for each cabin node in the doubly linked list
struct Cabin
{
    string cabin_name;
    bool seat[10];
    Cabin *prev;
    Cabin *next;
    Cabin(string name) : cabin_name(name), prev(nullptr), next(nullptr)
    {
        for (int i = 0; i < 10; ++i)
        {
            seat[i] = false;
        }
    }
};

// Class to manage the linked list of stations and ticket reservation
class TrainTickets
{
private:
    Station *head;
    string departure_times[12][3][2];
    vector<string> booked_tickets;
    vector<string> booked_ticket_time_slots;
    string user_name;
    map<int, Cabin *> route_cabins;

public:
    TrainTickets() : head(nullptr), user_name("") {}

    void addStation(string city, int index)
    {
        Station *newStation = new Station();
        newStation->city_name = city;
        newStation->index = index;
        newStation->next = nullptr;

        if (head == nullptr)
        {
            head = newStation;
        }
        else
        {
            Station *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newStation;
        }
    }

    // Function to create a doubly linked list of cabins
    Cabin *createCabinList()
    {
        Cabin *head = new Cabin("Cabin A");
        Cabin *current = head;
        current->next = new Cabin("Cabin B");
        current->next->prev = current;
        current = current->next;
        current->next = new Cabin("Cabin C");
        current->next->prev = current;
        current = current->next;
        current->next = new Cabin("Cabin D");
        current->next->prev = current;
        current = current->next;
        current->next = new Cabin("Cabin E");
        current->next->prev = current;
        current = current->next;
        current->next = new Cabin("Cabin F");
        current->next->prev = current;
        current = current->next;
        current->next = new Cabin("Cabin G");
        current->next->prev = current;
        return head;
    }

    pair<int, string> assignSeat(Cabin *head)
    {
        Cabin *current = head;
        while (current != nullptr)
        {
            for (int i = 0; i < 10; ++i)
            {
                if (!current->seat[i])
                {
                    current->seat[i] = true;
                    return {i + 1, current->cabin_name};
                }
            }
            current = current->next;
        }
        return {-1, ""};
    }

    void createRouteCabins(int routeIndex)
    {
        route_cabins[routeIndex] = createCabinList();
    }

    void bookTicket(int currentStationIndex, int destinationStationIndex, int timeSlot)
    {
        int distance = calculateDistance(currentStationIndex, destinationStationIndex);
        if (distance == 0)
        {
            cout << "Invalid route selected.\n";
            return;
        }

        if (timeSlot < 0 || timeSlot >= 3)
        {
            cout << "Invalid time slot selected.\n";
            return;
        }

        cout << "ENTER YOUR NAME : ";
        cin.ignore();
        getline(cin, user_name);

        string current_station = getCityNameByIndex(currentStationIndex);
        string destination_city = getCityNameByIndex(destinationStationIndex);
        string departure_time = departure_times[currentStationIndex][timeSlot][0];
        string departure_date = departure_times[currentStationIndex][timeSlot][1];

        pair<int, string> seatAssignment = {-1, ""};

        int routeIndex = currentStationIndex * 12 + destinationStationIndex;
        if (route_cabins.find(routeIndex) == route_cabins.end())
        {
            createRouteCabins(routeIndex);
        }

        Cabin *cabins = route_cabins[routeIndex];
        seatAssignment = assignSeat(cabins);

        if (seatAssignment.first == -1)
        {
            cout << "SORRY ALL THE SEATS ARE BOOKED IN THE CABIN.\n";
            return;
        }
        else
        {
            cout << "YOUR SEAT HAS BEEN ASSIGNED SUCCESSFULLY!\n";
        }

        string booked_ticket = "-------------------------------\n|NAME       |: " + user_name + "  \n" +
                               "|DEPARTURE     |: " + current_station + "  \n" +
                               "|DESTINATION   |: " + destination_city + "  \n" +
                               "|DEPARTURE TIME|: " + departure_time + "  \n" +
                               "|DEPARTURE DATE|: " + departure_date + "  \n" +
                               "|DISTANCE      |: " + to_string(distance) + " km  \n" +
                               "|ROUTE FARE    |: " + to_string(distance * 3.5) + "Rs \n" +
                               "|CABIN         |: " + seatAssignment.second + "  \n" +
                               "|SEAT NUMBER   |: " + to_string(seatAssignment.first) + "  \n" +
                               "-------------------------------\n";

        time_t now = time(0);
        tm *ltm = localtime(&now);
        ltm->tm_min += 90;
        mktime(ltm);
        string booked_ticket_time_slot = "---------------------------\n|Ticket Valid Till: " +
                                         to_string(ltm->tm_hour) + ":" +
                                         (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min) + " |\n---------------------------";

        booked_tickets.push_back(booked_ticket);
        booked_ticket_time_slots.push_back(booked_ticket_time_slot);

        cout << "----------------------------------------\n";
        cout << "TICKET HAS BEEN BOOKED SUCCESSFULLY!\n";
    }

    void displayStations()
    {
        if (head == nullptr)
        {
            cout << "No stations available.\n";
            return;
        }

        Station *temp = head;
        cout << "Available Stations:\n";
        while (temp != nullptr)
        {
            cout << temp->index + 1 << " . " << temp->city_name << "\n";
            temp = temp->next;
        }
    }

    int calculateDistance(int currentIndex, int destinationIndex)
    {
        return abs(currentIndex - destinationIndex) * 100;
    }

    void showAvailableTimes(int currentStationIndex, int destinationStationIndex)
    {
        cout << "Available Departure Times from " << getCityNameByIndex(currentStationIndex) << " to "
             << getCityNameByIndex(destinationStationIndex) << ":\n";
        for (int i = 0; i < 3; ++i)
        {
            cout << i + 1 << ". Time: " << departure_times[currentStationIndex][i][0]
                 << ", Date: " << departure_times[currentStationIndex][i][1] << "\n";
        }
    }

    void viewTickets()
    {
        if (booked_tickets.empty())
        {
            cout << "No tickets are booked.\n";
        }
        else
        {
            cout << "All Booked Tickets:\n";
            for (size_t i = 0; i < booked_tickets.size(); ++i)
            {
                cout << "Ticket " << i + 1 << ":\n";
                cout << booked_tickets[i];
                cout << booked_ticket_time_slots[i] << "\n";
            }
        }
    }

    string getCityNameByIndex(int index)
    {
        Station *temp = head;
        while (temp != nullptr)
        {
            if (temp->index == index)
            {
                return temp->city_name;
            }
            temp = temp->next;
        }
        return "";
    }

    void setDepartureTime(int stationIndex, int timeSlot)
    {
        int base_hour = 6;
        int base_minute = 0;
        int base_day = 1;

        int hour = base_hour + (stationIndex * 3 + timeSlot) % 12;
        int minute = base_minute + (stationIndex * 15 + timeSlot * 5) % 60;
        int day = base_day + (stationIndex * 3 + timeSlot) % 30;

        string hour_str = to_string(hour);
        string minute_str = (minute < 10) ? "0" + to_string(minute) : to_string(minute);
        string time_str = hour_str + ":" + minute_str;

        departure_times[stationIndex][timeSlot][0] = time_str;
        departure_times[stationIndex][timeSlot][1] = to_string(day) + "/12/2024";
    }
    void deleteBooking()
    {

        if (!booked_tickets.empty())
        {
            int ticketIndex1, ticketIndex;
            cout << "Enter the ticket index to delete: ";
            cin >> ticketIndex1;
            ticketIndex = ticketIndex1 - 1;
            if (ticketIndex < 0 || ticketIndex >= booked_tickets.size())
            {
                cout << "Invalid ticket index.\n";
                return;
            }

            // Find the corresponding seat and cabin
            string ticketDetails = booked_tickets[ticketIndex];
            size_t seatPos = ticketDetails.find("|SEAT NUMBER   |: ");
            if (seatPos != string::npos)
            {
                size_t seatEnd = ticketDetails.find("  \n", seatPos);
                string seatNumberStr = ticketDetails.substr(seatPos + 16, seatEnd - seatPos - 16);
                int seatNumber = stoi(seatNumberStr);

                // Find the cabin by checking seat assignment
                string cabinName;
                size_t cabinPos = ticketDetails.find("|CABIN         |: ");
                if (cabinPos != string::npos)
                {
                    size_t cabinEnd = ticketDetails.find("  \n", cabinPos);
                    cabinName = ticketDetails.substr(cabinPos + 15, cabinEnd - cabinPos - 15);
                }

                // Find the corresponding cabin and free the seat
                for (auto &route : route_cabins)
                {
                    Cabin *current = route.second;
                    while (current != nullptr)
                    {
                        if (current->cabin_name == cabinName && current->seat[seatNumber - 1])
                        {
                            current->seat[seatNumber - 1] = false;
                            cout << "Seat " << seatNumber << " in " << cabinName << " has been freed.\n";
                            break;
                        }
                        current = current->next;
                    }
                }
            }

            // Remove the ticket and time slot from the vectors
            booked_tickets.erase(booked_tickets.begin() + ticketIndex);
            booked_ticket_time_slots.erase(booked_ticket_time_slots.begin() + ticketIndex);

            cout << "BOOKING HAS BEEN DELETED SUCCESSFULY.\n";
        }
        else
        {
            cout << "NO BOOKING YET " << endl;
            return;
        }
    }
};

int main()
{
    TrainTickets ticketSystem;

    ticketSystem.addStation("PESHAWAR", 0);
    ticketSystem.addStation("TOPI", 1);
    ticketSystem.addStation("ISLAMABAD", 2);
    ticketSystem.addStation("SARGODHA", 3);
    ticketSystem.addStation("FAISLABAD", 4);
    ticketSystem.addStation("LAHORE", 5);
    ticketSystem.addStation("GUJRANWALA", 6);
    ticketSystem.addStation("MULTAN", 7);
    ticketSystem.addStation("BAHAWALPUR", 8);
    ticketSystem.addStation("SUKKUR", 9);
    ticketSystem.addStation("HYDERABAD", 10);
    ticketSystem.addStation("KARACHI", 11);

    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            ticketSystem.setDepartureTime(i, j);
        }
    }

    int choice;
    do
    {
        cout << "1. DISPLAY ROUTES\n";
        cout << "2. BOOK TICKETS\n";
        cout << "3. VIEW BOOKED TICKETS\n";
        cout << "4. DELETE BOOKING\n"; // Add delete option
        cout << "5. EXIT\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            ticketSystem.displayStations();
            break;
        case 2:
        {
            int currentStation, destinationStation, timeSlot;
            ticketSystem.displayStations();
            cout << "ENTER YOUR CURRENT STATION NUMBER : ";
            cin >> currentStation;
            cout << "ENTER YOUR DESTINATION NUMBER : ";
            cin >> destinationStation;
            ticketSystem.showAvailableTimes(currentStation - 1, destinationStation - 1);
            cout << "ENTER TIME SLOT : ";
            cin >> timeSlot;
            ticketSystem.bookTicket(currentStation - 1, destinationStation - 1, timeSlot - 1);
            break;
        }
        case 3:
            ticketSystem.viewTickets();
            break;
        case 4:
            ticketSystem.deleteBooking(); // Adjust for 0-based index
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
