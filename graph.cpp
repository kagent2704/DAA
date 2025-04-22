#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int vertices;                         // Number of users
    vector<vector<int>> adjList;         // Adjacency list to represent friendships

public:
    Graph(int v) {
        vertices = v;
        adjList.resize(vertices);
    }

    // Add a friendship (undirected edge)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // BFS traversal from a given user
    void bfs(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS Traversal starting from user " << start << ": ";

        while (!q.empty()) {
            int user = q.front();
            q.pop();
            cout << user << " ";

            for (int friend_id : adjList[user]) {
                if (!visited[friend_id]) {
                    visited[friend_id] = true;
                    q.push(friend_id);
                }
            }
        }
        cout << endl;
    }

    // DFS traversal from a given user
    void dfs(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS Traversal starting from user " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }

private:
    void dfsUtil(int user, vector<bool>& visited) {
        visited[user] = true;
        cout << user << " ";

        for (int friend_id : adjList[user]) {
            if (!visited[friend_id]) {
                dfsUtil(friend_id, visited);
            }
        }
    }
};

int main() {
    int users, connections;
    cout << "Enter the number of users in the network: ";
    cin >> users;

    Graph facebook(users);

    cout << "Enter the number of friendships: ";
    cin >> connections;

    cout << "Enter each friendship as two space-separated user IDs (0 to " << users - 1 << "):\n";
    for (int i = 0; i < connections; ++i) {
        int u, v;
        cin >> u >> v;
        facebook.addEdge(u, v);
    }

    int start;
    cout << "Enter the starting user ID for traversal: ";
    cin >> start;

    facebook.bfs(start);
    facebook.dfs(start);

    return 0;
}

/* Sample Input/Output: 
Enter the number of users in the network: 6
Enter the number of friendships: 7
Enter each friendship as two space-separated user IDs (0 to 5):
0 1
0 2
1 3
1 4
2 4
3 4
4 5
Enter the starting user ID for traversal: 0
*/