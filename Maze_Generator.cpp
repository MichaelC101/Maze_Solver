#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

void printGraph(vector<vector<int>>& adjList)
{
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    const int H = 5, W = 5;
    vector<vector<int>> adjList(H * W);
    vector<bool> v(H * W);
    stack<pair<int,int>> s;
    s.emplace(0, -1);
    while (!s.empty()) {
        auto u = s.top();
        s.pop();
        if (v[u.first])
            continue;
        v[u.first] = true;
        cout << u.first << endl;
        if (u.second != -1) {
            adjList[u.second].push_back(u.first);
            adjList[u.first].push_back(u.second);
        }
        vector<int> neighbors;
        // If u has unvisited north neighbor, push north neighbor to neighbors
        if (u.first / W > 0 && !v[u.first - W])
            neighbors.push_back(u.first - W);
        // If u has unvisited east neighbor, push east neighbor to neighbors
        if (u.first % W < W - 1 && !v[u.first + 1])
            neighbors.push_back(u.first + 1);
        // If u has unvisited south neighbor, push south neighbor to neighbors
        if (u.first / W < H - 1 && !v[u.first + W])
            neighbors.push_back(u.first + W);
        // If u has unvisited west neighbor, push west neighbor to neighbors
        if (u.first % W > 0 && !v[u.first - 1])
            neighbors.push_back(u.first - 1);
        // If u has unvisited neighbors, push to the stack randomly, indicate random one as visited and add it to graph
        if (!neighbors.empty()) {
            random_shuffle(neighbors.begin(), neighbors.end());
            for (auto neighbor : neighbors)
                s.emplace(neighbor, u.first);
        }
    }
    printGraph(adjList);
}