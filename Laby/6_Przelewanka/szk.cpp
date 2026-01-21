#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <cassert>
using namespace std;

const int MOD = 1e9 + 97;
const long long INF = 1e18;

struct node
{
    vector<int> v;
    long long moves;
};

// Returns a hash of a vector
long long encode(const vector<int> &v, const vector<int> &pw)
{
    long long hsh = 0;
    int n = int(v.size());
    for(int i=0;i<n;i++)
        hsh = (hsh + (long long)v[i] * pw[i]) % MOD;
    return hsh;
}

// Tries to pour water from i-th glass to every possible glass different than i
void pour(int i, vector<int> &v, long long moves, queue<node> &q, unordered_set<long long> &vis, const vector<int> &capacity, const vector<int> &pw)
{
    int n = (int)v.size();
    for(int j=0;j<n;j++)
    {
        if(j != i)
        {
            int to_pour = min(capacity[j] - v[j], v[i]);
            // Checks if it is possible to pour water
            if(to_pour > 0)
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
void empty_glass(int i, vector<int> &v, long long moves, queue<node> &q, unordered_set<long long> &vis, const vector<int> &pw)
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
void fill_glass(int i, vector<int> &v, long long moves, queue<node> &q, unordered_set<long long> &vis, const vector<int> &capacity, const vector<int> &pw)
{
    // A glass can only be filled if it is not already full
    if(v[i] < capacity[i])
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

// Calculates modular inverse using iterative Extended Euclidean Algorithm
long long modInverse(long long n, long long m) 
{
    long long x0 = 0, x1 = 1, a = n, b = m;
    while(a > 1 && b > 0) 
    {
        long long q = a / b;
        long long t = b;
        b = a - q * b; // Equivalent to a % b
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    return ((x1 % m) + m) % m;
}

// Calculates the number of operations for a specific strategy
// type 0: End state [target, 0] (Empty second jug)
// type 1: End state [target, 0] (Last move was pour)
// type 2: End state [target, full]
long long count_operations(long long from_cap, long long to_cap, long long target, int type) 
{
    long long inv = modInverse(from_cap, to_cap);
    long long fills = (target * inv) % to_cap;
    // We need to fill at least once
    if(fills == 0) 
        fills = to_cap;
    long long empties;
    if(type == 2) // Case where the second jug ends up FULL
    {   
        empties = (fills * from_cap - target - to_cap) / to_cap;
        if (empties < 0) 
            return INF;
    } 
    else // Case where the second jug ends up EMPTY
        empties = (fills * from_cap - target) / to_cap;
    // Adjust cost based on the last operation required
    if(type == 1) 
        return 2 * fills + 2 * empties - 1;
    return 2 * fills + 2 * empties;
}

// Solves the problem for exactly 2 jugs using Number Theory
long long solve_for_two(long long cap_a, long long cap_b, long long target_a, long long target_b) 
{
    long long res = INF;
    // Normalize: We want to focus on reaching target_a, with target_b being 0 or Full
    if(target_b == 0 || target_b == cap_b) 
    {
        swap(cap_a, cap_b);
        swap(target_a, target_b);
    }
    // Strategy 1: Target is in A, B ends up empty
    if (target_a == 0) 
    {
        long long tmp = count_operations(cap_a, cap_b, target_b, 0);
        if(tmp != INF)
            res = min(res, tmp);
        tmp = count_operations(cap_b, cap_a, target_b, 1);
        if(tmp != INF)
             res = min(res, tmp);
    }
    // Strategy 2: Target is in A, B ends up full (or A is full)
    if (target_a == cap_a) 
    {
        long long tmp = count_operations(cap_a, cap_b, target_b, 0);
        if(tmp != INF)
            res = min(res, tmp + 1);
        tmp = count_operations(cap_b, cap_a, target_b, 1);
        if(tmp != INF)
            res = min(res, tmp + 1);
        // Optimization: Simple fill and pour without emptying
        if((cap_a + target_b) % cap_b == 0) 
            res = min(res, 2 * (cap_a + target_b) / cap_b);
        tmp = count_operations(cap_b, cap_a, target_b, 2);
        if(tmp != INF)
            res = min(res, tmp);
    }
    return res;
}

// Checks if it ispossible to get the desired output
long long not_possible(vector<int> &capacity, vector<int> &target)
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
        return -1;
    else
    {
        for(int i=0;i<n;i++)
        {
            if(target[i] % g != 0)
                return -1;
            // Optimalization
            target[i] /= g;
            capacity[i] /= g;
        }
    }
    // Faster n = 2 case
    if (n == 2) 
    {
        // This ensures numbers are coprime for modular arithmetic.
        long long c1 = capacity[0];
        long long c2 = capacity[1];
        long long t1 = target[0];
        long long t2 = target[1];
        // At least one jug must be empty or full.
        bool possible = (t1 == 0 || t1 == c1 || t2 == 0 || t2 == c2);
        if (!possible) 
            return -1;
        else 
        {
            long long res = solve_for_two(c1, c2, t1, t2);
            if (res >= INF)
                return -1;
            return res;
        }
    }
    return -2;
}

// Simple case when all jugs are full
long long all_full(const vector<int> &capacity, const vector<int> &target)
{
    int n = (int)capacity.size();
    long long res = 0;
    for(int i=0;i<n;i++)
    {
        if(target[i] > 0)
        {
            if(target[i] == capacity[i])
                res++;
            else // this is not the all_full case
                return -1;
        }
    }
    return res;
}

// Function solves the task using BFS to find the shortest path in a state graph
// Returns minimal number of moves or -1 if no solution was found
long long solve(int n, vector<int> &capacity, vector<int> &target)
{
    long long full = all_full(capacity, target);
    if(full != -1)
        return full;
    long long tmp = not_possible(capacity, target);
    if(tmp == -1)
        return -1;
    else if(tmp >= 0)
        return tmp;
    // Calculates maximum capacity for hashes
    int mx = 0;
    for(int i=0;i<n;i++)
        mx = max(mx, capacity[i]);
    mx++;
    // Powers for polynominal hashes
    vector<int> pw(n+1);
    pw[0] = 1;
    tmp = 1;
    for(int i=1;i<n;i++)
    {
        tmp = tmp * mx % MOD;
        pw[i] = (int)tmp;
    }
    queue<node> q;
    // Initial state: all glasses are empty (0)
    q.push({vector<int>(n), 0});
    unordered_set<long long> vis;
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
    ios_base::sync_with_stdio(0); cin.tie(0);
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
    // Faster handling of case n = 2
    auto res = solve(n, capacity, target);
        cout<<res<<"\n";
    return 0;
}