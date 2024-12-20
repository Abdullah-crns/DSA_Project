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

// Structure for tree node (Seats and Cabins)
struct Reservation
{
    string ticketID;
    string departureStation;
    string arrivalStation;
    string name;
    string gender;
    double price;
    Reservation *left;
    Reservation *right;
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
        cout << "========================================\n";
        cout << "| Ticket ID:         | " << root->ticketID << endl;
        cout << "| Name:              | " << root->name << endl;
        cout << "| Gender:            | " << root->gender << endl;
        cout << "| Departure Station: | " << root->departureStation << endl;
        cout << "| Arrival Station:   | " << root->arrivalStation << endl;
        cout << "| Price:             | " << root->price << " PKR\n";
        cout << "========================================\n";
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
        cout << "Available Stations:\n";
        while (temp)
        {
            cout << "- " << temp->name << "\n";
            temp = temp->next;
        }
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

        cout << "Enter your departure station: ";
        cin >> departureStation;

        // Find the departure station in the linked list
        Station *departureNode = stationHead;
        while (departureNode && departureNode->name != departureStation)
        {
            departureNode = departureNode->next;
        }

        // Check if the departure station exists
        if (!departureNode)
        {
            cout << "Departure station not found. Please try again.\n";
            return;
        }

        // Display the list of connected cities for the departure station
        cout << "Cities connected to " << departureStation << ":\n";
        for (const auto &pair : departureNode->distances)
        {
            cout << "- " << pair.first << "\n"; // Display connected cities
        }

        cout << "Enter your arrival station from the above list: ";
        cin >> arrivalStation;

        // Check if the arrival station exists in the connected cities
        if (departureNode->distances.find(arrivalStation) == departureNode->distances.end())
        {
            cout << "Invalid arrival station. Please try again.\n";
            return;
        }

        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your gender: ";
        cin >> gender;

        // Calculate the distance and price
        double distance = departureNode->distances[arrivalStation];
        double price = distance * 11.67; // Price per km

        // Generate a unique ticket ID
        string ticketID = generateUniqueID();

        // Create a new reservation
        Reservation *newReservation = new Reservation{
            ticketID, departureStation, arrivalStation, name, gender, price, nullptr, nullptr};

        // Insert the reservation into the BST
        reservationRoot = insertReservation(reservationRoot, newReservation);
        reservationMap[ticketID] = newReservation;

        // Display the reservation details
        cout << "Ticket Reserved Successfully!\n";
        cout << "========================================\n";
        cout << "| Ticket ID:         | " << ticketID << endl;
        cout << "| Name:              | " << name << endl;
        cout << "| Gender:            | " << gender << endl;
        cout << "| Departure Station: | " << departureStation << endl;
        cout << "| Arrival Station:   | " << arrivalStation << endl;
        cout << "| Distance:          | " << distance << " km\n";
        cout << "| Price:             | " << price << " PKR\n";
        cout << "========================================\n";
    }

    // User: Delete a reservation
    void
    deleteTicket()
    {
        string ticketID;
        cout << "Enter Ticket ID to delete: ";
        cin >> ticketID;

        if (reservationMap.find(ticketID) == reservationMap.end())
        {
            cout << "No ticket found with ID " << ticketID << ".\n";
            return;
        }

        reservationRoot = deleteReservation(reservationRoot, ticketID);
        reservationMap.erase(ticketID);
        cout << "Reservation with Ticket ID " << ticketID << " deleted successfully.\n";
    }

    // User: Display all reservations
    void displayReservations()
    {
        if (!reservationRoot)
        {
            cout << "No reservations found.\n";
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
                cout << "\nUser Panel:\n1. Reserve Ticket\n2. Delete Ticket\n3. View Reservations\n4. Exit\nSelect an option: ";
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
                    cout << "Exiting User Panel.\n";
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
