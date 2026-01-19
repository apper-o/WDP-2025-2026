#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

struct node
{
    vector<int> v;
    int moves;
};

// Custom hasing function
struct vector_hash 
{
    // https://codeforces.com/blog/entry/62393
    static uint64_t splitmix64(uint64_t x) 
    {
        x += 0x9e3779b97f4a7c15; // Weil's constant 2^64 / \phi
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    // https://stackoverflow.com/questions/4948780/magic-number-in-boosthash-combine
    size_t operator()(const vector<int>& v) const 
    {
        // static const for future use
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        uint64_t hash = 0;
        for (int val : v)
            hash ^= splitmix64(val + FIXED_RANDOM + 0x9e3779b9 + (hash << 6) + (hash >> 2));
        return hash;
    }
};

using visited_set = unordered_set<vector<int>, vector_hash>;

// Tries to pour water from i-th glass to every possible glass different than i
void pour(int i, vector<int> &v, int moves, queue<node> &q, visited_set &vis, const vector<int> &capacity)
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
void empty_glass(int i, vector<int> &v, int moves, queue<node> &q, visited_set &vis)
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
void fill_glass(int i, vector<int> &v, int moves, queue<node> &q, visited_set &vis, const vector<int> &capacity)
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

// Returns gcd of two numbers
int gcd(int a, int b)
{
    return (b ? gcd(b, a % b) : a);
}

// Checks if it ispossible to get the desired output
bool not_possible(const vector<int> &capacity, const vector<int> &target)
{
    int n = capacity.size();
    int g = 0;
    bool non_zero_or_full = 0;
    for(int i=0;i<n;i++)
    {
        if(capacity[i] > 0)
            g = gcd(g, capacity[i]);
        non_zero_or_full |= (capacity[i] > 0 || capacity[i] == target[i]);
    }
    if(!non_zero_or_full)
        return -1;
    // If gcd doesn't divide target[i] than it is impossible to get the desired output
    if(g == 0)
    {
        for(int i=0;i<n;i++)
            if(target[i] > 0)
                return 1;
    }
    else
    {
        for(int i=0;i<n;i++)
            if(target[i] % g > 0)
                return 1;
    }
    return 0;
}

// Function solves the task using BFS to find the shortest path in a state graph
// Returns minimal number of moves or -1 if no solution was found
int solve(int n, const vector<int> &capacity, const vector<int> &target)
{
    if(not_possible(capacity, target))
        return -1;
    queue<node> q;
    // Initial state: all glasses are empty (0)
    q.push({vector<int>(n), 0});
    visited_set vis;
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
        assert(target[i] >= 0);
        assert(capacity[i] >= 0);
    }
    auto res = solve(n, capacity, target);
    cout<<res<<"\n";
    return 0;
}
