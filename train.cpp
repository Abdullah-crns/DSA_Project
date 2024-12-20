#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Structure for linked list node (Stations)
struct Station
{
    string name;
    unordered_map<string, double> distances; // Distances to connected stations
    Station *next;
};
struct Seats
{
    string seat_no; // Seat number
    bool isbooked;  // Seat booked status
};
struct Cabins
{
    Seats seats[6];  // 6 seats per cabin
    string cabin_no; // Cabin number
    bool isbooked;   // Cabin booked status
};
struct Coaches
{
    Cabins cabins[12]; // 12 cabins per coach
    bool isbooked;     // Coach booked status
    string Coach_no;   // Coach number
};
// Structure for tree node (Seats and Cabins)
struct Reservation
{
    string ticketID;
    double price;
    string departureStation;
    string arrivalStation;
    string name;
    string gender;
    Reservation *left;
    Reservation *right;
    Seats seats;
    Cabins cabins;
    Coaches Coach_no[15];
};

// Class for Train Ticket Reservation System
class TrainSystem
{
private:
    Station *stationHead;                                // Linked list for stations
    Reservation *reservationRoot;                        // Binary Search Tree for reservations
    unordered_map<string, Reservation *> reservationMap; // Map for quick ticket lookup

    // Generate unique ticket ID
    string generateUniqueID()
    {
        srand(time(0));
        return "TICKET-" + to_string(rand() % 10000 + 1);
    }

    // Insert reservation into BST
    Reservation *insertReservation(Reservation *root, Reservation *newReservation)
    {
        if (!root)
            return newReservation;
        if (newReservation->ticketID < root->ticketID)
            root->left = insertReservation(root->left, newReservation);
        else
            root->right = insertReservation(root->right, newReservation);
        return root;
    }

    // Find and delete reservation from BST
    Reservation *deleteReservation(Reservation *root, string ticketID)
    {
        if (!root)
            return nullptr;
        if (ticketID < root->ticketID)
            root->left = deleteReservation(root->left, ticketID);
        else if (ticketID > root->ticketID)
            root->right = deleteReservation(root->right, ticketID);
        else
        {
            if (!root->left)
            {
                Reservation *temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                Reservation *temp = root->left;
                delete root;
                return temp;
            }

            // Find in-order successor
            Reservation *temp = root->right;
            while (temp && temp->left)
                temp = temp->left;

            root->ticketID = temp->ticketID;
            root->departureStation = temp->departureStation;
            root->arrivalStation = temp->arrivalStation;
            root->price = temp->price;

            root->right = deleteReservation(root->right, temp->ticketID);
        }
        return root;
    }

    // In-order traversal to display reservations
    void displayReservationsInOrder(Reservation *root)
    {
        if (!root)
            return;

        displayReservationsInOrder(root->left);
        for (int i = 0; i < 15; i++)
        {
            if (root->Coach_no[i].isbooked)
            {
                cout << "========================================\n";
                cout << "            COACH RESERVATION           \n";
                cout << "========================================\n";
                cout << "| TICKET ID:            | " << root->ticketID << endl;
                cout << "| NAME:                 | " << root->name << endl;
                cout << "| GENDER:               | " << root->gender << endl;
                cout << "| STATION OF DEPARTURE: | " << root->departureStation << endl;
                cout << "| STATION OF ARRIVAL:   | " << root->arrivalStation << endl;
                cout << "| COACH NUMBER:         | " << i + 1 << endl;
                cout << "| PRICE:                | " << (root->price) * (72) << " PKR\n";
                cout << "========================================\n";
            }
        }
        for (int i = 0; i < 15; i++)
        {
            if (root->Coach_no[i].isbooked == false)
            {
                for (int j = 0; j < 12; j++)
                {
                    if (root->Coach_no[i].cabins[j].isbooked == true)
                    {
                        cout << "========================================\n";
                        cout << "            CABIN RESERVATION           \n";
                        cout << "========================================\n";
                        cout << "| TICKET ID:            | " << root->ticketID << endl;
                        cout << "| NAME:                 | " << root->name << endl;
                        cout << "| GENDER:               | " << root->gender << endl;
                        cout << "| STATION OF DEPARTURE: | " << root->departureStation << endl;
                        cout << "| STATION OF ARRIVAL:   | " << root->arrivalStation << endl;
                        cout << "| COACH NUMBER:         | " << i + 1 << endl;
                        cout << "| CABIN NUMBER:         | " << j + 1 << endl;
                        cout << "| PRICE:                | " << (root->price) * 6 << " PKR\n";
                        cout << "========================================\n";
                    }
                }
            }
        }
        for (int i = 0; i < 15; i++)
        {
            if (root->Coach_no[i].isbooked == false)
            {
                for (int j = 0; j < 12; j++)
                {
                    if (root->Coach_no[i].cabins[j].isbooked == false)
                    {
                        for (int k = 0; k < 6; k++)
                        {
                            if (root->Coach_no[i].cabins[j].seats[k].isbooked)
                            {
                                cout << "========================================\n";
                                cout << "| TICKET ID:            | " << root->ticketID << endl;
                                cout << "| NAME:                 | " << root->name << endl;
                                cout << "| GENDER:               | " << root->gender << endl;
                                cout << "| STATION OF DEPARTURE: | " << root->departureStation << endl;
                                cout << "| STATION OF ARRIVAL:   | " << root->arrivalStation << endl;
                                cout << "| COACH NUMBER:         | " << i + 1 << endl;
                                cout << "| CABIN NUMBER:         | " << j + 1 << endl;
                                cout << "| SEAT NUMBER:          | " << k + 1 << endl;
                                cout << "| PRICE:                | " << root->price << " pkr\n";
                                cout << "========================================\n";
                            }
                        }
                    }
                }
            }
        }

        displayReservationsInOrder(root->right);
    }

public:
    TrainSystem() : stationHead(nullptr), reservationRoot(nullptr) {}

    // Admin: Add station to the linked list
    void addStation(const string &name, const unordered_map<string, double> &distances)
    {
        Station *newStation = new Station{name, distances, nullptr};
        if (!stationHead)
        {
            stationHead = newStation;
            return;
        }
        Station *temp = stationHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newStation;

        // Now ensure the connection is bidirectional by adding reverse connections
        for (const auto &pair : distances)
        {
            string connectedStation = pair.first;
            double distance = pair.second;

            // Find the connected station in the list
            Station *connectedStationNode = stationHead;
            while (connectedStationNode && connectedStationNode->name != connectedStation)
                connectedStationNode = connectedStationNode->next;

            if (connectedStationNode)
            {
                // Add reverse connection (connectedStation -> station)
                connectedStationNode->distances[name] = distance;
            }
        }
    }

    // Admin: Display all stations
    void displayStations()
    {
        Station *temp = stationHead;
        if (!temp)
        {
            cout << "No stations available.\n";
            return;
        }
        cout << "==========================\n";
        cout << "AVAILABLE STATIONS:\n";
        cout << "==========================\n";
        while (temp)
        {
            cout << "- " << temp->name << "\n";
            temp = temp->next;
        }
        cout << "==========================\n";
    }

    // Admin: Edit a station
    void editStation()
    {
        displayStations();
        string stationName;
        cout << "Enter the name of the station to edit: ";
        cin >> stationName;

        Station *temp = stationHead;
        while (temp && temp->name != stationName)
            temp = temp->next;

        if (!temp)
        {
            cout << "Station not found.\n";
            return;
        }

        cout << "Editing distances for station: " << stationName << endl;
        for (auto &pair : temp->distances)
        {
            cout << "Enter distance to " << pair.first << " (current: " << pair.second << " km): ";
            cin >> pair.second;
        }
        cout << "Station distances updated successfully.\n";
    }

    // User: Reserve a ticket
    void reserveTicket()
    {
        displayStations();
        string departureStation, arrivalStation, name, gender;
        int coach_number, cabin_number, seat_number;
        Coaches Coach_no[15];

        cout << "ENTER YOUR CURRENT STATION NAME: \n";
        cout << "=================================\n";
        cin >> departureStation;
        cout << "=================================\n";

        // Find the departure station in the linked list
        Station *departureNode = stationHead;
        while (departureNode && departureNode->name != departureStation)
        {
            departureNode = departureNode->next;
        }

        // Check if the departure station exists
        if (!departureNode)
        {
            cout << "STATION NOT FOUND [please try again]\n";
            return;
        }

        // Display the list of connected cities for the departure station
        cout << "CITIES CONNECTED TO " << departureStation << ":\n";
        cout << "==============================\n";
        for (const auto &pair : departureNode->distances)
        {
            cout << "- " << pair.first << "\n"; // Display connected cities
        }

        cout << "ENTER YOUR DESTINATION FROM THE ABOVE LIST : ";
        cin >> arrivalStation;

        // Check if the arrival station exists in the connected cities
        if (departureNode->distances.find(arrivalStation) == departureNode->distances.end())
        {
            cout << "INVALID DESTINATION [please try again].\n";
            return;
        }
        double distance = departureNode->distances[arrivalStation];
        double prices = distance * 11.67; // Price per km

        // Generate a unique ticket ID
        string ticketID = generateUniqueID();

        cout << "ENTER YOUR NAME: ";
        cin >> name;
        cout << "EnNTER YOUR GENDER: ";
        cin >> gender;

        int reservation_option;
        cout << "======================================\n";
        cout << "1. RESERVE A SEAT" << endl;
        cout << "2. RESERVE A CABIN [family seat]" << endl;
        cout << "3. RESERVE A COACH" << endl;
        cout << "======================================\n";
        cout << "PLEASE ENTER YOUR RESERVATION OPTION : ";
        cout << "======================================\n";
        cin >> reservation_option;

        if (reservation_option == 1)
        {
            cout << "AVAILABLE COACHES" << endl;
            for (int i = 0; i < 15; i++)
            {
                if (!Coach_no[i].isbooked)
                {
                    cout << "| COACH NUMBER : " << i + 1 << " |" << endl;
                }
            }

            cout << "--------------------------------------\n";
            cout << "PLEASE ENTER THE COACH NUMBER : ";
            cin >> coach_number;

            if (coach_number < 1 || coach_number > 15)
            {
                cout << "INVALID COACH NUMBER [please enter a number from the above given list]\n";
                return;
            }

            cout << "Available Cabins" << endl;
            for (int i = 0; i < 12; i++)
            {
                if (!Coach_no[coach_number - 1].cabins[i].isbooked)
                {
                    cout << "Cabin Number: " << i + 1 << endl;
                }
            }

            cout << "--------------------------------------\n";
            cout << "PLEASE ENTER THE CABIN NUMBER: ";
            cin >> cabin_number;

            if (cabin_number < 1 || cabin_number > 12)
            {
                cout << "INVALID CABIN NUMBER\n";
                return;
            }

            cout << "Available Seats" << endl;
            for (int i = 0; i < 6; i++)
            {
                if (!Coach_no[coach_number - 1].cabins[cabin_number - 1].seats[i].isbooked)
                {
                    cout << "SEAT NUMBER: " << i + 1 << endl;
                }
            }

            cout << "PLEASE ENTER THE SEAT NUMBER: ";
            cin >> seat_number;

            if (seat_number < 1 || seat_number > 6)
            {
                cout << "INVALID SEAT NUMBER\n";
                return;
            }

            // Mark seat as booked
            Coach_no[coach_number - 1].cabins[cabin_number - 1].seats[seat_number - 1].isbooked = true;

            // Create a new reservation
            Reservation *newReservation = new Reservation{
                ticketID,
                prices,
                departureStation,
                arrivalStation,
                name,
                gender,
                nullptr,
                nullptr,
                Coach_no[coach_number - 1].cabins[cabin_number - 1].seats[seat_number - 1],
                Coach_no[coach_number - 1].cabins[cabin_number - 1],
                Coach_no[coach_number - 1]};

            // Insert the reservation into the BST
            reservationRoot = insertReservation(reservationRoot, newReservation);
            reservationMap[ticketID] = newReservation;
        }
        else if (reservation_option == 2)
        {
            cout << "--------------------------------------\n";
            cout << "AVAILABLE COACHES" << endl;
            for (int i = 0; i < 15; i++)
            {
                if (!Coach_no[i].isbooked)
                {
                    cout << "| COACH NUMBER: " << i + 1 << " |" << endl;
                }
            }

            cout << "--------------------------------------\n";
            cout << "PLEASE ENTER THE COACH NUMBER: ";
            cin >> coach_number;

            if (coach_number < 1 || coach_number > 15)
            {
                cout << "INVALID COACH NUMBER\n";
                return;
            }

            cout << "AVAILABLE CABINS IN COACH " << coach_number << endl;
            for (int i = 0; i < 12; i++)
            {
                if (!Coach_no[coach_number - 1].cabins[i].isbooked)
                {
                    cout << "CABIN NUMBER: " << i + 1 << endl;
                }
            }

            cout << "--------------------------------------\n";
            cout << "PLEASE ENTER THE CABIN NUMBER: ";
            cin >> cabin_number;

            if (cabin_number < 1 || cabin_number > 12)
            {
                cout << "INVALID CABIN NUMBER\n";
                return;
            }
            Coach_no[coach_number - 1].cabins[cabin_number - 1].isbooked = true;
            Seats seat;
            Reservation *newReservation = new Reservation{
                ticketID,
                prices,
                departureStation,
                arrivalStation,
                name,
                gender,
                nullptr,
                nullptr,
                seat,
                Coach_no[coach_number - 1].cabins[cabin_number - 1],
                Coach_no[coach_number - 1]};

            // Insert the reservation into the BST
            reservationRoot = insertReservation(reservationRoot, newReservation);
            reservationMap[ticketID] = newReservation;
        }
        else if (reservation_option == 3)
        {
            cout << "AVAILABLE COACHES" << endl;
            for (int i = 0; i < 15; i++)
            {
                if (!Coach_no[i].isbooked)
                {
                    cout << "COACH NUMBER: " << i + 1 << endl;
                }
            }

            cout << "PLEASE ENTER THE COACH NUMBER: ";
            cin >> coach_number;

            if (coach_number < 1 || coach_number > 15)
            {
                cout << "INVALID COACH NUMBER\n";
                return;
            }
            Seats seat;
            Cabins cabin;
            Coach_no[coach_number - 1].isbooked = true;
            Reservation *newReservation = new Reservation{
                ticketID,
                prices,
                departureStation,
                arrivalStation,
                name,
                gender,
                nullptr,
                nullptr,
                seat,
                cabin,
                Coach_no[coach_number - 1]};

            // Insert the reservation into the BST
            reservationRoot = insertReservation(reservationRoot, newReservation);
            reservationMap[ticketID] = newReservation;
        }
        else
        {
            cout << "INVALID RESERVATION OPTION" << endl;
            return;
        }

        // Calculate the distance and price

        // Display the reservation details
        cout << "TICKET RESERVED SUCCESSFULY!\n";
        cout << "========================================\n";
        cout << "| TICKET ID:         | " << ticketID << endl;
        cout << "| NAME:              | " << name << endl;
        cout << "| GENDER:            | " << gender << endl;
        cout << "| DEPARTURE STATION: | " << departureStation << endl;
        cout << "| ARRIVAL STATION:   | " << arrivalStation << endl;
        cout << "| DISTANCE:          | " << distance << " km\n";
        cout << "| PRICE:             | " << prices << " PKR\n";
        cout << "| COACH NUMBER:      | " << coach_number << endl;
        cout << "| CABIN NUMBER:      | " << cabin_number << endl;
        cout << "| SEAT NUMBER:       | " << seat_number << endl;
        cout << "| DISTANCE:          | " << distance << " PKR\n";
        cout << "========================================\n";
    }

    // User: Delete a reservation
    void
    deleteTicket()
    {
        string ticketID;
        cout << "ENTER THE TICKET ID TO DELETE IT: ";
        cin >> ticketID;

        if (reservationMap.find(ticketID) == reservationMap.end())
        {
            cout << "NO TICKET FOUND WITH ID : " << ticketID << ".\n";
            return;
        }

        reservationRoot = deleteReservation(reservationRoot, ticketID);
        reservationMap.erase(ticketID);
        cout << "RESERVATION WITH TICKET ID " << ticketID << " DELETED SUCCESSFULLY.\n";
    }

    // User: Display all reservations
    void displayReservations()
    {
        if (!reservationRoot)
        {
            cout << "NO RESERVATIONS FOUND.\n";
            return;
        }
        displayReservationsInOrder(reservationRoot);
    }
};

// Main function
int main()
{
    TrainSystem system;

    // Initial stations setup
    system.addStation("Karachi", {{"Lahore", 1211}, {"Islamabad", 1411}, {"Quetta", 683.7}, {"Sukkur", 474.5}, {"Multan", 1053.7}, {"Faisalabad", 1281.7}, {"Peshawar", 1483.7}, {"Hyderabad", 163.7}, {"Gwadar", 653.7}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Lahore", {{"Karachi", 1211}, {"Islamabad", 375}, {"Faisalabad", 128}, {"Multan", 331}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Peshawar", 189}, {"Sukkur", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sargodha", 1411}});
    system.addStation("Islamabad", {{"Lahore", 375}, {"Peshawar", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Peshawar", {{"Islamabad", 189}, {"Lahore", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Quetta", {{"Karachi", 683.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Multan", {{"Karachi", 1053.7}, {"Lahore", 331}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Faisalabad", {{"Karachi", 1281.7}, {"Lahore", 128}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Sukkur", {{"Karachi", 474.5}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Hyderabad", {{"Karachi", 163.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Sukkur", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    system.addStation("Gwadar", {{"Karachi", 653.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Sukkur", 1411}});
    int roleChoice;
    do
    {
        cout << "\n1. Admin Panel\n2. User Panel\n3. Exit\nSelect your role: ";
        cin >> roleChoice;

        if (roleChoice == 1)
        {
            int adminChoice;
            do
            {
                cout << "\nAdmin Panel:\n1. Add Station\n2. Edit Station\n3. Display Stations\n4. Exit\nSelect an option: ";
                cin >> adminChoice;

                switch (adminChoice)
                {
                case 1:
                {
                    unordered_map<string, double> distances;
                    string station_name;
                    int connections;

                    cout << "Enter station name: ";
                    cin.ignore(); // Clear the input buffer to handle the next getline properly
                    getline(cin, station_name);

                    cout << "Enter number of connections: ";
                    cin >> connections;

                    for (int i = 0; i < connections; ++i)
                    {
                        string connectedStation;
                        double distance;
                        cout << "Enter connected station name and distance: ";
                        cin >> connectedStation >> distance;
                        distances[connectedStation] = distance;
                    }

                    system.addStation(station_name, distances);
                    cout << "Station " << station_name << " added successfully.\n";
                }
                break;
                case 2:
                    system.editStation();
                    break;
                case 3:
                    system.displayStations();
                    break;
                case 4:
                    cout << "Exiting Admin Panel.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (adminChoice != 4);
        }
        else if (roleChoice == 2)
        {
            int userChoice;
            do
            {
                cout << "========================================\n";
                cout << "        TRAIN TICKET RESERVATION        \n";
                cout << "========================================\n";
                cout << "1. Reserve Ticket\n2. Delete Ticket\n3. View Reservations\n4. Exit\n";
                cout << "========================================\n";
                cout << "Select an option: ";
                cin >> userChoice;

                switch (userChoice)
                {
                case 1:
                    system.reserveTicket();
                    break;
                case 2:
                    system.deleteTicket();
                    break;
                case 3:
                    system.displayReservations();
                    break;
                case 4:
                    cout << "EXITING THE TRAIN TICKET RESERVATION PANEL.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (userChoice != 4);
        }
        else if (roleChoice != 3)
        {
            cout << "Invalid role. Try again.\n";
        }
    } while (roleChoice != 3);

    cout << "Exiting the system. Goodbye!\n";
    return 0;
}
