#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

int proximity(const vector<vector<int>> &adj, int s, int k)
{
    queue<int> q;
    vector<int> dist(s + k, INF);
    for(int i=0;i<s;i++)
    {
        q.push(i);
        dist[i] = 0;
    }
    while(q.size())
    {
        int v = q.front();
        q.pop();
        for(int u : adj[v])
        {
            if(dist[u] > dist[v] + 1)
            {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    int res = 0;
    for(int i=s+1;i<s+k;i++)
        res = max(res, dist[i]);
    return (res == INF ? -1 : res);
}

int main() 
{
    return 0;
}
