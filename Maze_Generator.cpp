#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

// Helper function prototypes
vector<unordered_set<int>> generateGraph(int H, int W);
vector<vector<bool>> graphToMaze(vector<unordered_set<int>>& adjList, int H, int W);
void printMaze(vector<vector<bool>>& matrix);
void dijkstra(vector<unordered_set<int>>& adjList,int src, int end);
void DFS(vector<unordered_set<int>>& adjList,int src, int end);
void printList(vector<unordered_set<int>>& adjList);

// Program Driver
int main()
{
    // 2500 x 40 gives 100k vertices and fits in console
    const int H = 100, W = 40;
    cout << "Generating maze of " << H << " by " << W << " vertices." << endl << endl;
    auto adjList = generateGraph(H, W);
    auto matrix = graphToMaze(adjList, H, W);
    printMaze(matrix);
    cout << endl << "Press any key to exit..." << endl;
    string c;
    cin >> c;
}

// Generates a random single-solution maze adjacency list using a version of DFS, then removes walls to introduce more solutions
vector<unordered_set<int>> generateGraph(int H=5, int W=5)
{
    // Graph adjacency list
    vector<unordered_set<int>> adjList(H * W);
    // Set of visited vertices
    vector<bool> v(H * W);
    // Stack of vertices to visit next...
    // NOTE: the pair consists of first: the vertex to be visited and second: which vertex it is visited from
    stack<pair<int,int>> s;
    //Push first vertex into stack with unused "from" value
    s.emplace(0, -1);

    // Visits each vertex exactly once
    while (!s.empty()) {

        // Get node to be visited and the node it is visited from
        int u = s.top().first;
        int from = s.top().second;
        s.pop();
        // If it has already been visited, move on
        if (v[u])
            continue;
        // Otherwise, mark it as visited
        v[u] = true;
        // Excluding the first node, add the edge to the adjacency list
        if (from != -1) {
            adjList[from].insert(u);
            adjList[u].insert(from);
        }

        // Create vector of unvisited neighbors
        vector<int> neighbors;
        if (u / W > 0 && !v[u - W])
            neighbors.push_back(u - W);
        if (u % W < W - 1 && !v[u + 1])
            neighbors.push_back(u + 1);
        if (u / W < H - 1 && !v[u + W])
            neighbors.push_back(u + W);
        if (u % W > 0 && !v[u - 1])
            neighbors.push_back(u - 1);
            
        // Push neighbors onto the stack in random order
        if (!neighbors.empty()) {
            random_shuffle(neighbors.begin(), neighbors.end());
            for (auto neighbor : neighbors)
                s.emplace(neighbor, u);
        }
    }

    // Remove some walls to create more solutions
    for (int i = 0; i < max(H, W); i++) {
        // Choose a random vertex
        int u = rand() % (W * H);
        // Create vector of *potential* neighbors of u
        vector<int> neighbors;
        if (u / W > 0 && !adjList[u].count(u - W))
            neighbors.push_back(u - W);
        if (u % W < W - 1 && !adjList[u].count(u + 1))
            neighbors.push_back(u + 1);
        if (u / W < H - 1 && !adjList[u].count(u + W))
            neighbors.push_back(u + W);
        if (u % W > 0 && !adjList[u].count(u - 1))
            neighbors.push_back(u - 1);
        // Knock down a random wall (make a connection with a random neighbor)
        if (!neighbors.empty()) {
            int v = neighbors[rand() % neighbors.size()];
            adjList[u].insert(v);
            adjList[v].insert(u);
        }
    }

    // Finally, return the completed adjacency list for underlying graph
    return adjList;
}

// Converts a graph adjacency list into a bool matrix representing a maze
vector<vector<bool>> graphToMaze(vector<unordered_set<int>>& adjList, int H, int W)
{
    vector<vector<bool>> matrix(H * 2 + 1, vector<bool>(W * 2 + 1));
    for (int i = 0; i < adjList.size(); i++) {
        int r = i / W;
        int c = i % W;
        int row = r * 2 + 1;
        int col = c * 2 + 1;
        matrix[row][col] = true;
        if (c < W - 1 && adjList[i].count(i + 1))
            matrix[row][col + 1] = true;
        if (r < H - 1 && adjList[i].count(i + W))
            matrix[row + 1][col] = true;
    }
    matrix[1][0] = true;
    matrix[H * 2 - 1][W * 2] = true;
    return matrix;
}

void printList(vector<unordered_set<int>>& adjList){
    for (int i = 0; i < adjList.size(); i++){
        if(!adjList[i].empty()){
            cout << i << " -> ";
            for (auto it = adjList[i].begin(); it != adjList[i].end(); ++it){
                cout << *it << " ";
            }
            cout << endl;
        }
    }
}
// does dijkstra stuff
void dijkstra(vector<unordered_set<int>>& adjList,int src, int end){
    auto start =  chrono::high_resolution_clock::now();
    unordered_set<int> computed;
    unordered_set<int> notComputed;
    computed.emplace(src);
    //filling notComputed with all verticies except src
    for (int i = 0; i < adjList.size(); i++){
        if(computed.count(i) != 1){
            notComputed.emplace(i);
        }
    }
    // distance to each verticy
    vector<int> d (adjList.size(), 99999);
    d[src] = 0;
    // keeps track of predecessor
    vector<int> p (adjList.size(), -1);

    for (auto it = adjList[src].begin(); it != adjList[src].end(); ++it){
        d[*it] = 1;
        p[*it] = src;
    }

    while (!notComputed.empty()){
        //need the smallest index that hasnt been visited yet
        vector<int> temp = d;
        //if it has been visited I make it big so it def wont be the smallest
        for(auto it = computed.begin(); it != computed.end(); ++it){
            temp[*it] = 999999999;
        }

        int minIndex = std::min_element(temp.begin(),temp.end()) - temp.begin();
        computed.emplace(minIndex);
        notComputed.erase(minIndex);

        for (auto it = adjList[minIndex].begin(); it != adjList[minIndex].end(); ++it){
            if (notComputed.count(*it) != 0){
                if(d[minIndex] + 1 < d[*it]){
                    d[*it] = d[minIndex] + 1;
                    p[*it] = minIndex;
                }
            }
        }

    }
    auto stopTime =  chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stopTime - start;
    cout << endl;
    cout << "Using DIJKSTRA" << endl;
    cout << "Finding " << end << " from " << src << " using DIJSKTRA took "
    << duration.count() << " Im not sure of time units" << endl;
    cout << "The distance from " << src << " to " << end << " is " << d[end] << endl;
    cout << "Path dijkstra took from " << src << " to " << end << ": ";
    // create a vector of the path
    int x = 999;
    int y = end;
    vector <int> v;
    while (x != src){
         x = p[y];
         v.push_back(x);
         y = x;
    }
    for (int i = v.size() - 1; i >= 0; i--){
        cout << v[i] << " -> ";
    }
    cout << end << endl;
    cout << endl;

}

//DFS stuff 
void DFS(vector<unordered_set<int>>& adjList,int src, int end){
    auto start =  chrono::high_resolution_clock::now();
    unordered_set<int> visited;
    stack<int> stack;
    visited.emplace(src);
    stack.push(src);
    //created path to keep track of all verticies DFS visisted
    //note path keeps track of all verticies visited, not just those in the "best path"
    vector<int> path;

    while (!stack.empty()){
        int x = stack.top();
        if (x == end){
            break;
        }
        path.push_back(x);
        stack.pop();
        vector<int> neighbors;
        for (auto it = adjList[x].begin(); it != adjList[x].end(); ++it){
            neighbors.push_back(*it);
        }
        for (int v : neighbors){
            if (visited.count(v) == 0){
                visited.insert(v);
                stack.push(v);
            }
        }
    }
    auto stopTime =  chrono::high_resolution_clock::now();
    chrono::duration<float> duration = stopTime - start;
    cout << "Using Depth First Search" << endl;
    cout << "Finding " << end << " from " << src << " using DFS took "
    << duration.count() << " Im not sure time unit" << endl;
    cout << "The distance from " << src << " to " << end << " is " << path.size() << endl;
    cout << "Path DFS took from " << src << " to " << end << ": ";
    for (int i = 0; i < path.size(); i++){
        cout << path[i] << "-> ";
    }
    cout << end;
}

// Convenient way to view a bool matrix maze without external libraries
void printMaze(vector<vector<bool>>& matrix)
{
    char path = 255u;
    char wall = 219u;
    for (auto v : matrix) {
        for (auto b : v) {
            if (b)
                cout << path << path;
            else
                cout << wall << wall;
        }
        cout << endl;
    }
}
