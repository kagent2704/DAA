#include <iostream>
#include <iomanip> //managing setw function
#include <string>
using namespace std;

class Graph
{
    int cost[10][10]; //Adjacency Matrix

public:
    string cities[10]; // Names of cities in the graph    | Public Declaration of variables for global access
    int n; // Number of cities                            | __|
    Graph();
    void create();
    void display();
    void prims(int start_v); // Prim's Algorithm
};

//Constructor
//Self-loops (cost to itself) = 0. Other costs = 999 (infinity)
//cities[] stores names of cities
Graph::Graph()
{
    cout << "Enter the number of cities: ";
    cin >> n;

    cout << "Enter the names of the cities:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "City " << i << ": ";
        cin >> cities[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cost[i][j] = (i == j) ? 0 : 999; // Set diagonal to 0, others to high value
        }
    }
}

void Graph::create()
{
    cout << "Enter connections and their cost:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            char ch;
            cout << "Is " << cities[i] << " connected to " << cities[j] << "? (Y/N): ";
            cin >> ch;
            if (tolower(ch) == 'y')
            {
                cout << "Enter cost: ";
                cin >> cost[i][j];
                cost[j][i] = cost[i][j]; //Stores costs in the adjacency matrix (cost[i][j] = cost[j][i] since it's undirected).
                //undirected graph means if i is connected to j then j is also connected to i. therefore to and fro cost is same.
            }
        }
    }
    cout << "Adjacency matrix created.\n";
    display();
}

void Graph::display()
{
    cout << "\nAdjacency Matrix:\n";       // | 
    cout << setw(12) << "";                // |  
    for (int i = 0; i < n; i++)            // |  
    {                                      // |----> Displaying the names of cities as column headers
        cout << setw(12) << cities[i];     // |  
    }                                      // |  
    cout << "\n";                          // |

    //Displaying the adjacency matrix
    for (int i = 0; i < n; i++)          // |
    {                                    // |----> Displaying the names of cities as row headers 
        cout << setw(12) << cities[i];   // |
        for (int j = 0; j < n; j++)                                                   // |
        {                                                                             // |----> Displaying the cost of connection between cities
            cout << setw(12) << (cost[i][j] == 999 ? "INF" : to_string(cost[i][j]));  // |     (or "INF" if no connection)
        }              
        cout << endl;
    }
}

void Graph::prims(int start_v)
{
    int nearest[10], t[10][3], mincost = 0, r = 0;

    fill(begin(nearest), end(nearest), -1);
    for (int i = 0; i < n; i++)
        if (i != start_v)
            nearest[i] = start_v;

    for (int i = 1; i < n; i++)
    {
        int min = 999, j = -1;

        for (int k = 0; k < n; k++)
        {
            if (nearest[k] != -1 && cost[k][nearest[k]] < min)
            {
                min = cost[k][nearest[k]];
                j = k;
            }
        }
        
        if (j == -1)
            break;
        t[r][0] = nearest[j];
        t[r][1] = j;
        t[r][2] = min;
        r++;
        mincost += min;
        nearest[j] = -1;

        for (int k = 0; k < n; k++)
        {
            if (nearest[k] != -1 && cost[k][j] < cost[k][nearest[k]])
            {
                nearest[k] = j;
            }
        }
        
        cout << "\nIteration " << i << ":";
        cout << "\nNearest: ";
        for (int k = 0; k < n; k++) cout << nearest[k] << " ";
        cout << "\nEdges in MST so far: ";
        for (int k = 0; k < r; k++)
            cout << "(" << cities[t[k][0]] << " - " << cities[t[k][1]] << " : " << t[k][2] << ") ";
        cout << "\nCurrent MST Edge Count: " << r << "\n";
    }
    
    cout << "\nMinimum Spanning Tree Edges:\n";
    for (int i = 0; i < r; i++)
    {
        cout << "Edge: (" << cities[t[i][0]] << " - " << cities[t[i][1]] << ") Cost: " << t[i][2] << "\n";
    }
    cout << "Total Minimum Cost: " << mincost << "\n";
}

int main()
{
    Graph g;
    g.create();
    string start_city;
    cout << "Enter the starting city: ";
    cin >> start_city;
    int start_v = -1;
    for (int i = 0; i < g.n; i++)
    {
        if (g.cities[i] == start_city)
        {
            start_v = i;
            break;
        }
    }
    if (start_v == -1)
    {
        cout << "Invalid city name.\n";
        return 1;
    }
    g.prims(start_v);
    return 0;
}
