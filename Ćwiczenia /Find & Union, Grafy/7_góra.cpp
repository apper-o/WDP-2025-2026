#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

struct pii
{
    int val;
    int a, b;
    bool operator <(const auto &other) const
    {
        return val < other.val;
    };
};

int solve(const vector<vector<int>> &adj)
{
    int n = adj.size();
    int m = adj[0].size();
    
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<int>> dist(n, vector<int>(m, INF));
    dist[0][0] = adj[0][0];
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({adj[0][0], 0, 0});
    while(pq.size())
    {
        auto [val, x, y] = pq.top();
        pq.pop();
        if(val != dist[y][x])
            continue;
        if(y == n-1 && x == m-1)
            return val;
        for(auto [dx, dy] : moves)
        {
            int new_x = dx + x;
            int new_y = dy + y;
            if(min(new_x, new_y) >= 0 && new_x < m && new_y < n && dist[new_y][new_x] > max(dist[y][x], adj[new_y][new_x]))
            {
                dist[new_y][new_x] = max(dist[y][x], adj[new_y][new_x]);
                pq.push({dist[new_y][new_x], new_x, new_y});
            }
        }
    }
}

int main() 
{
    return 0;
}
