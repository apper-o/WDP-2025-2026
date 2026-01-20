#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <chrono>
using namespace std;

const int MOD = 1e9 + 7;

struct node
{
    vector<int> v;
    int moves;
};

// Returns a hash of a vector
long long encode(const vector<int> &v, const vector<int> &pw)
{
    long long hsh = 0;
    int n = int(v.size());
    for(int i=0;i<n;i++)
        hsh = (hsh + v[i] * pw[i]) % MOD;
    return hsh;
}

// Tries to pour water from i-th glass to every possible glass different than i
void pour(int i, vector<int> &v, int moves, queue<node> &q, unordered_set<int> &vis, const vector<int> &capacity, const vector<int> &pw)
{
    int n = (int)v.size();
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
                long long hsh = encode(v, pw);
                if(!vis.count(hsh))
                {
                    vis.insert(hsh);
                    q.push({v, moves + 1});
                }
                v[i] += to_pour;
                v[j] -= to_pour;
            }
        }
    }
}

// Empties the i-th glass 
void empty_glass(int i, vector<int> &v, int moves, queue<node> &q, unordered_set<int> &vis, const vector<int> &pw)
{
    // A glass can only be emptied if it is not already empty 
    if(v[i] > 0)
    {
        // Temporary variable to retrieve v vector
        int tmp = v[i];
        v[i] = 0;
        long long hsh = encode(v, pw);
        if(!vis.count(hsh))
        {
            vis.insert(hsh);
            q.push({v, moves + 1});
        }
        v[i] = tmp;
    }
}

// Fills the i-th glass to the maximum capacity
void fill_glass(int i, vector<int> &v, int moves, queue<node> &q, unordered_set<int> &vis, const vector<int> &capacity, const vector<int> &pw)
{
    // A glass can only be filled if it is not already full
    if(v[i] != capacity[i] && v[i] == 0)
    {
        // Temporary variable to retrieve v vector
        int tmp = v[i];
        v[i] = capacity[i];
        long long hsh = encode(v, pw);
        if(!vis.count(hsh))
        {
            vis.insert(hsh);
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
bool not_possible(vector<int> &capacity, vector<int> &target)
{
    int n = (int)capacity.size();
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
        {
            if(target[i] % g > 0)
                return 1;
            // Optimalization
            target[i] /= g;
            capacity[i] /= g;
        }
    }
    return 0;
}

// Function solves the task using BFS to find the shortest path in a state graph
// Returns minimal number of moves or -1 if no solution was found
int solve(int n, vector<int> &capacity, vector<int> &target)
{
    if(not_possible(capacity, target))
        return -1;
    // Calculates maximum capacity for hashes
    int mx = 0;
    for(int i=0;i<n;i++)
        mx = max(mx, capacity[i]);
    mx++;
    // Powers for polynominal hashes
    vector<int> pw(n+1);
    pw[0] = 1;
    for(int i=1;i<n;i++)
        pw[i] = ((long long)pw[i-1] * mx) % MOD;

    queue<node> q;
    // Initial state: all glasses are empty (0)
    q.push({vector<int>(n), 0});
    unordered_set<int> vis;
    vis.insert(encode(vector<int>(n), pw));
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
            pour(i, v, moves, q, vis, capacity, pw);
            empty_glass(i, v, moves, q, vis, pw);
            fill_glass(i, v, moves, q, vis, capacity, pw);
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