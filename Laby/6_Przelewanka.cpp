#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <cassert>
using namespace std;

struct node
{
    vector<int> v;
    int moves;
};

// Tries to pour water from i-th glass to every possible glass different than i
void pour(int i, vector<int> &v, int moves, queue<node> &q, set<vector<int>> &vis, const vector<int> &capacity)
{
    int n = v.size();
    for(int j=0;j<n;j++)
    {
        if(j != i)
        {
            int to_pour = min(capacity[j] - v[j], v[i]);
            // Checks if it is possible to pour water
            if(to_pour)
            {
                // Subtracting and adding to_pour so that it is easier to retrieve v 
                v[i] -= to_pour;
                v[j] += to_pour;
                if(!vis.count(v))
                {
                    vis.insert(v);
                    q.push({v, moves + 1});
                }
                v[i] += to_pour;
                v[j] -= to_pour;
            }
        }
    }
}

// Empties the i-th glass 
void empty_glass(int i, vector<int> &v, int moves, queue<node> &q, set<vector<int>> &vis)
{
    // A glass can only be emptied if it is not already empty 
    if(v[i] > 0)
    {
        int n = v.size();
        // Temporary variable to retrieve v vector
        int tmp = v[i];
        v[i] = 0;
        if(!vis.count(v))
        {
            vis.insert(v);
            q.push({v, moves + 1});
        }
        v[i] = tmp;
    }
}

// Fills the i-th glass to the maximum capacity
void fill_glass(int i, vector<int> &v, int moves, queue<node> &q, set<vector<int>> &vis, const vector<int> &capacity)
{
    // A glass can only be filled if it is not already full
    if(v[i] != capacity[i])
    {
        // Temporary variable to retrieve v vector
        int tmp = v[i];
        v[i] = capacity[i];
        if(!vis.count(v))
        {
            vis.insert(v);
            q.push({v, moves + 1});
        }
        v[i] = tmp;
    }
}

// Function solves the task using BFS to find the shortest path in a state graph
// Returns minimal number of moves or -1 if no solution was found
int solve(int n, const vector<int> &capacity, const vector<int> &target)
{
    queue<node> q;

    // Initial state: all glasses are empty (0)
    q.push({vector<int>(n), 0});
    set<vector<int>> vis;
    vis.insert(vector<int>(n));
    while(q.size())
    {
        auto [v, moves] = q.front();
        q.pop();
        // Check if the target was reached
        if(v == target)
            return moves;
        // Tries all 3 operations for every possible glass
        for(int i=0;i<n;i++)
        {
            pour(i, v, moves, q, vis, capacity);
            empty_glass(i, v, moves, q, vis);
            fill_glass(i, v, moves, q, vis, capacity);
        }
    }
    return -1;
}

int main() 
{
    // Reads input
    int n;
    cin>>n;
    vector<int> capacity(n), target(n);
    for(int i=0;i<n;i++)
    {
        cin>>capacity[i]>>target[i];
        assert(capacity[i] >= target[i]);
    }
    auto res = solve(n, capacity, target);
    cout<<res<<"\n";
    return 0;
}