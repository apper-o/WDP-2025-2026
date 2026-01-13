#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

struct pii
{
    int a, y, x;
    bool operator<(const pii& other) const 
    {
        return a < other.a;
    }
};

int sadzawka(const vector<vector<int>> &mapa, int jas_x, int jas_y)
{
    int n = mapa.size();
    int m = mapa[0].size();
    vector<vector<int>> dist(n, vector<int>(m, 0));
    priority_queue<pii> pq;
    pq.push({mapa[jas_y][jas_x], jas_y, jas_x});
    dist[jas_y][jas_x] = mapa[jas_y][jas_x];
    vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    while(pq.size())
    {
        auto [val, y, x] = pq.top();
        pq.pop();
        if(dist[y][x] > val)
            continue;
        if(y == 0 || x == 0 || x == n - 1 || y == m - 1)
            return val;
        for(auto [dx, dy] : moves)
        {
            int new_y = y + dy;
            int new_x = x + dx;
            if(min(new_x, new_y) < 0 || new_x >= m || new_y >= n)
                continue;
            if(dist[new_y][new_x] < min(mapa[new_y][new_x], val))
            {
                dist[new_y][new_x] = min(mapa[new_y][new_x], val);
                pq.push({dist[new_y][new_x], new_y, new_x});
            }
        }
    }
    return 0;
}

int main() 
{
    return 0;
}
