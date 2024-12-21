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
//                                                           CLASS FOR BUS TICKET Reservation_TrainSYSTEM
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
    string busNumber; // Bus number
    Seats_BUS Seats_BUS[44];  // 44 Seats_BUS per bus
    bool isBooked;    // Bus booked status
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
    AVLNode_BUS *left;                    // Left child
    AVLNode_BUS *right;                   // Right child
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

// Class for Train Ticket Reservation_BUSSystem
class BusSystem
{
private:
    Station_BUS *StationHead_BUS;                                    // Linked list for stations
    AVLNode_BUS *reservationRoot_BUS;                                // Binary Search Tree for reservations
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
        cout << "    ENTER YOUR CURRENT Station_BUS NAME: \n";
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
            cout << "Station_BUS NOT FOUND [please try again]\n";
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
        cout << "  PLEASE ENTER YOUR Reservation_BUSOPTION  \n";
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
                Coach_no[coach_number - 1].Seats_BUS[seat_number - 1]};

                // Insert the Reservation_BUSinto the AVL
                reservationRoot_BUS = insertReservation(reservationRoot_BUS, newReservation_BUS);
            reservationMap_BUS[ticketID] = newReservation_BUS;
            cout << "========================================\n";
            cout << "       TICKET RESERVED SUCCESSFULY!\n";
            cout << "========================================\n";
            cout << "| TICKET ID:         | " << ticketID << endl;
            cout << "| NAME:              | " << name << endl;
            cout << "| GENDER:            | " << gender << endl;
            cout << "| DEPARTURE Station_BUS: | " << departureStation << endl;
            cout << "| ARRIVAL Station_BUS:   | " << arrivalStation << endl;
            cout << "| DISTANCE:          | " << distance << " km\n";
            cout << "| PRICE:             | " << prices << " PKR\n";
            cout << "| BUS NUMBER:        | " << coach_number << endl;
            cout << "| SEAT NUMBER:       | " << seat_number << endl;
            cout << "| DISTANCE:          | " << distance << " PKR\n";
            cout << "========================================\n";
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
//                                                          END OF BUS SYSTEM
//===========================================================================================================================================================================









//============================================================CONCERT RESERVATION SYSTEM================================================================================


struct Concert_Seats
{
    string seat_no; // Seat number
    bool isBooked;  // Seat booked status
};
struct Concert_Hall
{
    string name;
    string location;
    Concert_Seats Concert_seats[50];
    Concert_Hall *next;
    bool isBooked;
};
struct Concert_Event
{
    Concert_Hall hall[5];
    bool isBooked;
};
struct Concert_Reservation
{
    string name;
    string gender;
    string Concert_ticketID;
    string time;
    string Singer_name;
    string type;
    string date;
    double price;
    string location;
    Concert_Event OCUPATION;
};
struct Concert
{
    bool isBooked;
    string name;
    string type;
    string date;
    string time;
    string no_of_halls;
    string venue;
    double price;
    Concert *next;
    Concert_Reservation *Concert_reservation;
};

struct Concert_AVLNode
{
    Concert_Reservation *Concert_reservation; // Pointer to the Concert_reservation
    Concert_AVLNode *left;            // Left child
    Concert_AVLNode *right;           // Right child
    int height;               // Height of the node
};

// Function to get the height of the tree
int height(Concert_AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Function to get the balance factor of the node
int getBalance(Concert_AVLNode *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotate
Concert_AVLNode *rightRotate(Concert_AVLNode *y)
{
    Concert_AVLNode *x = y->left;
    Concert_AVLNode *T2 = x->right;

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
Concert_AVLNode *leftRotate(Concert_AVLNode *x)
{
    Concert_AVLNode *y = x->right;
    Concert_AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}
// Structure for tree node (Concert_Seats and Cabins)

// Class for Train Ticket Concert_Reservation System
class CONCERT
{
private:
    Concert *stationHead;                                // Linked list for stations
    Concert_AVLNode *Concert_reservationRoot;                            // Binary Search Tree for Concert_reservations
    unordered_map<string, Concert_Reservation *> Concert_reservationMap; // Map for quick ticket lookup
    string generateUniqueID()
    {
        srand(time(0));
        return "TICKET-" + to_string(rand() % 10000 + 1);
    }
    Concert_AVLNode *insertConcert_Reservation(Concert_AVLNode *node, Concert_Reservation *Concert_reservation)
    {
        // Normal BST insert
        if (node == nullptr)
        {
            Concert_AVLNode *newNode = new Concert_AVLNode();
            newNode->Concert_reservation = Concert_reservation;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1; // New node is initially added at leaf
            return newNode;
        }

        if (Concert_reservation->Concert_ticketID < node->Concert_reservation->Concert_ticketID)
            node->left = insertConcert_Reservation(node->left, Concert_reservation);
        else if (Concert_reservation->Concert_ticketID > node->Concert_reservation->Concert_ticketID)
            node->right = insertConcert_Reservation(node->right, Concert_reservation);
        else // Duplicate ticket IDs are not allowed
            return node;

        // Update the height of this ancestor node
        node->height = 1 + max(height(node->left), height(node->right));

        // Get the balance factor of this ancestor node to check whether
        // this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && Concert_reservation->Concert_ticketID < node->left->Concert_reservation->Concert_ticketID)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && Concert_reservation->Concert_ticketID > node->right->Concert_reservation->Concert_ticketID)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && Concert_reservation->Concert_ticketID > node->left->Concert_reservation->Concert_ticketID)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && Concert_reservation->Concert_ticketID < node->right->Concert_reservation->Concert_ticketID)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // Return the (unchanged) node pointer
        return node;
    }
    // Insert Concert_reservation into BST
    Concert_AVLNode *deleteConcert_Reservation(Concert_AVLNode *root, string Concert_ticketID)
    {
        if (root == nullptr)
            return root;

        // Perform standard BST delete
        if (Concert_ticketID < root->Concert_reservation->Concert_ticketID)
            root->left = deleteConcert_Reservation(root->left, Concert_ticketID);
        else if (Concert_ticketID > root->Concert_reservation->Concert_ticketID)
            root->right = deleteConcert_Reservation(root->right, Concert_ticketID);
        else
        {
            // Node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                Concert_AVLNode *temp = root->left ? root->left : root->right;

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
                Concert_AVLNode *temp = root->right;
                while (temp->left != nullptr)
                    temp = temp->left;

                // Copy the inorder successor's data to this node
                root->Concert_reservation = temp->Concert_reservation;

                // Delete the inorder successor
                root->right = deleteConcert_Reservation(root->right, temp->Concert_reservation->Concert_ticketID);
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

    // In-order traversal to display Concert_reservations
    void displayConcert_ReservationsInOrder(Concert_AVLNode *root)
    {
        if (!root)
            return;

        displayConcert_ReservationsInOrder(root->left);

        if (root->Concert_reservation->OCUPATION.isBooked == true)
        {
            cout << "========================================\n";
            cout << "            EVENT RESERVATION           \n";
            cout << "========================================\n";
            cout << "| TICKET ID:            | " << root->Concert_reservation->Concert_ticketID << endl;
            cout << "| NAME:                 | " << root->Concert_reservation->name << endl;
            cout << "| GENDER:               | " << root->Concert_reservation->gender << endl;
            cout << "| TYPE:                 | " << root->Concert_reservation->type << endl;
            cout << "| SINGER:               | " << root->Concert_reservation->Singer_name << endl;
            cout << "| LOCATION:             | " << root->Concert_reservation->location << endl;
            cout << "| DATE:                 | " << root->Concert_reservation->date << endl;
            cout << "| TIME:                 | " << root->Concert_reservation->time << endl;
            cout << "| PRICE:                | " << (root->Concert_reservation->price) * 250 << endl;
            cout << "========================================\n";
        }
        else if (root->Concert_reservation->OCUPATION.isBooked == false)
        {
            for (int j = 0; j < 5; j++)
            {
                if (root->Concert_reservation->OCUPATION.hall[j].isBooked == true)
                {
                    cout << "========================================\n";
                    cout << "            HALL RESERVATION           \n";
                    cout << "========================================\n";
                    cout << "| TICKET ID:            | " << root->Concert_reservation->Concert_ticketID << endl;
                    cout << "| NAME:                 | " << root->Concert_reservation->name << endl;
                    cout << "| GENDER:               | " << root->Concert_reservation->gender << endl;
                    cout << "| EVENT TYPE:           | " << root->Concert_reservation->type << endl;
                    cout << "| SINGER NAME:          | " << root->Concert_reservation->Singer_name << endl;
                    cout << "| LOCATION:             | " << root->Concert_reservation->location << endl;
                    cout << "| HALL NAME:            | " << root->Concert_reservation->OCUPATION.hall->name << endl;
                    cout << "| HALL LOCATION:        | " << root->Concert_reservation->OCUPATION.hall->location << endl;
                    cout << "| DATE :                | " << root->Concert_reservation->date << endl;
                    cout << "| TIME :                | " << root->Concert_reservation->time << endl;
                    cout << "| SEAT NUMBER:          | " << j + 1 << endl;
                    cout << "| PRICE:                | " << (root->Concert_reservation->price) * 250 << " PKR\n";
                    cout << "========================================\n";
                }
            }
        }
        displayConcert_ReservationsInOrder(root->right);
    }

public:
    CONCERT() : stationHead(nullptr), Concert_reservationRoot(nullptr) {}

    //===========================================================================Admin functions================================================================================================
    void addConcert(bool booked, const string &name, const string &type, const string &date, const string &time, const string &venue, string no_of_halls, double price)
    {
        Concert *newConcert = new Concert{booked, name, type, date, time, venue, no_of_halls, price};
        if (!stationHead)
        {
            stationHead = newConcert;
            return;
        }
        Concert *temp = stationHead;
        while (temp->next)
            temp = temp->next;
        temp->next = newConcert;
    }
    // Admin: Display all stations
    void displayConcerts()
    {
        Concert *temp = stationHead;
        if (!temp)
        {
            cout << "No Concerts available.\n";
            return;
        }
        cout << "========================================\n";
        cout << "          AVAILABLE CONCERTS:\n";
        cout << "========================================\n";
        while (temp)
        {
            cout << "NAME  :" << temp->name << "\n";
            cout << "TYPE  :" << temp->type << "\n";
            cout << "DATE  :" << temp->date << "\n";
            cout << "TIME  :" << temp->time << "\n";
            cout << "VENUE :" << temp->venue << "\n";
            cout << "PRICE :" << temp->price << "\n";
            temp = temp->next;
        }
        cout << "========================================\n";
    }

    // Admin: Edit a station
    void editConcert()
    {
        displayConcerts(); // Display all concerts to the user
        string concertName;
        cout << "Enter the name of the concert to edit: ";
        cin >> concertName;

        Concert *temp = stationHead;
        while (temp && temp->name != concertName)
            temp = temp->next;

        if (!temp)
        {
            cout << "Concert not found.\n";
            return;
        }

        int choice;
        do
        {
            cout << "\nEditing concert: " << temp->name << endl;
            cout << "Select the property to edit:\n";
            cout << "1. Concert Name\n";
            cout << "2. Date\n";
            cout << "3. Time\n";
            cout << "4. Venue\n";
            cout << "5. Number of Concert_Halls\n";
            cout << "6. Price\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string newName;
                cout << "Enter new concert name: ";
                cin >> newName;
                temp->name = newName;
                cout << "Concert name updated successfully.\n";
                break;
            }
            case 2:
            {
                string newDate;
                cout << "Enter new date (YYYY-MM-DD): ";
                cin >> newDate;
                temp->date = newDate;
                cout << "Concert date updated successfully.\n";
                break;
            }
            case 3:
            {
                string newTime;
                cout << "Enter new time (HH:MM): ";
                cin >> newTime;
                temp->time = newTime;
                cout << "Concert time updated successfully.\n";
                break;
            }
            case 4:
            {
                string newVenue;
                cout << "Enter new venue: ";
                cin >> newVenue;
                temp->venue = newVenue;
                cout << "Concert venue updated successfully.\n";
                break;
            }
            case 5:
            {
                string newNoOfConcert_Halls;
                cout << "Enter new number of halls: ";
                cin >> newNoOfConcert_Halls;
                temp->no_of_halls = newNoOfConcert_Halls;
                cout << "Number of halls updated successfully.\n";
                break;
            }
            case 6:
            {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                temp->price = newPrice;
                cout << "Concert price updated successfully.\n";
                break;
            }
            case 7:
            {
                cout << "Exiting edit menu.\n";
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 7);
    }
    void bubbleSort()
    {
        if (!stationHead)
            return; // If the list is empty, do nothing

        bool swapped;
        do
        {
            swapped = false;
            Concert *current = stationHead;

            while (current->next != nullptr)
            {
                // Compare based on concert name (you can change this to date or time as needed)
                if (current->name > current->next->name)
                {
                    // Swap the concerts
                    swap(current->name, current->next->name);
                    swap(current->date, current->next->date);
                    swap(current->time, current->next->time);
                    swap(current->venue, current->next->venue);
                    swap(current->no_of_halls, current->next->no_of_halls);
                    swap(current->price, current->next->price);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }
    // Function to delete a specific station from the linked list
    void deleteConcert(const string &concertName)
    {
        Concert *temp = stationHead; // Start from the head of the concert list
        Concert *prev = nullptr;     // To keep track of the previous node

        // Traverse the list to find the concert
        while (temp != nullptr && temp->name != concertName)
        {
            prev = temp;       // Move prev to current
            temp = temp->next; // Move to the next concert
        }

        // If the concert was not found
        if (temp == nullptr)
        {
            cout << "Concert not found.\n";
            return;
        }

        // If the concert is the head of the list
        if (prev == nullptr)
        {
            stationHead = temp->next; // Change head to the next concert
        }
        else
        {
            prev->next = temp->next; // Unlink the concert from the list
        }

        delete temp; // Free memory
        cout << "Concert '" << concertName << "' deleted successfully.\n";
    }

    //================================================================================================================================================================================================================================
    void reserveTicket()
    {
        displayConcerts();
        int choice;
        string concert_name;
        Concert *temp = stationHead;
        cout << "Enter the name of the concert: ";
        cin.ignore();
        getline(cin, concert_name);

        // Find the concert
        while (temp && temp->name != concert_name)
        {
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "CONCERT NOT FOUND [please try again]\n";
            return;
        }

        if (temp->isBooked)
        {
            cout << "CONCERT IS FULLY BOOKED\n";
            return;
        }
        else
        {
            cout << "========================================\n";
            cout << "           CONCERT DETAILS" << endl;
            cout << "========================================\n";
            cout << "NAME  :" << temp->name << "\n";
            cout << "TYPE  :" << temp->type << "\n";
            cout << "DATE  :" << temp->date << "\n";
            cout << "TIME  :" << temp->time << "\n";
            cout << "VENUE :" << temp->venue << "\n";
            cout << "PRICE :" << temp->price << "\n";
            cout << "========================================\n";
        }

        int choice2;
        cout << "========================================\n";
        cout << "          ENTER YOUR CHOICE :\n";
        cout << "========================================\n";
        cout << "1. BOOK A SEAT\n";
        cout << "2. BOOK A HALL\n";
        cout << "3. BOOK AN EVENT\n";
        cout << "Enter your choice: ";

        // Validate input for choice2
        while (!(cin >> choice2) || choice2 < 1 || choice2 > 3)
        {
            cout << "INVALID CHOICE. Please enter 1, 2, or 3: ";
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }

        int hall_no;
        int seat_no;

        switch (choice2)
        {
        case 1: // Book a seat
            if (temp->isBooked)
            {
                cout << "SORRY, THE CONCERT IS FULLY BOOKED\n";
                return;
            }
            cout << "AVAILABLE HALLS\n";
            for (int i = 0; i < 5; i++)
            {
                if (!temp->Concert_reservation->OCUPATION.hall[i].isBooked)
                {
                    cout << "HALL NUMBER :" << i + 1 << endl;
                }
            }
            cout << "ENTER THE HALL NUMBER: ";
            cin >> hall_no;
            if (hall_no < 1 || hall_no > 5 || temp->Concert_reservation->OCUPATION.hall[hall_no - 1].isBooked)
            {
                cout << "INVALID HALL NUMBER [please enter a number from the above given list]\n";
                return;
            }
            else
            {
                cout << "AVAILABLE SEATS\n";
                for (int i = 0; i < 50; i++)
                {
                    if (!temp->Concert_reservation->OCUPATION.hall[hall_no - 1].Concert_seats[i].isBooked)
                    {
                        cout << "SEAT NUMBER :" << i + 1 << endl;
                    }
                }
                cout << "ENTER THE SEAT NUMBER: ";
                cin >> seat_no;
                if (seat_no < 1 || seat_no > 50 || temp->Concert_reservation->OCUPATION.hall[hall_no - 1].Concert_seats[seat_no - 1].isBooked)
                {
                    cout << "INVALID SEAT NUMBER\n";
                    return;
                }
                else
                {
                    temp->Concert_reservation->OCUPATION.hall[hall_no - 1].Concert_seats[seat_no - 1].isBooked = true;
                    cout << "SEAT BOOKED SUCCESSFULLY\n";
                }
            }
            break;

        case 2: // Book a hall
            if (temp->Concert_reservation->OCUPATION.isBooked)
            {
                cout << "SORRY, THE CONCERT IS FULLY BOOKED\n";
                return;
            }
            cout << "AVAILABLE HALLS\n";
            for (int i = 0; i < 5; i++)
            {
                if (!temp->Concert_reservation->OCUPATION.hall[i].isBooked)
                {
                    cout << "HALL NUMBER :" << i + 1 << endl;
                }
            }
            cout << "ENTER THE HALL NUMBER: ";
            cin >> hall_no;
            if (hall_no < 1 || hall_no > 5 || temp->Concert_reservation->OCUPATION.hall[hall_no - 1].isBooked)
            {
                cout << "INVALID HALL NUMBER [please enter a number from the above given list]\n";
                return;
            }
            else
            {
                temp->Concert_reservation->OCUPATION.hall[hall_no - 1].isBooked = true;
                cout << "HALL BOOKED SUCCESSFULLY\n";
            }
            break;

        case 3: // Book an event
            if (temp->Concert_reservation->OCUPATION.isBooked)
            {
                cout << "SORRY, THE CONCERT IS FULLY BOOKED\n";
                return;
            }
            temp->Concert_reservation->OCUPATION.isBooked = true;
            cout << "EVENT BOOKED SUCCESSFULLY\n";
            break;

        default:
            cout << "INVALID CHOICE\n";
            break;
        }
    }

    // User: Delete a Concert_reservation
    void deleteTicket()
    {
        string Concert_ticketID;
        cout << "ENTER THE TICKET ID YOU WANT TO DELETE: ";
        cin >> Concert_ticketID;

        if (Concert_reservationMap.find(Concert_ticketID) == Concert_reservationMap.end())
        {
            cout << "Ticket not found.\n";
            return;
        }

        Concert_reservationRoot = deleteConcert_Reservation(Concert_reservationRoot, Concert_ticketID);
        Concert_reservationMap.erase(Concert_ticketID);
        cout << "Ticket deleted successfully.\n";
    }

    // User: Display all Concert_reservations
    void displayConcert_Reservations()
    {
        if (!Concert_reservationRoot)
        {
            cout << "NO RESERVATIONS FOUND.\n";
            return;
        }
        displayConcert_ReservationsInOrder(Concert_reservationRoot);
    }
};



//===========================================================================================================================================================================
//                                                          END OF CONCERT SYSTEM
//===========================================================================================================================================================================







//============================================================STADIUM RESERVATION SYSTEM================================================================================




