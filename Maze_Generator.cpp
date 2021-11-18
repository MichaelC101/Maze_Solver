#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

vector<vector<bool>> toMatrix(vector<unordered_set<int>>& adjList, int H, int W)
{
    vector<vector<bool>> matrix(H * 2 + 1, vector<bool>(W * 2 + 1, false));
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

void printMatrix(vector<vector<bool>>& matrix)
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

int main()
{
    const int H = 20, W = 20;
    vector<unordered_set<int>> adjList(H * W);
    vector<bool> v(H * W);
    stack<pair<int,int>> s;
    s.emplace(0, -1);

    // Should visit each node once
    while (!s.empty()) {
        int u = s.top().first;
        int from = s.top().second; 
        s.pop();
        if (v[u])
            continue;
        v[u] = true;
        if (from != -1) {
            adjList[from].insert(u);
            adjList[u].insert(from);
        }

        // Create list of unvisited neighbors
        vector<int> neighbors;
        if (u / W > 0 && !v[u - W])
            neighbors.push_back(u - W);
        if (u % W < W - 1 && !v[u + 1])
            neighbors.push_back(u + 1);
        if (u / W < H - 1 && !v[u + W])
            neighbors.push_back(u + W);
        if (u % W > 0 && !v[u - 1])
            neighbors.push_back(u - 1);
            
        // Push neighbors onto the stack randomly
        if (!neighbors.empty()) {
            random_shuffle(neighbors.begin(), neighbors.end());
            for (auto neighbor : neighbors)
                s.emplace(neighbor, u);
        }
    }
    
    // Convert adjacency list to bool matrix and print
    auto matrix = toMatrix(adjList, H, W);
    printMatrix(matrix);
}