//1.dijakstras workflow
/*#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
using namespace std;
// Define a structure to represent edges with a destination and weight
struct Edge {
    string destination;
    int weight;
};

// Define a graph as an adjacency list
unordered_map<string, vector<Edge>> metroNetwork =
{
    {"A", {{"B", 2}, {"C", 5}}},
    {"B", {{"A", 2}, {"C", 1}, {"D", 4}}},
    {"C", {{"A", 5}, {"B", 1}, {"D", 2}}},
    {"D", {{"B", 4}, {"C", 2}}}
};

// Function to implement Dijkstra's algorithm
int dijkstra(const string& start, const string& end) {
    // Priority queue to store {distance, node}, smallest distance on top
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Map to store the minimum distance to each node
    unordered_map<string, int> distances;

    // Initialize all distances to infinity
    for (const auto& node : metroNetwork) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start] = 0;

    // Add the starting node to the queue
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        // If we reach the destination, return the distance
        if (currentNode == end) {
            return currentDistance;
        }

        // Traverse neighbors
        for (const Edge& neighbor : metroNetwork[currentNode]) {
            int newDistance = currentDistance + neighbor.weight;
            if (newDistance < distances[neighbor.destination]) {
                distances[neighbor.destination] = newDistance;
                pq.push({newDistance, neighbor.destination});
            }
        }
    }

    // If no path is found, return -1
    return -1;
}

int main() {
    string source, destination;

    cout << "Enter the source station: ";
    cin >> source;

    cout << "Enter the destination station: ";
    cin >> destination;

    if (metroNetwork.find(source) == metroNetwork.end() || metroNetwork.find(destination) == metroNetwork.end()) {
        cout << "Invalid stations entered!" << endl;
        return 1;
    }

    int shortestPath = dijkstra(source, destination);

    if (shortestPath != -1) {
        cout << "The shortest path from " << source << " to " << destination << " is: " << shortestPath << endl;
    } else {
        cout << "No path exists between " << source << " and " << destination << "." << endl;
    }

    return 0;
}
A --2--> B --1--> C --2--> D
|        |              ^
5        4              |
v        v              |
C       D <--------------
*/



// 2.security workflow
/*#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// Function to add passenger data
void addPassenger(unordered_map<string, string>& database, const string& id, const string& name) {
    database[id] = name;
    cout << "Passenger added: " << name << " with ID: " << id << endl;
}

// Function to verify passenger data
void verifyPassenger(const unordered_map<string, string>& database, const string& id) {
    auto it = database.find(id);
    if (it != database.end()) {
        cout << "Verification Successful! Passenger: " << it->second << endl;
    } else {
        cout << "Verification Failed! No passenger found with ID: " << id << endl;
    }
}

// Function to delete passenger data
void deletePassenger(unordered_map<string, string>& database, const string& id) {
    if (database.erase(id)) {
        cout << "Passenger with ID: " << id << " has been removed." << endl;
    } else {
        cout << "No passenger found with ID: " << id << endl;
    }
}

int main() {
    unordered_map<string, string> passengerDatabase;
    int choice;
    string id, name;

    cout << "=== Security Workflow: Passenger Identity Verification ===" << endl;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Passenger\n";
        cout << "2. Verify Passenger\n";
        cout << "3. Delete Passenger\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Passenger ID: ";
                cin >> id;
                cout << "Enter Passenger Name: ";
                cin.ignore();
                getline(cin, name);
                addPassenger(passengerDatabase, id, name);
                break;
            case 2:
                cout << "Enter Passenger ID to verify: ";
                cin >> id;
                verifyPassenger(passengerDatabase, id);
                break;
            case 3:
                cout << "Enter Passenger ID to delete: ";
                cin >> id;
                deletePassenger(passengerDatabase, id);
                break;
            case 4:
                cout << "Exiting Security Workflow." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
*/

//3.Route planning workflow
/*#include <iostream>   //DRAFT A
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Define a structure for an edge
struct Edge {
    int destination;
    int weight;
};

// Define a structure to compare the edges for the priority queue
struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

// Function to implement Prim's algorithm
void prim(int nodes, vector<vector<Edge>>& graph) {
    vector<int> key(nodes, INT_MAX);  // To store minimum weight of edges
    vector<bool> inMST(nodes, false); // To track nodes already included in MST
    priority_queue<Edge, vector<Edge>, Compare> pq;

    key[0] = 0;  // Start from the first node
    pq.push({0, 0});  // {node, weight}

    while (!pq.empty()) {
        int u = pq.top().destination;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        // Iterate through all adjacent nodes of u
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // If v is not in MST and weight of u-v is smaller than current key[v]
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({v, key[v]});
            }
        }
    }

    // Output the MST weights
    int totalWeight = 0;
    for (int i = 0; i < nodes; ++i) {
        if (key[i] != INT_MAX) {
            totalWeight += key[i];
        }
    }
    cout << "Minimum cost to connect all cities (MST): " << totalWeight << endl;
}

int main() {
    int nodes, edges;

    cout << "Enter number of nodes (cities): ";
    cin >> nodes;
    cout << "Enter number of edges (connections between cities): ";
    cin >> edges;

    // Create an adjacency list for the graph
    vector<vector<Edge>> graph(nodes);

    cout << "Enter the edges in the format: node1 node2 weight" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;

        // Since the graph is undirected, add edge in both directions
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    // Call Prim's algorithm to find MST
    prim(nodes, graph);

    return 0;
}

#include <iostream>    //DRAFT B
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Define a structure for an edge
struct Edge {
    int destination;
    int weight;
};

// Define a structure to compare the edges for the priority queue
struct Compare {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight > b.weight;
    }
};

// Function to implement Prim's algorithm
void prim(int nodes, vector<vector<Edge>>& graph) {
    vector<int> key(nodes, INT_MAX);  // To store minimum weight of edges
    vector<bool> inMST(nodes, false); // To track nodes already included in MST
    priority_queue<Edge, vector<Edge>, Compare> pq;

    key[0] = 0;  // Start from the first node
    pq.push({0, 0});  // {node, weight}

    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().destination;
        pq.pop();

        if (inMST[u]) continue;  // If the node is already in MST, skip it
        inMST[u] = true;
        totalWeight += key[u];   // Add the weight of this edge to MST total

        // Iterate through all adjacent nodes of u
        for (const Edge& edge : graph[u]) {
            int v = edge.destination;
            int weight = edge.weight;

            // If v is not in MST and weight of u-v is smaller than current key[v]
            if (!inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({v, key[v]});
            }
        }
    }

    cout << "Minimum cost to connect all cities (MST): " << totalWeight << endl;
}

int main() {
    int nodes, edges;

    cout << "Enter number of nodes (cities): ";
    cin >> nodes;
    cout << "Enter number of edges (connections between cities): ";
    cin >> edges;

    // Create an adjacency list for the graph
    vector<vector<Edge>> graph(nodes);

    cout << "Enter the edges in the format: node1 node2 weight" << endl;
    for (int i = 0; i < edges; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;

        // Since the graph is undirected, add edge in both directions
        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    // Call Prim's algorithm to find MST
    prim(nodes, graph);

    return 0;
}
*/

//4.Sorting by population density
/*#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Structure to represent a city with name and population density
struct City {
    string name;
    int populationDensity;
};

// QuickSort function to sort cities based on population density (ascending order)
void quickSort(vector<City>& cities, int low, int high) {
    if (low < high) {
        // Partition the cities into two sub-arrays based on population density
        int pivot = cities[high].populationDensity;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (cities[j].populationDensity < pivot) {
                i++;
                swap(cities[i], cities[j]);
            }
        }
        swap(cities[i + 1], cities[high]);

        // Recursively apply quickSort to the sub-arrays
        quickSort(cities, low, i);
        quickSort(cities, i + 2, high);
    }
}

// Function to display the sorted cities based on population density
void displayCities(const vector<City>& cities) {
    cout << "\nCities sorted by population density (ascending order):\n";
    for (const auto& city : cities) {
        cout << city.name << " - Population Density: " << city.populationDensity << endl;
    }
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<City> cities(n);

    cout << "Enter city name and population density for each city:\n";
    for (int i = 0; i < n; i++) {
        cout << "City " << i + 1 << " Name: ";
        cin >> cities[i].name;
        cout << "City " << i + 1 << " Population Density: ";
        cin >> cities[i].populationDensity;
    }

    // Apply QuickSort to sort cities by population density
    quickSort(cities, 0, n - 1);

    // Display the sorted list of cities
    displayCities(cities);

    return 0;
}
*/

//5.Passenger Comfort Workflow
/*#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<int> BIT;
    int n;

public:
    FenwickTree(int size) {
        n = size;
        BIT.assign(n + 1, 0);  // Initialize Fenwick Tree with 0 (indicating all seats are available)
    }

    // Function to update a seat (allocate a seat)
    void update(int index, int value) {
        while (index <= n) {
            BIT[index] += value;
            index += index & (-index);
        }
    }

    // Function to query the sum (e.g., available seats) up to a given index
    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & (-index);
        }
        return sum;
    }

    // Function to find the first available seat
    int findAvailableSeat() {
        for (int i = 1; i <= n; ++i) {
            if (query(i) == 1) {  // Seat available (value 1 means available)
                return i;
            }
        }
        return -1; // No available seat
    }
};

int main() {
    int numSeats;

    cout << "Enter number of seats: ";
    cin >> numSeats;

    FenwickTree fenwick(numSeats);

    // Initialize all seats as available (1 means available)
    for (int i = 1; i <= numSeats; ++i) {
        fenwick.update(i, 1);  // Set each seat to be available initially
    }

    while (true) {
        cout << "\nPassenger Seat Allocation Menu:\n";
        cout << "1. Allocate Seat\n";
        cout << "2. Query Available Seats\n";
        cout << "3. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            // Allocate a seat to the next passenger
            int availableSeat = fenwick.findAvailableSeat();
            if (availableSeat != -1) {
                cout << "Allocating seat " << availableSeat << " to passenger.\n";
                fenwick.update(availableSeat, -1); // Mark the seat as occupied (value 0)
            } else {
                cout << "No seats available!\n";
            }
        } else if (choice == 2) {
            // Query number of available seats
            int availableSeats = fenwick.query(numSeats);
            cout << "Available seats: " << availableSeats << endl;
        } else if (choice == 3) {
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
*/

//6.Train Scheduling Workflow
/*#include <iostream> //needs improvement
#include <vector>
using namespace std;

// Train struct to hold train details
struct Train {
    string trainName;
    int departureTime;  // Departure time in minutes from midnight
    int arrivalTime;    // Arrival time in minutes from midnight

    Train(string name, int depTime, int arrTime)
        : trainName(name), departureTime(depTime), arrivalTime(arrTime) {}
};

// Function to swap two trains
void swap(Train &a, Train &b) {
    Train temp = a;
    a = b;
    b = temp;
}

// Partition function for QuickSort
int partition(vector<Train>& trains, int low, int high) {
    int pivot = trains[high].departureTime;
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (trains[j].departureTime < pivot) {
            ++i;
            swap(trains[i], trains[j]);
        }
    }
    swap(trains[i + 1], trains[high]);
    return i + 1;
}

// QuickSort algorithm
void quickSort(vector<Train>& trains, int low, int high) {
    if (low < high) {
        int pi = partition(trains, low, high);
        quickSort(trains, low, pi - 1);
        quickSort(trains, pi + 1, high);
    }
}

// Function to display the train schedule
void displayTrainSchedule(const vector<Train>& trains) {
    cout << "\nTrain Schedule (sorted by departure time):\n";
    cout << "Train Name\tDeparture Time\tArrival Time\n";
    for (const auto& train : trains) {
        cout << train.trainName << "\t\t"
             << train.departureTime << "\t\t"
             << train.arrivalTime << "\n";
    }
}

int main() {
    // Sample input of trains (train name, departure time in minutes, arrival time in minutes)
    vector<Train> trains = {
        Train("Train A", 600, 720),  // 10:00 AM to 12:00 PM
        Train("Train B", 450, 630),  // 7:30 AM to 10:30 AM
        Train("Train C", 540, 680),  // 9:00 AM to 11:20 AM
        Train("Train D", 300, 450),  // 5:00 AM to 7:30 AM
        Train("Train E", 900, 1020)  // 3:00 PM to 5:00 PM
    };

    // Sort the trains by departure time using QuickSort
    quickSort(trains, 0, trains.size() - 1);

    // Display the sorted train schedule
    displayTrainSchedule(trains);

    return 0;
}
*/

//7.Booking Management Workflow
/*#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Define the Passenger struct
struct Passenger {
    string name;
    int waitTime;  // Wait time in minutes
    int priority;  // Priority based on wait time

    // Constructor to initialize a passenger
    Passenger(string n, int wt) : name(n), waitTime(wt), priority(wt) {}

    // Overloading the < operator to create a priority based on waitTime
    bool operator<(const Passenger& other) const {
        // Higher wait time should have higher priority (max-heap behavior)
        return waitTime < other.waitTime;
    }
};

// Function to simulate booking process
void processBookings(priority_queue<Passenger>& pq) {
    cout << "\nBooking Process:\n";
    while (!pq.empty()) {
        Passenger current = pq.top();  // Get the passenger with highest priority
        pq.pop();  // Remove the passenger from the queue
        cout << "Booking for " << current.name << " with wait time " << current.waitTime << " minutes is processed.\n";
    }
}

int main() {
    // Creating a priority queue for passengers based on their wait time (longer wait time = higher priority)
    priority_queue<Passenger> pq;

    // Sample passengers (name, wait time in minutes)
    pq.push(Passenger("Alice", 30));
    pq.push(Passenger("Bob", 15));
    pq.push(Passenger("Charlie", 45));
    pq.push(Passenger("David", 20));
    pq.push(Passenger("Eve", 50));

    // Process the bookings
    processBookings(pq);

    return 0;
}
*/

