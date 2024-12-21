#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <list>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

//==========================================================================TRAIN Reservation_TrainSYSTEM=======================================================================

//------------------------------------------
// Structure for linked list node (Stations)
//------------------------------------------

struct Station
{
    string name;                             // Name of the station
    unordered_map<string, double> distances; // Distances to connected stations
    Station *next;                           // Pointer to the next station
};

//--------------------
// Structure for Seats
//--------------------

struct Seats
{
    string seat_no; // Seat number
    bool isbooked;  // Seat booked status
};

//---------------------
// Structure for Cabins
//---------------------

struct Cabins
{
    Seats seats[6];  // 6 seats per cabin
    string cabin_no; // Cabin number
    bool isbooked;   // Cabin booked status
};

//----------------------------------------------------------------
// Structure for each coach of a train(every train has 15 coaches)
//----------------------------------------------------------------

struct Coaches
{
    Cabins cabins[12]; // 12 cabins per coach
    bool isbooked;     // Coach booked status
    string Coach_no;   // Coach number
};

//--------------------------------------------
// Structure for tree node (Seats and Cabins)
//--------------------------------------------

struct Reservation_Train
{
    string ticketID;
    double price;
    string departureStation;
    string arrivalStation;
    string name;
    string gender;
    Reservation_Train *left;
    Reservation_Train *right;
    Seats seats;
    Cabins cabins;
    Coaches Coach_no[15];
};

//===========================================================================================================================================================================
//                                                           CLASS FOR TRAIN TICKET Reservation_TrainSYSTEM
//===========================================================================================================================================================================
class TrainSystem
{
private:
    Station *stationHead;                                      // Linked list for stations
    Reservation_Train *reservationRoot;                        // Binary Search Tree for reservations
    unordered_map<string, Reservation_Train *> reservationMap; // Map for quick ticket lookup

    // FUNCTION TO GENERATE A UNIQUE TICKET ID FOR EACH TICKET
    string generateUniqueID()
    {
        srand(time(0));
        return "TICKET-" + to_string(rand() % 10000 + 1);
    }

    // FUNCTION FOR INSERTION INTO THE THE Reservation_TrainNODES OF THE BINARY SEARCH TREE
    Reservation_Train *insertReservation(Reservation_Train *root, Reservation_Train *newReservation)
    {
        if (!root)
            return newReservation;
        if (newReservation->ticketID < root->ticketID)
            root->left = insertReservation(root->left, newReservation);
        else
            root->right = insertReservation(root->right, newReservation);
        return root;
    }

    // FUNCTION TO DELETE A Reservation_TrainFROM THE BINARY SEARCH TREE
    Reservation_Train *deleteReservation(Reservation_Train *root, string ticketID)
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
                Reservation_Train *temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                Reservation_Train *temp = root->left;
                delete root;
                return temp;
            }

            // Find in-order successor
            Reservation_Train *temp = root->right;
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

    // FUNCTION TO DISPLAY RESERVATIONS IN ORDER
    void displayReservationsInOrder(Reservation_Train *root)
    {
        if (!root)
            return;

        displayReservationsInOrder(root->left);
        for (int i = 0; i < 15; i++)
        {
            if (root->Coach_no[i].isbooked)
            {
                cout << "========================================\n";
                cout << "            COACH Reservation_Train          \n";
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
                        cout << "            CABIN Reservation_Train          \n";
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
    // CONSTUCTOR
    TrainSystem() : stationHead(nullptr), reservationRoot(nullptr) {}

    //===========================================================================ADMIN FUNCTIONS================================================================================================

    //================================================================
    // 1. FUNCTION FOR THE ADMIN TO ADD A PARTICULAR STATION HE DESIRES
    //================================================================

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

        // NOW ENSURE THAT THE CONNECTIONS ARE BIDIRECTIONAL
        for (const auto &pair : distances)
        {
            string connectedStation = pair.first;
            double distance = pair.second;

            // FINDING THE CONNECTED STATION
            Station *connectedStationNode = stationHead;
            while (connectedStationNode && connectedStationNode->name != connectedStation)
                connectedStationNode = connectedStationNode->next;

            if (connectedStationNode)
            {
                // ADDING THE REVERSE CONNECTION
                connectedStationNode->distances[name] = distance;
            }
        }
    }

    //====================================================
    // 2. FUNCTION TO DISPLAY ALL THE STATIONS BY THE ADMIN
    //====================================================

    void displayStations()
    {
        Station *temp = stationHead;
        if (!temp)
        {
            cout << "No stations available.\n";
            return;
        }
        cout << "========================================\n";
        cout << "          AVAILABLE STATIONS:\n";
        cout << "========================================\n";
        while (temp)
        {
            cout << "- " << temp->name << "\n";
            temp = temp->next;
        }
        cout << "========================================\n";
    }

    //=====================================================
    // 3. FUNCTION TO EDIT A PARTICULAR STATION BY THE ADMIN
    //=====================================================

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
    Station *merge(Station *left, Station *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->name < right->name)
        {
            left->next = merge(left->next, right);
            return left;
        }
        else
        {
            right->next = merge(left, right->next);
            return right;
        }
    }

    //================================================================
    // 4. FUNCTION TO SORT THE STATIONS BY THE ADMIN IN ASCENDING ORDER
    //================================================================
    void Sort()
    {
        mergeSort(&stationHead);
    }

    // FUNCTION TO MERGE LINKED LIST
    void split(Station *source, Station **front, Station **back)
    {
        Station *fast;
        Station *slow;
        slow = source;
        fast = source->next;

        // Move fast two nodes and slow one node
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // Slow is before the midpoint, so split it in two
        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    // PERFORM MERGE SORT ON THE LINKED LIST
    void mergeSort(Station **headRef)
    {
        Station *head = *headRef;
        Station *left;
        Station *right;

        // Base case: if the list is empty or has one node
        if (!head || !head->next)
        {
            return;
        }

        // Split the list into two halves
        split(head, &left, &right);

        // USING RECUSRSION TO SORT THE SUB LISTS
        mergeSort(&left);
        mergeSort(&right);

        // MERGING THE SORTED LISTS
        *headRef = merge(left, right);
    }
    // FUNCTION TO DELETE A PARTICULAR STATION BY THE ADMIN
    void deleteStation(const string &stationName)
    {
        Station *temp = stationHead;
        Station *prev = nullptr;

        // Find the station in the linked list
        while (temp != nullptr && temp->name != stationName)
        {
            prev = temp;
            temp = temp->next;
        }

        // If the station was not found
        if (temp == nullptr)
        {
            cout << "Station not found.\n";
            return;
        }

        // If the station is the head of the list
        if (prev == nullptr)
        {
            stationHead = temp->next; // Change head
        }
        else
        {
            prev->next = temp->next; // Unlink the station
        }

        delete temp; // Free memory
    }

    //============================================================================CUSTOMER FUNCTIONS===========================================================================================================================================

    //=============================================
    // 1. FUNCTION TO RESERVE A TICKET BY THE USER//
    //=============================================

    void reserveTicket()
    {
        displayStations();
        string departureStation, arrivalStation, name, gender;
        int coach_number, cabin_number, seat_number;
        Coaches Coach_no[15];
        cout << "========================================\n";
        cout << "    ENTER YOUR CURRENT STATION NAME: \n";
        cout << "========================================\n";
        cin >> departureStation;
        cout << "========================================\n";

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
        cout << "========================================\n";
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
        cout << "========================================\n";
        cout << "1. RESERVE A SEAT" << endl;
        cout << "2. RESERVE A CABIN [family seat]" << endl;
        cout << "3. RESERVE A COACH" << endl;
        cout << "========================================\n";
        cout << "  PLEASE ENTER YOUR Reservation_TrainOPTION  \n";
        cout << "========================================\n";
        cin >> reservation_option;

        if (reservation_option == 1)
        {
            cout << "AVAILABLE COACHES" << endl;
            for (int i = 0; i < 15; i++)
            {
                if (!Coach_no[i].isbooked)
                {
                    cout << " COACH NUMBER : " << i + 1 << " " << endl;
                }
            }

            cout << "========================================\n";
            cout << "      PLEASE ENTER THE COACH NUMBER : \n";
            cout << "========================================\n";
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

            cout << "========================================\n";
            cout << "     PLEASE ENTER THE CABIN NUMBER: \n";
            cout << "========================================\n";
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
            cout << "========================================\n";
            cout << "     PLEASE ENTER THE SEAT NUMBER: \n";
            cout << "========================================\n";
            cin >> seat_number;

            if (seat_number < 1 || seat_number > 6)
            {
                cout << "INVALID SEAT NUMBER\n";
                return;
            }

            // Mark seat as booked
            Coach_no[coach_number - 1].cabins[cabin_number - 1].seats[seat_number - 1].isbooked = true;

            // Create a new reservation
            Reservation_Train *newReservation_Train = new Reservation_Train{
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

            // Insert the Reservation_Traininto the BST
            reservationRoot = insertReservation(reservationRoot, newReservation_Train);
            reservationMap[ticketID] = newReservation_Train;
        }
        else if (reservation_option == 2)
        {
            cout << "========================================\n";
            cout << "           AVAILABLE COACHES" << endl;
            cout << "========================================\n";
            for (int i = 0; i < 15; i++)
            {
                if (!Coach_no[i].isbooked)
                {
                    cout << " COACH NUMBER: " << i + 1 << " " << endl;
                }
            }

            cout << "========================================\n";
            cout << "    PLEASE ENTER THE COACH NUMBER: ";
            cout << "========================================\n";
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

            cout << "========================================\n";
            cout << "    PLEASE ENTER THE CABIN NUMBER: \n";
            cout << "========================================\n";
            cin >> cabin_number;

            if (cabin_number < 1 || cabin_number > 12)
            {
                cout << "INVALID CABIN NUMBER\n";
                return;
            }
            Coach_no[coach_number - 1].cabins[cabin_number - 1].isbooked = true;
            Seats seat;
            Reservation_Train *newReservation_Train = new Reservation_Train{
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

            // Insert the Reservation_Traininto the BST
            reservationRoot = insertReservation(reservationRoot, newReservation_Train);
            reservationMap[ticketID] = newReservation_Train;
        }
        else if (reservation_option == 3)
        {
            cout << "========================================\n";
            cout << "          AVAILABLE COACHES" << endl;
            cout << "========================================\n";
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
            Reservation_Train *newReservation_Train = new Reservation_Train{
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

            // Insert the Reservation_Traininto the BST
            reservationRoot = insertReservation(reservationRoot, newReservation_Train);
            reservationMap[ticketID] = newReservation_Train;
        }
        else
        {
            cout << "INVALID Reservation_TrainOPTION" << endl;
            return;
        }

        // Calculate the distance and price

        // Display the Reservation_Traindetails
        cout << "========================================\n";
        cout << "       TICKET RESERVED SUCCESSFULY!\n";
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

    //===================================================
    // 2. FUNCTION TO DELETE A RESERVED TICKET BY THE USER
    //===================================================

    void deleteTicket()
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
        cout << "Reservation_TrainWITH TICKET ID " << ticketID << " DELETED SUCCESSFULLY.\n";
    }

    //============================================================
    // 3. FUNCTION TO DISPLAY ALL THE RESERVATIONS MADE BY THE USER
    //============================================================

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
//=============================================================END OF TRAIN TICKET Reservation_TrainCLASS=====================================================================

//===========================================================================================================================================================================
//                                                                      BUS TICKET RESERVATION
//===========================================================================================================================================================================
// Structure for linked list node (Stations)
struct Station_BUS
{
    string name;
    unordered_map<string, double> distances; // Distances to connected stations
    Station_BUS *next;
};
struct Seats_BUS
{
    string seat_no; // Seat number
    bool isBooked;  // Seat booked status
};
struct Bus
{
    string busNumber;        // Bus number
    Seats_BUS Seats_BUS[44]; // 44 Seats_BUS per bus
    bool isBooked;           // Bus booked status
    // You can add more attributes as needed
};

struct Reservation_BUS
{
    string ticketID;
    double price;
    string departureStation;
    string arrivalStation;
    string name;
    string gender;
    Seats_BUS Seats_BUS;
    Reservation_BUS *left;
    Reservation_BUS *right;
    Bus bus[4];
};
struct AVLNode_BUS
{
    Reservation_BUS *reservation_BUS; // Pointer to the reservation_BUS
    AVLNode_BUS *left;                // Left child
    AVLNode_BUS *right;               // Right child
    int height;                       // Height of the node
};

// Function to get the height of the tree
int height(AVLNode_BUS *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of the node
int getBalance(AVLNode_BUS *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotate
AVLNode_BUS *rightRotate(AVLNode_BUS *y)
{
    AVLNode_BUS *x = y->left;
    AVLNode_BUS *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate
AVLNode_BUS *leftRotate(AVLNode_BUS *x)
{
    AVLNode_BUS *y = x->right;
    AVLNode_BUS *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}
// Structure for tree node (Seats_BUS and Cabins)
//===========================================================================================================================================================================
//                                                           CLASS FOR BUS TICKET Reservation_TrainSYSTEM
//===========================================================================================================================================================================

// Class for Train Ticket Reservation_BUSSystem
class BusSystem
{
private:
    Station_BUS *StationHead_BUS;                                // Linked list for stations
    AVLNode_BUS *reservationRoot_BUS;                            // Binary Search Tree for reservations
    unordered_map<string, Reservation_BUS *> reservationMap_BUS; // Map for quick ticket lookup

    // Generate unique ticket ID
    string generateUniqueID()
    {
        srand(time(0));
        return "TICKET-" + to_string(rand() % 10000 + 1);
    }
    AVLNode_BUS *insertReservation(AVLNode_BUS *node, Reservation_BUS *reservation_BUS)
    {
        // Normal BST insert
        if (node == nullptr)
        {
            AVLNode_BUS *newNode = new AVLNode_BUS();
            newNode->reservation_BUS = reservation_BUS;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1; // New node is initially added at leaf
            return newNode;
        }

        if (reservation_BUS->ticketID < node->reservation_BUS->ticketID)
            node->left = insertReservation(node->left, reservation_BUS);
        else if (reservation_BUS->ticketID > node->reservation_BUS->ticketID)
            node->right = insertReservation(node->right, reservation_BUS);
        else // Duplicate ticket IDs are not allowed
            return node;

        // Update the height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor of this ancestor node to check whether
        // this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && reservation_BUS->ticketID < node->left->reservation_BUS->ticketID)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && reservation_BUS->ticketID > node->right->reservation_BUS->ticketID)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && reservation_BUS->ticketID > node->left->reservation_BUS->ticketID)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && reservation_BUS->ticketID < node->right->reservation_BUS->ticketID)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }
    // Insert Reservation_BUSinto BST
    AVLNode_BUS *deleteReservation(AVLNode_BUS *root, string ticketID)
    {
        if (root == nullptr)
            return root;

        // Perform standard BST delete
        if (ticketID < root->reservation_BUS->ticketID)
            root->left = deleteReservation(root->left, ticketID);
        else if (ticketID > root->reservation_BUS->ticketID)
            root->right = deleteReservation(root->right, ticketID);
        else
        {
            // Node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                AVLNode_BUS *temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else               // One child case
                    *root = *temp; // Copy the contents of the non-empty child

                delete temp;
            }
            else
            {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                AVLNode_BUS *temp = root->right;
                while (temp->left != nullptr)
                    temp = temp->left;

                // Copy the inorder successor's data to this node
                root->reservation_BUS = temp->reservation_BUS;

                // Delete the inorder successor
                root->right = deleteReservation(root->right, temp->reservation_BUS->ticketID);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr)
            return root;

        // Update the height of the current node
        root->height = 1 + max(height(root->left), height(root->right));

        // Get the balance factor of this node to check whether
        // this node became unbalanced
        int balance = getBalance(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // In-order traversal to display reservations
    void displayReservationsInOrder(AVLNode_BUS *root)
    {
        if (!root)
            return;

        displayReservationsInOrder(root->left);

        for (int i = 0; i < 4; i++)
        {
            if (root->reservation_BUS->bus[i].isBooked == true)
            {
                cout << "========================================\n";
                cout << "             BUS Reservation_BUS          \n";
                cout << "========================================\n";
                cout << "| TICKET ID:            | " << root->reservation_BUS->ticketID << endl;
                cout << "| NAME:                 | " << root->reservation_BUS->name << endl;
                cout << "| GENDER:               | " << root->reservation_BUS->gender << endl;
                cout << "| Station_BUS OF DEPARTURE: | " << root->reservation_BUS->departureStation << endl;
                cout << "| Station_BUS OF ARRIVAL:   | " << root->reservation_BUS->arrivalStation << endl;
                cout << "| BUS NUMBER:           | " << root->reservation_BUS->bus[i].busNumber << endl;
                cout << "| PRICE:                | " << (root->reservation_BUS->price) * (44) << " PKR\n";
                cout << "========================================\n";
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (root->reservation_BUS->bus[i].isBooked == false)
            {
                for (int j = 0; j < 12; j++)
                {
                    if (root->reservation_BUS->bus[i].Seats_BUS[j].isBooked == true)
                    {
                        cout << "========================================\n";
                        cout << "            CABIN Reservation_BUS          \n";
                        cout << "========================================\n";
                        cout << "| TICKET ID:            | " << root->reservation_BUS->ticketID << endl;
                        cout << "| NAME:                 | " << root->reservation_BUS->name << endl;
                        cout << "| GENDER:               | " << root->reservation_BUS->gender << endl;
                        cout << "| Station_BUS OF DEPARTURE: | " << root->reservation_BUS->departureStation << endl;
                        cout << "| Station_BUS OF ARRIVAL:   | " << root->reservation_BUS->arrivalStation << endl;
                        cout << "| SEAT NUMBER:          | " << j + 1 << endl;
                        cout << "| PRICE:                | " << (root->reservation_BUS->price) << " PKR\n";
                        cout << "========================================\n";
                    }
                }
            }
        }
        displayReservationsInOrder(root->right);
    }

public:
    BusSystem() : StationHead_BUS(nullptr), reservationRoot_BUS(nullptr) {}

    //===========================================================================Admin functions================================================================================================
    void addStation(const string &name, const unordered_map<string, double> &distances)
    {
        Station_BUS *newStation = new Station_BUS{name, distances, nullptr};
        if (!StationHead_BUS)
        {
            StationHead_BUS = newStation;
            return;
        }
        Station_BUS *temp = StationHead_BUS;
        while (temp->next)
            temp = temp->next;
        temp->next = newStation;

        // Now ensure the connection is bidirectional by adding reverse connections
        for (const auto &pair : distances)
        {
            string connectedStation = pair.first;
            double distance = pair.second;

            // Find the connected Station_BUS in the list
            Station_BUS *connectedStationNode = StationHead_BUS;
            while (connectedStationNode && connectedStationNode->name != connectedStation)
                connectedStationNode = connectedStationNode->next;

            if (connectedStationNode)
            {
                // Add reverse connection (connectedStation -> Station_BUS)
                connectedStationNode->distances[name] = distance;
            }
        }
    }

    // Admin: Display all stations
    void displayStations()
    {
        Station_BUS *temp = StationHead_BUS;
        if (!temp)
        {
            cout << "No stations available.\n";
            return;
        }
        cout << "========================================\n";
        cout << "          AVAILABLE STATIONS:\n";
        cout << "========================================\n";
        while (temp)
        {
            cout << "- " << temp->name << "\n";
            temp = temp->next;
        }
        cout << "========================================\n";
    }

    // Admin: Edit a Station_BUS
    void editStation()
    {
        displayStations();
        string stationName;
        cout << "Enter the name of the Station_BUS to edit: ";
        cin >> stationName;

        Station_BUS *temp = StationHead_BUS;
        while (temp && temp->name != stationName)
            temp = temp->next;

        if (!temp)
        {
            cout << "Station_BUS not found.\n";
            return;
        }

        cout << "Editing distances for Station_BUS: " << stationName << endl;
        for (auto &pair : temp->distances)
        {
            cout << "Enter distance to " << pair.first << " (current: " << pair.second << " km): ";
            cin >> pair.second;
        }
        cout << "Station_BUS distances updated successfully.\n";
    }
    Station_BUS *merge(Station_BUS *left, Station_BUS *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->name < right->name)
        {
            left->next = merge(left->next, right);
            return left;
        }
        else
        {
            right->next = merge(left, right->next);
            return right;
        }
    }
    void Sort()
    {
        mergeSort(&StationHead_BUS);
    }

    // Function to split the linked list into two halves
    void split(Station_BUS *source, Station_BUS **front, Station_BUS **back)
    {
        Station_BUS *fast;
        Station_BUS *slow;
        slow = source;
        fast = source->next;

        // Move fast two nodes and slow one node
        while (fast != nullptr)
        {
            fast = fast->next;
            if (fast != nullptr)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        // Slow is before the midpoint, so split it in two
        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    // Function to perform merge sort on the linked list
    void mergeSort(Station_BUS **headRef)
    {
        Station_BUS *head = *headRef;
        Station_BUS *left;
        Station_BUS *right;

        // Base case: if the list is empty or has one node
        if (!head || !head->next)
        {
            return;
        }

        // Split the list into two halves
        split(head, &left, &right);

        // Recursively sort the sublists
        mergeSort(&left);
        mergeSort(&right);

        // Merge the sorted lists
        *headRef = merge(left, right);
    }
    // Function to delete a specific Station_BUS from the linked list
    void deleteStation(const string &stationName)
    {
        Station_BUS *temp = StationHead_BUS;
        Station_BUS *prev = nullptr;

        // Traverse the list to find the Station_BUS
        while (temp != nullptr && temp->name != stationName)
        {
            prev = temp;
            temp = temp->next;
        }

        // If the Station_BUS was not found
        if (temp == nullptr)
        {
            cout << "Station_BUS not found.\n";
            return;
        }

        // If the Station_BUS is the head of the list
        if (prev == nullptr)
        {
            StationHead_BUS = temp->next; // Change head
        }
        else
        {
            prev->next = temp->next; // Unlink the Station_BUS
        }

        delete temp; // Free memory
    }

    //================================================================================================================================================================================================================================
    void reserveTicket()
    {
        displayStations();
        string departureStation, arrivalStation, name, gender;
        int coach_number, cabin_number, seat_number;
        Bus Coach_no[4];
        cout << "========================================\n";
        cout << "    ENTER YOUR CURRENT STATION NAME: \n";
        cout << "========================================\n";
        cin >> departureStation;
        cout << "========================================\n";

        // Find the departure Station_BUS in the linked list
        Station_BUS *departureNode = StationHead_BUS;
        while (departureNode && departureNode->name != departureStation)
        {
            departureNode = departureNode->next;
        }

        // Check if the departure Station_BUS exists
        if (!departureNode)
        {
            cout << "STATION NOT FOUND [please try again]\n";
            return;
        }

        // Display the list of connected cities for the departure Station_BUS
        cout << "CITIES CONNECTED TO " << departureStation << ":\n";
        cout << "========================================\n";
        for (const auto &pair : departureNode->distances)
        {
            cout << "- " << pair.first << "\n"; // Display connected cities
        }

        cout << "ENTER YOUR DESTINATION FROM THE ABOVE LIST : ";
        cin >> arrivalStation;

        // Check if the arrival Station_BUS exists in the connected cities
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
        cout << "========================================\n";
        cout << "1. RESERVE A SEAT" << endl;
        cout << "2. RESERVE A COMPLETE BUS " << endl;
        cout << "========================================\n";
        cout << "       PLEASE ENTER YOUR OPTION  \n";
        cout << "========================================\n";
        cin >> reservation_option;

        if (reservation_option == 1)
        {
            cout << "AVAILABLE COACHES" << endl;
            for (int i = 0; i < 4; i++)
            {
                if (!Coach_no[i].isBooked)
                {
                    cout << " COACH NUMBER : " << i + 1 << " " << endl;
                }
            }

            cout << "========================================\n";
            cout << "      PLEASE ENTER THE BUS NUMBER : \n";
            cout << "========================================\n";
            cin >> coach_number;

            if (coach_number < 1 || coach_number > 4)
            {
                cout << "INVALID COACH NUMBER [please enter a number from the above given list]\n";
                return;
            }

            cout << "Available Cabins" << endl;
            for (int i = 0; i < 44; i++)
            {
                if (!Coach_no[coach_number - 1].Seats_BUS[i].isBooked)
                {
                    cout << "Seat Number: " << i + 1 << endl;
                }
            }

            cout << "========================================\n";
            cout << "     PLEASE ENTER THE SEAT NUMBER: \n";
            cout << "========================================\n";
            cin >> seat_number;

            if (seat_number < 1 || seat_number > 44)
            {
                cout << "INVALID SEAT NUMBER\n";
                return;
            }

            // Mark seat as booked
            Coach_no[coach_number - 1].Seats_BUS[seat_number - 1].isBooked = true;

            // Create a new reservation_BUS
            Reservation_BUS *newReservation_BUS = new Reservation_BUS{
                ticketID,
                prices,
                departureStation,
                arrivalStation,
                name,
                gender,
                Coach_no[coach_number - 1].Seats_BUS[seat_number - 1],
                nullptr,
                nullptr,
            };

            // Insert the Reservation_BUSinto the AVL
            reservationRoot_BUS = insertReservation(reservationRoot_BUS, newReservation_BUS);
            reservationMap_BUS[ticketID] = newReservation_BUS;
            cout << "========================================\n";
            cout << "       TICKET RESERVED SUCCESSFULY!\n";
            cout << "========================================\n";
            cout << "| TICKET ID:         | " << ticketID << endl;
            cout << "| NAME:              | " << name << endl;
            cout << "| GENDER:            | " << gender << endl;
            cout << "| DEPARTURE STATION: | " << departureStation << endl;
            cout << "| ARRIVAL STATION:   | " << arrivalStation << endl;
            cout << "| DISTANCE:          | " << distance << " km\n";
            cout << "| PRICE:             | " << prices << " PKR\n";
            cout << "| BUS NUMBER:        | " << coach_number << endl;
            cout << "| SEAT NUMBER:       | " << seat_number << endl;
            cout << "| DISTANCE:          | " << distance << " PKR\n";
            cout << "========================================\n";
            return;
        }
        else if (reservation_option == 2)
        {
            cout << "========================================\n";
            cout << "            AVAILABLE BUSES" << endl;
            cout << "========================================\n";
            for (int i = 0; i < 4; i++)
            {
                if (!Coach_no[i].isBooked)
                {
                    cout << " BUS NUMBER: " << i + 1 << " " << endl;
                }
            }

            cout << "========================================\n";
            cout << "    PLEASE ENTER THE BUS NUMBER: ";
            cout << "========================================\n";
            cin >> coach_number;

            if (coach_number < 1 || coach_number > 4)
            {
                cout << "INVALID COACH NUMBER\n";
                return;
            }

            Coach_no[coach_number - 1].isBooked = true;
            Seats_BUS seat;
            Reservation_BUS *newReservation_BUS = new Reservation_BUS{
                ticketID,
                prices,
                departureStation,
                arrivalStation,
                name,
                gender,
                seat,
                nullptr,
                nullptr,
                Coach_no[coach_number - 1]};

            // Insert the Reservation_BUSinto the BST
            reservationRoot_BUS = insertReservation(reservationRoot_BUS, newReservation_BUS);
            reservationMap_BUS[ticketID] = newReservation_BUS;
        }
        else
        {
            cout << "INVALID Reservation_BUSOPTION" << endl;
            return;
        }

        // Calculate the distance and price

        // Display the Reservation_BUSdetails
        cout << "========================================\n";
        cout << "       BUS RESERVED SUCCESSFULY!\n";
        cout << "========================================\n";
        cout << "| TICKET ID:         | " << ticketID << endl;
        cout << "| NAME:              | " << name << endl;
        cout << "| GENDER:            | " << gender << endl;
        cout << "| DEPARTURE Station_BUS: | " << departureStation << endl;
        cout << "| ARRIVAL Station_BUS:   | " << arrivalStation << endl;
        cout << "| DISTANCE:          | " << distance << " km\n";
        cout << "| PRICE:             | " << prices << " PKR\n";
        cout << "| BUS NUMBER:        | " << coach_number << endl;
        cout << "| SEAT NUMBER:       | " << "1-44" << endl;
        cout << "| DISTANCE:          | " << distance << " PKR\n";
        cout << "========================================\n";
    }

    // User: Delete a reservation_BUS
    void
    deleteTicket()
    {
        string ticketID;
        cout << "ENTER THE TICKET ID TO DELETE IT: ";
        cin >> ticketID;

        if (reservationMap_BUS.find(ticketID) == reservationMap_BUS.end())
        {
            cout << "NO TICKET FOUND WITH ID : " << ticketID << ".\n";
            return;
        }

        reservationRoot_BUS = deleteReservation(reservationRoot_BUS, ticketID);
        reservationMap_BUS.erase(ticketID);
        cout << "Reservation_BUSWITH TICKET ID " << ticketID << " DELETED SUCCESSFULLY.\n";
    }

    // User: Display all reservations
    void displayReservations()
    {
        if (!reservationRoot_BUS)
        {
            cout << "NO RESERVATIONS FOUND.\n";
            return;
        }
        displayReservationsInOrder(reservationRoot_BUS);
    }
};

//===========================================================================================================================================================================
//                                                                                END OF BUS SYSTEM
//===========================================================================================================================================================================

//============================================================CONCERT RESERVATION SYSTEM================================================================================
//---------------------------
// Concert Reservation System
//---------------------------
struct Concert_Seats
{
    string seat_no; // Seat number
    bool isBooked;  // Seat booked status
};

//---------------------------
// Struct to represent a hall
//---------------------------

struct Concert_Hall
{
    string name;
    string location;
    Concert_Seats Concert_seats[50];
    bool isBooked;
    double price;
};

//------------------------------------------
// Struct to represent a Concert_reservation
//------------------------------------------

struct Concert_Reservation
{
    string name;
    string gender;
    int age; // Added age field
    string ticketID;
    string time;
    string singer_name;
    string type;
    string date;
    double price;
    string location;
    string hallName;   // Concert_Hall name where the Concert_reservation is made
    string seatNumber; // Seat number reserved
};

// Struct to represent a concert
struct Concert
{
    bool isBooked;
    string name;
    string type;
    string date;
    string time;
    string venue;
    double price;
    list<Concert_Reservation> reservations; // List of reservations for this concert
    vector<Concert_Hall> halls;             // Halls associated with this concert

    // Constructor to initialize halls
    Concert()
    {
        halls.resize(5);
        halls[0] = {"Platinum Concert_Hall", venue, {}, false, 500}; // Platinum Concert_Hall
        halls[1] = {"Gold Concert_Hall", venue, {}, false, 400};     // Gold Concert_Hall
        halls[2] = {"Silver Concert_Hall", venue, {}, false, 300};   // Silver Concert_Hall
        halls[3] = {"Bronze Concert_Hall", venue, {}, false, 200};   // Bronze Concert_Hall
        halls[4] = {"VIP Concert_Hall", venue, {}, false, 600};      // VIP Concert_Hall
    }
};

class ConcertGraph
{
private:
    unordered_map<string, Concert> concerts; // Map of concert name to Concert object

public:
    // Constructor
    ConcertGraph() {}

    // Add a concert to the graph
    void addConcert(const string &name, const string &type, const string &date, const string &time, const string &venue, double price)
    {
        Concert newConcert;
        newConcert.isBooked = false;
        newConcert.name = name;
        newConcert.type = type;
        newConcert.date = date;
        newConcert.time = time;
        newConcert.venue = venue;
        newConcert.price = price;
        concerts[name] = newConcert; // Add to the graph
    }

    // Display all concerts
    void displayConcerts()
    {
        if (concerts.empty())
        {
            cout << "No Concerts available.\n";
            return;
        }
        cout << "========================================\n";
        cout << "          AVAILABLE CONCERTS:\n";
        cout << "========================================\n";
        for (const auto &pair : concerts)
        {
            const Concert &concert = pair.second;
            cout << "NAME  :" << concert.name << "\n";
            cout << "TYPE  :" << concert.type << "\n";
            cout << "DATE  :" << concert.date << "\n";
            cout << "TIME  :" << concert.time << "\n";
            cout << "VENUE :" << concert.venue << "\n";
            cout << "PRICE :" << concert.price << "\n";
        }
        cout << "========================================\n";
    }

    // Reserve a ticket for a concert
    void reserveTicket(const string &concertName, const string &name, const string &gender, int age)
    {
        if (concerts.find(concertName) == concerts.end())
        {
            cout << "Concert not found.\n";
            return;
        }

        Concert &concert = concerts[concertName];

        // Check if any seat or hall is already booked
        if (concert.isBooked || std::any_of(concert.halls.begin(), concert.halls.end(), [](const Concert_Hall &hall)
                                            { return hall.isBooked; }))
        {
            cout << "There is already a booking for this event.\n";
            return;
        }

        int choice;
        cout << "========================================\n";
        cout << "Choose booking type:\n";
        cout << "========================================\n";
        cout << "1. Book Entire Event\n";
        cout << "2. Book a Concert_Hall\n";
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
                    if (concert.halls[i].Concert_seats[j].isBooked)
                    {
                        cout << " A Seat is already booked here\n";
                        return;
                    }
                }
            }
            concert.isBooked = true;
            {
                string ticketID = to_string(rand() % 10000); // Generate a random ticket ID
                cout << "Event booked successfully for " << concertName << ".\n";
                cout << "========================================\n";
                cout << "           RESERVATION DETAILS\n";
                cout << "========================================\n";
                cout << "| NAME:           | " << name << endl;
                cout << "| TICKET ID:      | " << ticketID << endl;
                cout << "| GENDER:         | " << gender << endl;
                cout << "| AGE:            | " << age << endl;
                cout << "| CONCERT NAME:   | " << concertName << endl;
                cout << "| CONCERT VENUE:  | " << concert.venue << endl;
                cout << "| CONCERT DATE:   | " << concert.date << endl;
                cout << "| CONCERT TIME:   | " << concert.time << endl;
                cout << "| TICKET PRICE:   | " << (concert.price) * 200 << endl;
                cout << "========================================\n";
            }
            break;

        case 2:
        { // Book a hall
            // Check if the event is already booked
            if (concert.isBooked)
            {
                cout << "There is already a booking for this event.\n";
                return;
            }

            cout << "Available Halls:\n";
            for (size_t i = 0; i < concert.halls.size(); ++i)
            {
                cout << i + 1 << ". " << concert.halls[i].name << " - Price: " << concert.halls[i].price << "\n";
            }
            int hallChoice;
            cout << "Select a hall to book: ";
            cin >> hallChoice;

            if (hallChoice < 1 || hallChoice > concert.halls.size() || concert.halls[hallChoice - 1].isBooked)
            {
                cout << "Invalid choice or hall already booked.\n";
                return;
            }

            Concert_Reservation Concert_reservation;
            Concert_reservation.name = name;
            Concert_reservation.gender = gender;
            Concert_reservation.age = age;
            Concert_reservation.ticketID = to_string(rand() % 10000);          // Generate a random ticket ID
            Concert_reservation.hallName = concert.halls[hallChoice - 1].name; // Set hall name
            concert.reservations.push_back(Concert_reservation);               // Add Concert_reservation to concert

            concert.halls[hallChoice - 1].isBooked = true;
            cout << "Concert_Hall " << concert.halls[hallChoice - 1].name << " booked successfully.\n";
            cout << "========================================\n";
            cout << "           RESERVATION DETAILS\n";
            cout << "========================================\n";
            cout << "| NAME:           | " << name << endl;
            cout << "| TICKET ID:      | " << Concert_reservation.ticketID << endl;
            cout << "| GENDER:         | " << gender << endl;
            cout << "| AGE:            | " << age << endl;
            cout << "| HALL NAME:      | " << Concert_reservation.hallName << endl;
            cout << "| CONCERT DATE:   | " << concert.date << endl;
            cout << "| CONCERT VENUE: | " << concert.venue << endl;
            cout << "| CONCERT TIME:   | " << concert.time << endl;
            cout << "========================================\n";
            break;
        }

        case 3:
        { // Book a seat
            // Check if the event is already booked
            if (concert.isBooked)
            {
                cout << "There is already a booking for this event.\n";
                return;
            }

            cout << "Available Halls:\n";
            for (size_t i = 0; i < concert.halls.size(); ++i)
            {
                cout << i + 1 << ". " << concert.halls[i].name << " - Price: " << concert.halls[i].price << "\n";
            }
            int hallChoice;
            cout << "Select a hall to book a seat: ";
            cin >> hallChoice;

            if (hallChoice < 1 || hallChoice > concert.halls.size() || concert.halls[hallChoice - 1].isBooked)
            {
                cout << "Invalid choice or hall already booked.\n";
                return;
            }

            Concert_Hall &selectedHall = concert.halls[hallChoice - 1];
            cout << "========================================\n";
            cout << "Available Concert_Seats in " << selectedHall.name << ":\n";
            cout << "========================================\n";

            // Display available Concert_seats
            for (int i = 0; i < 50; i++)
            {
                selectedHall.Concert_seats[i].seat_no = to_string(i + 1); // Assign seat numbers
            }
            for (int i = 0; i < 50; ++i)
            {
                if (!selectedHall.Concert_seats[i].isBooked)
                {
                    cout << selectedHall.Concert_seats[i].seat_no << " | "; // Print available seat numbers
                }
                if (i == 10 || i == 20 || i == 30 || i == 40)
                {
                    cout << "\n"; // New line for better readability
                }
            }
            cout << "\n"; // New line for better readability

            cout << "Enter seat number to book: ";
            string seatNumber;
            cin >> seatNumber;

            // Check if the seat number is valid
            bool seatFound = false;
            for (int i = 0; i < 50; ++i)
            {
                if (selectedHall.Concert_seats[i].seat_no == seatNumber)
                {
                    if (!selectedHall.Concert_seats[i].isBooked)
                    {
                        selectedHall.Concert_seats[i].isBooked = true;
                        cout << "Seat " << seatNumber << " booked successfully in " << selectedHall.name << ".\n";
                        seatFound = true;

                        // Create a Concert_reservation entry
                        Concert_Reservation Concert_reservation;
                        Concert_reservation.name = name;
                        Concert_reservation.gender = gender;
                        Concert_reservation.age = age;
                        Concert_reservation.ticketID = to_string(rand() % 10000); // Generate a random ticket ID
                        Concert_reservation.hallName = selectedHall.name;         // Set hall name
                        Concert_reservation.seatNumber = seatNumber;              // Set seat number
                        concert.reservations.push_back(Concert_reservation);      // Add Concert_reservation to concert

                        cout << "========================================\n";
                        cout << "           RESERVATION DETAILS\n";
                        cout << "========================================\n";
                        cout << "| NAME:           | " << name << endl;
                        cout << "| TICKET ID:      | " << Concert_reservation.ticketID << endl;
                        cout << "| GENDER:         | " << gender << endl;
                        cout << "| AGE:            | " << age << endl;
                        cout << "| HALL NAME:      | " << Concert_reservation.hallName << endl;
                        cout << "| SEAT NUMBER:    | " << Concert_reservation.seatNumber << endl;
                        cout << "| CONCERT DATE:   | " << concert.date << endl;
                        cout << "| CONCERT VENUE:  | " << concert.venue << endl;
                        cout << "| CONCERT TIME:   | " << concert.time << endl;
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
    // Display reservations for a concert
    // Display reservations for a concert
    void displayReservations(const string &ticketID = "")
    {
        if (ticketID.empty())
        {
            cout << "No ticket ID provided.\n";
            return;
        }

        bool found = false; // Flag to check if the Concert_reservation is found

        // Iterate through all concerts to find the Concert_reservation by ticket ID
        for (const auto &concertPair : concerts)
        {
            const Concert &concert = concertPair.second;

            for (const auto &Concert_reservation : concert.reservations)
            {
                if (Concert_reservation.ticketID == ticketID)
                {
                    // Print ticket-like format
                    cout << "========================================\n";
                    cout << "               TICKET\n";
                    cout << "========================================\n";
                    cout << "| TICKET ID:      | " << Concert_reservation.ticketID << "\n";
                    cout << "| NAME:           | " << Concert_reservation.name << "\n";
                    cout << "| GENDER:         | " << Concert_reservation.gender << "\n";
                    cout << "| AGE:            | " << Concert_reservation.age << "\n";
                    cout << "| CONCERT:        | " << concertPair.first << "\n";
                    cout << "| CONCERT THEME:  | " << concert.type << "\n";
                    cout << "| VENUE:          | " << concert.venue << "\n"; // Assuming venue is a field in Concert
                    cout << "| HALL:           | " << Concert_reservation.hallName << "\n";
                    cout << "| SEAT:           | " << Concert_reservation.seatNumber << "\n";
                    cout << "| DATE:           | " << concert.date << "\n"; // Date and time of the Concert_reservation
                    cout << "| TIME:           | " << concert.time << "\n"; // Date and time of the Concert_reservation
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
            cout << "No Concert_reservation found for ticket ID " << ticketID << ".\n";
        }
    }

    // Delete a Concert_reservation by ticket ID
    void deleteReservation(const string &concertName, const string &ticketID)
    {
        if (concerts.find(concertName) == concerts.end())
        {
            cout << "Concert not found.\n";
            return;
        }

        Concert &concert = concerts[concertName];
        auto it = concert.reservations.begin();
        while (it != concert.reservations.end())
        {
            if (it->ticketID == ticketID)
            {
                it = concert.reservations.erase(it); // Remove Concert_reservation
                cout << "Concert_Reservation with ticket ID " << ticketID << " deleted successfully.\n";
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Ticket ID not found in reservations.\n";
    }
};

//===========================================================================================================================================================================
//                                                                        END OF CONCERT SYSTEM
//===========================================================================================================================================================================

//=======================================================================STADIUM RESERVATION SYSTEM================================================================================

//--------------------------
// Struct to represent seats
//--------------------------
struct Stadium_Seats
{
    string seat_no; // Seat number
    bool isBooked;  // Seat booked status
};

//--------------------------
// Struct to represent a section
//--------------------------

struct Stadium_section
{
    string name;
    string location;
    Stadium_Seats seats[250];
    bool isBooked;
    double price; // Price for booking this section
};

//----------------------------------
// Struct to represent a reservation
//----------------------------------

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

//--------------------------------
// Struct to represent a stadium
//--------------------------------

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

//===========================================================================================================================================================================
//                                                          CLASS OF STADIUM SYSTEM
//===========================================================================================================================================================================
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

//===========================================================================================================================================================================
//                                                                        END OF STADIUM SYSTEM
//===========================================================================================================================================================================

//===========================================================================================================================================================================
//                                                                        FILE HANDLING FUNCTIONS
//===========================================================================================================================================================================

//===============================
// Function to authenticate admin
//===============================

bool authenticateAdmin(const string &userId, const string &password)
{
    ifstream file("admin_credientials.txt");
    if (!file.is_open())
    {
        cout << "Error opening credentials file.\n";
        return false;
    }

    string name, storedUserId, storedPassword;
    while (file >> name >> storedUserId >> storedPassword)
    {
        if (storedUserId == userId && storedPassword == password)
        {
            return true; // Authentication successful
        }
    }

    return false; // Authentication failed
}
bool authenticateCustomer(const string &userId, const string &password)
{
    ifstream file("customer_credentials.txt");
    if (!file.is_open())
    {
        cout << "Error opening customer credentials file.\n";
        return false;
    }

    string name, storedUserId, storedPassword;
    while (file >> name >> storedUserId >> storedPassword)
    {
        if (storedUserId == userId && storedPassword == password)
        {
            return true; // Authentication successful
        }
    }

    return false; // Authentication failed
}

//================================
// Function to signup a new admin
//================================

bool signupCustomer(const string &name, const string &userId, const string &password)
{
    ofstream file("customer_credentials.txt", ios::app); // Open in append mode
    if (!file.is_open())
    {
        cout << "Error opening customer credentials file for signup.\n";
        return false;
    }

    // Check if the userId already exists
    ifstream checkFile("customer_credentials.txt");
    string storedName, storedUserId, storedPassword;
    while (checkFile >> storedName >> storedUserId >> storedPassword)
    {
        if (storedUserId == userId)
        {
            cout << "User  ID already exists. Please choose a different one.\n";
            return false; // User ID already exists
        }
    }

    // Write new customer details to the file
    file << name << " " << userId << " " << password << endl;
    cout << "Signup successful! You can now log in.\n";
    return true;
}

//===========================================================================================================================================================================
//                                                                       MAIN FUNCTION
//===========================================================================================================================================================================

int main()
{
    //=======================
    // CREATE SYSTEM OBJECTS
    //=======================
    TrainSystem Trainsystem;
    StadiumGraph Stadiumsystem;
    ConcertGraph Concertsystem;
    BusSystem Bussystem;

    //=======================
    // INITIALIZE TRAIN SYSTEM
    //=======================

    Trainsystem.addStation("Karachi", {{"Lahore", 1211}, {"Islamabad", 1411}, {"Quetta", 683.7}, {"Sukkur", 474.5}, {"Multan", 1053.7}, {"Faisalabad", 1281.7}, {"Peshawar", 1483.7}, {"Hyderabad", 163.7}, {"Gwadar", 653.7}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Lahore", {{"Karachi", 1211}, {"Islamabad", 375}, {"Faisalabad", 128}, {"Multan", 331}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Peshawar", 189}, {"Sukkur", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Islamabad", {{"Lahore", 375}, {"Peshawar", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Peshawar", {{"Islamabad", 189}, {"Lahore", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Quetta", {{"Karachi", 683.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Multan", {{"Karachi", 1053.7}, {"Lahore", 331}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Faisalabad", {{"Karachi", 1281.7}, {"Lahore", 128}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Sukkur", {{"Karachi", 474.5}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Hyderabad", {{"Karachi", 163.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Sukkur", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Trainsystem.addStation("Gwadar", {{"Karachi", 653.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Sukkur", 1411}});

    //=========================
    // INITIALIZE STADIUM SYSTEM
    //=========================

    Stadiumsystem.addMatch("India", "Pakistan ", "GADDAFI-STADIUM", "Cricket", "2025-01-10", "10:00", "Mumbai    ");
    Stadiumsystem.addMatch("India", "Australia", "ADELEDE OVAL", "Cricket", "2025-03-12", "10:00", "Delhi     ");
    Stadiumsystem.addMatch("India", "England  ", "MCG", "Cricket", "2025-01-14", "10:00", "Rawalpindi");

    //=========================
    // INITIALIZE CONCERT SYSTEM
    //=========================

    Concertsystem.addConcert("ATIF-ASLAM-CONCERT", "Music", "2025-01-11", "17:00", "Karachi", 250);
    Concertsystem.addConcert("ALI-ZAFAR-CONCERT", "Music", "2025-01-12", "17:00", "Lahore", 300);
    Concertsystem.addConcert("ARIJIT-SINGH-CONCERT", "Music", "2025-01-13", "17:00", "Islamabad", 350);

    //=========================
    // INITIALIZE BUS SYSTEM
    //=========================

    Bussystem.addStation("Karachi", {{"Lahore", 1211}, {"Islamabad", 1411}, {"Quetta", 683.7}, {"Sukkur", 474.5}, {"Multan", 1053.7}, {"Faisalabad", 1281.7}, {"Peshawar", 1483.7}, {"Hyderabad", 163.7}, {"Gwadar", 653.7}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Lahore", {{"Karachi", 1211}, {"Islamabad", 375}, {"Faisalabad", 128}, {"Multan", 331}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Peshawar", 189}, {"Sukkur", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Islamabad", {{"Lahore", 375}, {"Peshawar", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Peshawar", {{"Islamabad", 189}, {"Lahore", 189}, {"Karachi", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Quetta", {{"Karachi", 683.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Multan", {{"Karachi", 1053.7}, {"Lahore", 331}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Faisalabad", {{"Karachi", 1281.7}, {"Lahore", 128}, {"Islamabad", 1411}, {"Sukkur", 1411}, {"Multan", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Quetta", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Sukkur", {{"Karachi", 474.5}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Hyderabad", {{"Karachi", 163.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Sukkur", 1411}, {"Gwadar", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}});
    Bussystem.addStation("Gwadar", {{"Karachi", 653.7}, {"Lahore", 1411}, {"Islamabad", 1411}, {"Quetta", 1411}, {"Multan", 1411}, {"Faisalabad", 1411}, {"Hyderabad", 1411}, {"Peshawar", 1411}, {"Sialkot", 1411}, {"Sargodha", 1411}, {"Sukkur", 1411}});

    //=====================================
    // TAKE USER INPUT FOR ADMIN OR CUSTOMER
    //=====================================

    int ROLE;
    do
    {
        cout << "========================================\n";
        cout << "          WELCOME TO TICKET MASTER\n";
        cout << "========================================\n";
        cout << "1. ADMIN\n";
        cout << "2. CUSTOMER\n";
        cout << "========================================\n";
        cout << "ENTER YOUR ROLE: \n";
        cout << "========================================\n";
        cin >> ROLE;

        string admin_userId, admin_password;
        int customer_credentials_choice;
        string customer_userId, customer_password;
        int system_choice;
        int train_choice;
        int stadium_choice;
        int concert_choice;
        int bus_choice;
        int admin_choice;
        int admin_train_choice, admin_stadium_choice, admin_concert_choice, admin_bus_choice;

        switch (ROLE)
        {
        //=======================
        // ADMINISTRATOR INTERFACE
        //=======================
        case 1:
            cout << "Enter your User ID: ";
            cin >> admin_userId;
            cout << "Enter your Password: ";
            cin >> admin_password;

            // Authenticate admin
            do
            {
                if (authenticateAdmin(admin_userId, admin_password))
                {
                    cout << "========================================\n";
                    cout << "    Access granted to Admin Panel.\n";
                    cout << "========================================\n";
                    // Proceed to admin panel
                    cout << "========================================\n";
                    cout << "1. TRAIN SYSTEM\n";
                    cout << "2. STADIUM SYSTEM\n";
                    cout << "3. CONCERT SYSTEM\n";
                    cout << "4. BUS SYSTEM\n";
                    cout << "5. EXIT\n";
                    cout << "========================================\n";
                    cout << "ENTER YOUR CHOICE: ";
                    cin >> admin_choice;

                    switch (admin_choice)
                    {
                    case 1:
                    {
                        string delete_station;
                        do
                        {
                            cout << "========================================\n";
                            cout << "|             ADMIN PANEL:             |\n";
                            cout << "========================================\n";
                            cout << "1. ADD STATIONS \n2. EDIT STATIONS\n3. DISPLAY STATIONS\n4.SORT THE STATIONS\n5.DELETE A STATION\n6. EXIT\nSELECT AN OPTION: ";
                            cin >> admin_train_choice;

                            switch (admin_train_choice)
                            {
                            case 1:
                            {
                                unordered_map<string, double> distances;
                                string station_name;
                                int connections;

                                cout << "ENTER THE STATION NAME : ";
                                cin.ignore(); // Clear the input buffer to handle the next getline properly
                                getline(cin, station_name);

                                cout << "ENTER THE NUMBER OF CONNECTED STATIONS : ";
                                cin >> connections;

                                for (int i = 0; i < connections; ++i)
                                {
                                    string connectedStation;
                                    double distance;
                                    cout << "ENTER THE NAME OF THE CONNECTED STATIONS AND THE DISTANCE : ";
                                    cin >> connectedStation >> distance;
                                    distances[connectedStation] = distance;
                                }

                                Trainsystem.addStation(station_name, distances);
                                cout << "STATION " << station_name << " ADDED SUCCESSFULLY.\n";
                            }
                            break;
                            case 2:
                                Trainsystem.editStation();
                                cout << "===============================" << endl;
                                cout << "  STATION EDITED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 3:
                                Trainsystem.displayStations();
                                break;
                            case 4:
                                Trainsystem.Sort();
                                cout << "===============================" << endl;
                                cout << "  STATION SORTED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 5:

                                cout << "Enter the name of the station you want to delete";
                                cin >> delete_station;
                                Trainsystem.deleteStation(delete_station);
                                cout << "===============================" << endl;
                                cout << " STATION DELETED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 6:
                                cout << "===============================" << endl;
                                cout << "    EXITING ADMIN PANEL.\n";
                                cout << "===============================" << endl;
                                break;
                            default:
                                cout << "===============================" << endl;
                                cout << "   INVALID CHOICE TRY AGAIN.\n";
                                cout << "===============================" << endl;
                            }
                        } while (admin_train_choice != 6);
                    }
                    break;
                    case 2:
                    {
                        string stadium_to_delete;
                        do
                        {
                            cout << "========================================\n";
                            cout << "|             ADMIN PANEL:             |\n";
                            cout << "========================================\n";
                            cout << "1. ADD MATCH \n2. DISPLAY MATCHES\n3. DELETE MATCH DATA \n 4.EXIT\nSELECT AN OPTION: ";
                            cin >> admin_stadium_choice;

                            switch (admin_stadium_choice)
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
                                Stadiumsystem.addMatch(Team1, Team2, name, type, date, time, venue);

                                cout << "MATCH" << Team1 << "vs" << Team2 << " ADDED SUCCESSFULLY .\n"; // Confirmation message
                                break;
                            }
                            case 2:
                                Stadiumsystem.displayUpcomingMatches();
                                break;
                            case 3:
                                cout << "ENTER THE NAME OF THE STADIUM ";
                                cin.ignore();
                                getline(cin, stadium_to_delete);
                                Stadiumsystem.deleteMatch(stadium_to_delete);
                                break;
                            case 4:
                                cout << "Exiting admin panel.\n";
                                break;
                            default:
                                cout << "Invalid choice. Try again.\n";
                            }
                        } while (admin_stadium_choice != 3);
                    }
                    break;
                    case 3:
                    {
                        do
                        {
                            cout << "========================================\n";
                            cout << "|             ADMIN PANEL:             |\n";
                            cout << "========================================\n";
                            cout << "1. ADD CONCERT \n2. DISPLAY CONCERTS\n3. EXIT\nSELECT AN OPTION: ";
                            cin >> admin_concert_choice;

                            switch (admin_concert_choice)
                            {
                            case 1:
                            {
                                string name, type, date, time, venue;
                                double price;
                                cout << "Enter concert name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter concert type: ";
                                getline(cin, type);
                                cout << "Enter concert date (YYYY-MM-DD): ";
                                getline(cin, date);
                                cout << "Enter concert time (HH:MM): ";
                                getline(cin, time);
                                cout << "Enter concert venue: ";
                                getline(cin, venue);
                                cout << "Enter concert price: ";
                                cin >> price;

                                Concertsystem.addConcert(name, type, date, time, venue, price);
                                cout << "Concert added successfully.\n";
                                break;
                            }
                            case 2:
                                Concertsystem.displayConcerts();
                                break;
                            case 3:
                                cout << "Exiting admin panel.\n";
                                break;
                            default:
                                cout << "Invalid choice. Try again.\n";
                            }
                        } while (admin_concert_choice != 3);
                    }
                    break;
                    case 4:
                    {
                        do
                        {
                            cout << "========================================\n";
                            cout << "|             ADMIN PANEL:             |\n";
                            cout << "========================================\n";
                            cout << "1. ADD STATIONS \n2. EDIT STATIONS\n3. DISPLAY STATIONS\n4.SORT THE STATIONS\n5.DELETE A Station_BUS\n6. EXIT\nSELECT AN OPTION: ";
                            cin >> admin_bus_choice;
                            string delete_station;
                            switch (admin_bus_choice)
                            {
                            case 1:
                            {
                                unordered_map<string, double> distances;
                                string station_name;
                                int connections;

                                cout << "ENTER THE STATION NAME : ";
                                cin.ignore(); // Clear the input buffer to handle the next getline properly
                                getline(cin, station_name);

                                cout << "ENTER THE NUMBER OF CONNECTED STATIONS : ";
                                cin >> connections;

                                for (int i = 0; i < connections; ++i)
                                {
                                    string connectedStation;
                                    double distance;
                                    cout << "ENTER THE NAME OF THE CONNECTED STATIONS AND THE DISTANCE : ";
                                    cin >> connectedStation >> distance;
                                    distances[connectedStation] = distance;
                                }

                                Bussystem.addStation(station_name, distances);
                                cout << "Station_BUS " << station_name << " ADDED SUCCESSFULLY.\n";
                            }
                            break;
                            case 2:
                                Bussystem.editStation();
                                cout << "===============================" << endl;
                                cout << "  Station_BUS EDITED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 3:
                                Bussystem.displayStations();
                                break;
                            case 4:
                                Bussystem.Sort();
                                cout << "===============================" << endl;
                                cout << "  Station_BUS SORTED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 5:

                                cout << "Enter the name of the Station_BUS you want to delete";
                                cin >> delete_station;
                                Bussystem.deleteStation(delete_station);
                                cout << "===============================" << endl;
                                cout << " Station_BUS DELETED SUCCESSFULLY\n";
                                cout << "===============================" << endl;
                                break;
                            case 6:
                                cout << "===============================" << endl;
                                cout << "    EXITING ADMIN PANEL.\n";
                                cout << "===============================" << endl;
                                break;
                            default:
                                cout << "===============================" << endl;
                                cout << "   INVALID CHOICE TRY AGAIN.\n";
                                cout << "===============================" << endl;
                            }
                        } while (admin_bus_choice != 6);
                    }
                    break;
                    }
                }
                else
                {
                    cout << "Access denied. Invalid User ID or Password.\n";
                }
            } while (admin_choice != 5);
            break;
        case 2:
            cout << "============\n";
            cout << "1. LOGIN\n";
            cout << "2. SIGNUP\n";
            cout << "============\n";
            cout << "ENTER YOUR CHOICE: ";
            cin >> customer_credentials_choice;
            if (customer_credentials_choice == 1)
            {

                cout << "Enter your User ID: ";
                cin >> customer_userId;
                cout << "Enter your Password: ";
                cin >> customer_password;

                // Authenticate customer
                if (authenticateCustomer(customer_userId, customer_password))
                {
                    cout << "========================================\n";
                    cout << "    Access granted to Customer Panel.\n";
                    cout << "========================================\n";
                    // Proceed to customer panel

                    do
                    {
                        cout << "ENTER YOUR CHOICE\n";
                        cout << "1. TRAIN SYSTEM\n";
                        cout << "2. STADIUM SYSTEM\n";
                        cout << "3. CONCERT SYSTEM\n";
                        cout << "4. BUS SYSTEM\n";
                        cout << "5. EXIT\n";
                        cin >> system_choice;
                        switch (system_choice)
                        {
                        case 1:
                        {
                            do
                            {
                                cout << "========================================\n";
                                cout << "        TRAIN TICKET RESERVATION        \n";
                                cout << "========================================\n";
                                cout << "1. Reserve Ticket\n2. Delete Ticket\n3. View Reservations\n4. Exit\n";
                                cout << "========================================\n";
                                cout << "Select an option: ";
                                cin >> train_choice;

                                switch (train_choice)
                                {
                                case 1:
                                    Trainsystem.reserveTicket();
                                    break;
                                case 2:
                                    Trainsystem.deleteTicket();
                                    break;
                                case 3:
                                    Trainsystem.displayReservations();
                                    break;
                                case 4:
                                    cout << "===========================================\n";
                                    cout << "EXITING THE TRAIN TICKET RESERVATION PANEL.\n";
                                    cout << "===========================================\n";
                                    break;
                                default:
                                    cout << "========================================\n";
                                    cout << "       INVALID CHOICE .TRY AGAIN\n";
                                    cout << "========================================\n";
                                }
                            } while (train_choice != 4);
                        }
                        break;
                        case 2:
                        {
                            do
                            {
                                cout << "========================================\n";
                                cout << "         MATCH TICKET RESERVATION        \n";
                                cout << "========================================\n";
                                cout << "1. Reserve Ticket\n2. View Reservations\n3. Delete Stadium_Reservation\n4. Exit\n";
                                cout << "Select an option: ";
                                cin >> stadium_choice;

                                switch (stadium_choice)
                                {
                                case 1:
                                {
                                    Stadiumsystem.displayUpcomingMatches();
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

                                    Stadiumsystem.reserveTicket(stadiumName, name, gender, age);
                                    break;
                                }
                                case 2:
                                {
                                    string TicketID;
                                    cout << "Enter ticket ID to view reservations: ";
                                    cin.ignore();
                                    getline(cin, TicketID);
                                    Stadiumsystem.displayReservations(TicketID);
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
                                    Stadiumsystem.deleteReservation(stadiumName, ticketID);
                                    break;
                                }
                                case 4:
                                {
                                    cout << "===========================================\n";
                                    cout << "EXITING THE MATCH TICKET RESERVATION PANEL.\n";
                                    cout << "===========================================\n";
                                    break;
                                }
                                default:
                                    cout << "===========================================\n";
                                    cout << "      Invalid choice. Try again.\n";
                                    cout << "===========================================\n";
                                    break;
                                }
                            } while (stadium_choice != 4);
                        }
                        break;
                        case 3:
                            do
                            {
                                cout << "========================================\n";
                                cout << "         CONCERT TICKET RESERVATION        \n";
                                cout << "========================================\n";
                                cout << "1. Reserve Ticket\n2. View Reservations\n3. Delete Reservation\n4. Exit\n";
                                cout << "Select an option: ";
                                cin >> concert_choice;

                                switch (concert_choice)
                                {
                                case 1:
                                {

                                    string concertName, name, gender;
                                    int age;
                                    cout << "Enter concert name: ";
                                    cin.ignore();
                                    getline(cin, concertName);
                                    cout << "Enter your name: ";
                                    getline(cin, name);
                                    cout << "Enter your gender: ";
                                    getline(cin, gender);
                                    cout << "Enter your age: ";
                                    cin >> age;

                                    Concertsystem.reserveTicket(concertName, name, gender, age);

                                    break;
                                }
                                case 2:
                                {
                                    string TicketID;
                                    cout << "Enter ticket ID to view reservations: ";
                                    cin.ignore();
                                    getline(cin, TicketID);
                                    Concertsystem.displayReservations(TicketID);
                                    break;
                                }
                                case 3:
                                {
                                    string concertName, ticketID;
                                    cout << "Enter concert name to delete reservation: ";
                                    cin.ignore();
                                    getline(cin, concertName);
                                    cout << "Enter ticket ID to delete: ";
                                    getline(cin, ticketID);
                                    Concertsystem.deleteReservation(concertName, ticketID);
                                    break;
                                }
                                case 4:
                                    cout << "EXITING THE CONCERT TICKETING PANEL.\n";
                                    break;
                                default:
                                    cout << "Invalid choice. Try again.\n";
                                }
                            } while (concert_choice != 4);
                            break;
                        case 4:
                        {
                            do
                            {
                                cout << "========================================\n";
                                cout << "         BUS TICKET Reservation_BUS       \n";
                                cout << "========================================\n";
                                cout << "1. Reserve Ticket\n2. Delete Ticket\n3. View Reservations\n4. Exit\n";
                                cout << "========================================\n";
                                cout << "Select an option: ";
                                cin >> bus_choice;

                                switch (bus_choice)
                                {
                                case 1:
                                    Bussystem.reserveTicket();
                                    break;
                                case 2:
                                    Bussystem.deleteTicket();
                                    break;
                                case 3:
                                    Bussystem.displayReservations();
                                    break;
                                case 4:
                                    cout << "===========================================\n";
                                    cout << "EXITING THE BUS TICKET Reservation_BUSPANEL.\n";
                                    cout << "===========================================\n";
                                    break;
                                default:
                                    cout << "========================================\n";
                                    cout << "       INVALID CHOICE .TRY AGAIN\n";
                                    cout << "========================================\n";
                                }
                            } while (bus_choice != 4);
                        }
                        break;
                        case 5:
                            cout << "EXITING THE CUSTOMER PANEL" << endl;
                            break;
                        }
                    } while (system_choice != 5);
                }
                else
                {
                    cout << "Access denied. Invalid User ID or Password.\n";
                    return 1; // Exit the program or handle accordingly
                }
            }
            else if (customer_credentials_choice == 2)
            {
                string name, userId, password;
                cout << "Enter your Name: ";
                cin >> name;
                cout << "Enter your User ID: ";
                cin >> userId;
                cout << "Enter your Password: ";
                cin >> password;

                // Signup customer
                if (!signupCustomer(name, userId, password))
                {
                    cout << "Signup failed. Please try again.\n";
                    break;
                }
                else
                {
                    cout << "Signup successful. Please login to continue.\n";
                    break;
                }
            }
            else
            {
                cout << "Invalid choice.\n";
                break;
            }

            break;
        case 3:
            cout << "EXITING THE TICKET MASTER" << endl;
            break;
        default:
            cout << "INVALID CHOICE\n";
            break;
        }
    } while (ROLE != 3);
}

//===========================================================================================================================================================================
//===========================================================================================================================================================================
//                                                                                     THE END
//===========================================================================================================================================================================
//===========================================================================================================================================================================
