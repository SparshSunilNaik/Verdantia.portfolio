#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <limits>
#include <iomanip>
#include <cmath>
#include <utility>
#include<tuple>
#include<fstream>
#include<string>
using namespace std;

// Alias for simplicity
using pii=pair<int,double>;
const int INF=numeric_limits<int>::max();



// Railway Network Graph
class RailwayNetwork
{
private:
    vector<vector<pii>> adjacencyList;
    int numStations;

public:

    RailwayNetwork(int n) : numStations(n), adjacencyList(n) {}

    void setStaticGraph();

    void addConnection(int u, int v, double weight);

    double calculateFare(int source, int destination);

    void dist(int source, int destination);

    vector<double> dijkstra(int source);

    void displayGraph();
};




// Security Workflow
class SecurityWorkflow
{
private:

    unordered_map<string, bool> passengerDB;

public:

    void addPassenger(string id);

    void removePassenger(string id);

    void verifyPassenger(string id);

    void viewAllPassengers();
};



//RoutePlanning Workflow
class RoutePlanningWorkflow
{
public:

    void primsAlgorithm(int numStations, const vector<vector<pair<int, double>>>& graph);
};





//Metro Time Scheduling
class MetroLine
{
private:

    int numStations;
    double length;
    int normalTrains;
    int peakTrains;
    double avgSpeed;
    int normalHeadway = 5;
    int peakHeadway = 3;
    double dwellTime = 1;
    double buffer = 1.1;

public:

    MetroLine(int stations, double lineLength, double speed = 35)
        : numStations(stations), length(lineLength), avgSpeed(speed) {
        calculateRequiredTrains();}

    void calculateRequiredTrains();

    void displayTimings();

private:

    void displayTimings(int startHour, int endHour, int frequency);
};




class LostAndFoundWorkflow
{
private:

    string fileName;

    bool bruteForceSearch(const string& target);

    void addItemToFile(const string& item);
public:

    LostAndFoundWorkflow(const string& fileName) : fileName(fileName) {}

    void menu();
};





void RailwayNetwork::setStaticGraph()
{
    vector<tuple<int, int, double>> connections =
    {
        {0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {0, 4, 1.0},
        {1, 5, 2.0}, {2, 6, 1.5}, {3, 7, 2.0}, {4, 8, 1.5},
        {5, 9, 1.5}, {6, 10, 2.0}, {7, 11, 1.5}, {8, 12, 2.0},
        {9, 13, 2.0}, {10, 14, 3.0}, {11, 15, 2.0}, {12, 16, 3.0},
        {13, 17, 3.0}, {14, 18, 5.0}, {15, 19, 3.0}, {17, 20, 5.0},
        {18, 21, 4.0}, {19, 22, 2.0}, {20, 23, 4.0}, {22, 24, 4.0},
        {24, 25, 5.0}, {25, 26, 6.0}  // fixed connection railway network
    };

    for (const auto& conn : connections)
    {
        int u,v;
        double weight;
        tie(u,v,weight)=conn;
        addConnection(u,v,weight);
    }
}






void RailwayNetwork::addConnection(int u,int v,double weight)
{
    adjacencyList[u].push_back({v,weight});
    adjacencyList[v].push_back({u,weight});
}







double RailwayNetwork::calculateFare(int source, int destination)
{
    if(source<0 || source>=numStations || destination<0 || destination>=numStations)
    {
        cout<<"Invalid station numbers!"<<endl;
        return -1;
    }

    vector<double> distances=dijkstra(source);

    if(distances[destination]==INF)
    {
        cout<<"No path exists between these stations!"<<endl;
        return -1;
    }

    double fare=distances[destination]*6.0;
    cout<<"Total distance: "<<fixed<<setprecision(2)<<distances[destination]<<" km\n";
    // cout << "Rate per km: 6.00\n";
    return fare;
}






void RailwayNetwork::dist(int source, int destination)
{
    if (source<0 || source>=numStations || destination<0 || destination>=numStations)
    {
        cout<<"Invalid station numbers!"<<endl;
    }

    vector<double> distances=dijkstra(source);
    if (distances[destination]==INF)
    {
        cout<<"No path exists between these stations!"<<endl;
    }
        cout<< "Total distance: "<<fixed<<setprecision(2)<<distances[destination]<<" km\n";

}






vector<double> RailwayNetwork::dijkstra(int source)
{
    vector<double> distance(numStations,INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    distance[source]=0;

    pq.push({0,source});

    while(!pq.empty())
    {
        double dist=pq.top().first;

        int u=pq.top().second;
        pq.pop();

        if (dist>distance[u])
            continue;

        for (const auto& neighbor:adjacencyList[u])
        {
            int v=neighbor.first;
            double weight=neighbor.second;
            if (distance[u]+weight<distance[v])
            {
                distance[v]=distance[u]+weight;

                pq.push({distance[v],v});
            }
        }
    }
    return distance;
}







void RailwayNetwork::displayGraph()
{
    for (int i=0;i<numStations;++i)
    {
        cout<<"Station "<<i+1<<": ";
        for (const auto& neighbor : adjacencyList[i])
        {
            cout<<"("<<neighbor.first +1<<", "<<fixed<<setprecision(1)<<neighbor.second +1<<") ";
        }
        cout<<endl;
    }
}




void SecurityWorkflow::addPassenger(string id)
{
    passengerDB[id]=true;
    cout<<"Passenger with ID: "<<id<<" added.\n";
}







void SecurityWorkflow::removePassenger(string id)
{
    if (passengerDB.find(id)!=passengerDB.end())
    {
        passengerDB.erase(id);
        cout<<"Passenger with ID: "<<id<<" removed.\n";
    }
    else
    {
        cout<<"Passenger with ID: "<<id<<" not found.\n";
    }
}






void SecurityWorkflow::verifyPassenger(string id)
{
    if (passengerDB.find(id) != passengerDB.end())
    {
        cout<<"Passenger with ID: "<<id<<" verified.\n";
    }
    else
    {
        cout<<"Passenger with ID: "<<id<<" not found.\n";
    }
}






void SecurityWorkflow::viewAllPassengers()
{
    string password;
    cout<<"Enter password to view passenger details: ";
    cin>>password;

    if (password=="123")
    {
        if(passengerDB.empty())
        {
            cout<<"No passengers have been added yet.\n";
        }
        else
        {
            cout<<"\nPassenger Details:\n";
            for(const auto& passenger:passengerDB)
            {
                cout<<"Passenger ID: "<<passenger.first<<endl;
            }
        }
    }
    else
    {
        cout<<"Incorrect password. Access denied.\n";
    }
}




void RoutePlanningWorkflow::primsAlgorithm(int numStations, const vector<vector<pair<int, double>>>& graph)
{
    vector<int> parent(numStations,-1);
    vector<double> key(numStations,INF);
    vector<bool> inMST(numStations,false);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;

    key[0]=0;
    pq.push({0.0,0});

    double totalWeight=0;
    while(!pq.empty())
    {
        int u=pq.top().second;
        pq.pop();

        if(inMST[u])
            continue;

        inMST[u]=true;

        if(parent[u]!=-1)
        {
            cout<<"Station "<<parent[u]<<" <-> Station "<<u<<" (Distance: "<<fixed<<setprecision(1)<<key[u]<<"km)\n";
            totalWeight +=key[u];
        }

        for (const auto& neighbor:graph[u])
        {
            int v=neighbor.first;
            double weight=neighbor.second;
            if (!inMST[v] && weight<key[v])
            {
                parent[v]=u;
                key[v]=weight;
                pq.push({weight,v});
            }
        }
    }
    cout<<"\nTotal Network Length: "<<fixed<<setprecision(1)<<totalWeight<<"km\n";
}





void MetroLine::calculateRequiredTrains()
{
    double journeyTime=(length/avgSpeed)*60;
    double totalDwellTime=numStations*dwellTime;
    double oneWayTotal=journeyTime+totalDwellTime;
    double turnaroundTime=5;
    double roundTrip=(oneWayTotal*2)+(turnaroundTime*2);
    double withBuffer=roundTrip*buffer;

    normalTrains=ceil(withBuffer/normalHeadway);
    peakTrains=ceil(withBuffer/peakHeadway);
}





void MetroLine::displayTimings()
{
    cout<<"\nRequired Trains:"<<endl;
    cout<<"Normal hours (5-min frequency): "<<normalTrains<<" trains"<<endl;
    cout<<"Peak hours (3-min frequency): "<<peakTrains<<" trains"<<endl;

    cout<<"\nTrain Departure Times:"<<endl;
    cout<<"Normal Hours (06:00-07:00):"<<endl;
    displayTimings(6,7,normalHeadway);

    cout<<"\nMorning Peak Hours (07:00-10:00):"<<endl;
    displayTimings(7,10,peakHeadway);

    cout<<"\nNormal Hours (10:00-16:00):"<< endl;
    displayTimings(10,16,normalHeadway);

    cout<<"\nEvening Peak Hours (16:00-20:00):"<<endl;
    displayTimings(16,20,peakHeadway);

    cout<<"\nNormal Hours (20:00-23:00):"<<endl;
    displayTimings(20,23,normalHeadway);
}




void MetroLine::displayTimings(int startHour, int endHour, int frequency)
{
    for (int hour=startHour;hour<endHour;hour++)
    {
        for (int minute=0;minute<60;minute+=frequency)
        {
            cout<<setfill('0')<<setw(2)<<hour<<":"<<setfill('0')<<setw(2)<<minute<<" ";
        }
        cout<<endl;
    }
}




bool LostAndFoundWorkflow::bruteForceSearch(const string& target)
{
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout<<"File "<<fileName<<" not found."<<endl;
        return false;
    }

    string line;
    while(getline(file,line))
    {
        if(line.find(target)!=string::npos)
        {
            file.close();
            return true; // Target found
        }
    }

    file.close();

    return false; // Target not found
}

void LostAndFoundWorkflow::addItemToFile(const string& item)
{
    ofstream file(fileName,ios::app); // Open in append mode
    if (!file.is_open())
    {
        cout<<"Unable to open "<<fileName<<" for writing."<<endl;
        return;
    }

    file<<item<<endl; // Add the item to the file
    file.close();
    cout<<"Item added successfully to the list."<<endl;
}




void LostAndFoundWorkflow::menu()
{
    int c;
    string input;


        cout<<"\n--- Lost and Found Department ---"<<endl;
        cout<<"1. Search for an item"<<endl;
        cout<<"2. Add a new item to the list"<<endl;
        cout<<"Enter your choice: ";
        cin>>c;
        cin.ignore();

        switch(c)
        {
            case 1:
            {
                cout<<"Enter the item to search for: ";
                getline(cin, input);

                if(bruteForceSearch(input))
                {
                    cout<<"Item found in the lost and found list!"<<endl;
                }
                else
                {
                    cout<<"Item not found."<<endl;
                }
                break;
            }
            case 2:
            {
                cout<<"Enter the item to add to the list: ";
                getline(cin,input);

                addItemToFile(input);

                break;
            }

            default:
                cout<<"Invalid choice! Returning to main menu."<<endl;
        }

}






int main()
{
    const int NUM_STATIONS=27;

    RailwayNetwork railway(27);

    railway.setStaticGraph();

    SecurityWorkflow security;

    RoutePlanningWorkflow routePlanning;

    LostAndFoundWorkflow lnfWorkflow("LnF.txt");

    int choice,x=0;
    while(true)
    {
        cout<<"\nMain Menu:\n";

        cout<<"1. Supply Chain Workflow\n";

        cout<<"2. Fare Calculation using\n";

        cout<<"3. Security Workflow\n";

        cout<<"4. Route Planning Workflow\n";

        cout<<"5. Train Scheduling Workflow\n";

        cout<<"6. Display Railway Layout\n";

        cout<<"7. Lost and found\n";

        cout<<"0. Exit\n";

        cout<<"Enter your choice: ";
        cin>>choice;

        if(cin.fail()) //in case of input failure
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input.Please enter a valid number.\n";
            continue;
        }

        switch(choice)
        {
            case 1:
            {
                int source;
                cout<<"Enter source station (1 to "<<NUM_STATIONS<<"): ";
                cin>>source;
                vector<double> distanceb=railway.dijkstra(source-1);

                cout<<"\nShortest distances from station "<<source<<":\n";
                for (int i=0;i<27;i++)
                {
                    cout<<"Station "<<i+1<<": ";
                    if(distanceb[i]==INF)
                        cout<<"Unreachable"<<endl;
                    else
                        cout<<distanceb[i]<<endl;
                }

                break;
            }

            case 2:
            {
                int source,destination,people;
                cout<<"Enter source station (1 to "<<NUM_STATIONS<<"): ";
                cin>>source;
                cout<<"Enter destination station (1 to "<<NUM_STATIONS<<"): ";
                cin>>destination;
                cout<<"Enter number of people:";
                cin>> people;

                double fare=railway.calculateFare(source-1,destination-1);
                cout<<"Fare from station "<<source<<" to station "<<destination<<fixed<<setprecision(2)<<" for "<<people<<" people is "<< fare*people <<" rupees."<<endl;

                break;
            }

            case 3:
            {
                int secChoice;

                cout<<"\nSecurity Workflow:\n";

                cout<<"1. Add Passenger\n";

                cout<<"2. Remove Passenger\n";

                cout<<"3. Verify Passenger\n";

                cout<<"4. View All Passengers\n";

                cout<<"Enter your choice: ";
                cin>>secChoice;

                if(secChoice==1)
                {
                    string id;
                    cout<<"Enter passenger ID: ";
                    cin>>id;
                    security.addPassenger(id);
                }

                else if(secChoice==2)
                {
                    string id;
                    cout<<"Enter passenger ID: ";
                    cin>>id;
                    security.removePassenger(id);
                }

                else if(secChoice==3)
                {
                    string id;
                    cout<<"Enter passenger ID: ";
                    cin>>id;
                    security.verifyPassenger(id);
                }

                else if(secChoice==4)
                {
                    security.viewAllPassengers();
                }

                else
                {
                    cout<<"Invalid choice. Returning to main menu.\n";
                }

                break;
            }

           case 4:
            {
                vector<vector<pair<int, double>>> graph(NUM_STATIONS); // use double for weights
                vector<tuple<int, int, double>> edges =
                {
                    {0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {0, 4, 1.0},
                    {1, 5, 2.0}, {2, 6, 1.5}, {3, 7, 2.0}, {4, 8, 1.5},
                    {5, 9, 1.5}, {6, 10, 2.0}, {7, 11, 1.5}, {8, 12, 2.0},
                    {9, 13, 2.0}, {10, 14, 3.0}, {11, 15, 2.0}, {12, 16, 3.0},
                    {13, 17, 3.0}, {14, 18, 5.0}, {15, 19, 3.0}, {17, 20, 5.0},
                    {18, 21, 4.0}, {19, 22, 2.0}, {20, 23, 4.0}, {22, 24, 4.0},
                    {24, 25, 5.0}, {25, 26, 6.0}
                 };

                for (const auto& edge : edges)
                {

                    int u = get<0>(edge);
                    int v = get<1>(edge);
                    double w = get<2>(edge);
                    graph[u].emplace_back(v, w);
                    graph[v].emplace_back(u, w);
                }

                cout << "\nCalculating optimal route using Prim's Algorithm...\n";
                routePlanning.primsAlgorithm(NUM_STATIONS, graph);
                break;
            }

            case 5:
            {
                cout << "\nTrain Schedule Information\n";
                cout << "=========================\n";
                cout << "\nLine 1 Details:\n";
                MetroLine line1(10, 24, 35);  // 10 stations, 24km length, 35km/h avg speed
                line1.displayTimings();

                cout << "\nLine 2 Details:\n";
                MetroLine line2(17, 45, 35);  // 17 stations, 45km length, 35km/h avg speed
                line2.displayTimings();
                break;
            }

            case 6:
            {
                cout << "\nCurrent Railway Network Layout:\n";
                cout << "==============================\n";
                railway.displayGraph();
                break;
            }

            case 7:
            {
                lnfWorkflow.menu();
                break;
            }

            case 0:
            {
                cout << "Exiting the program. Goodbye!\n";
                return 0;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
