#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

void dfs(int v, const vector<vector<bool>> &g, vector<int> &vis)
{
    vis[v] = 1;
    for(int i=0;i<g[v].size();i++)
        if(g[v][i] && !vis[i])
            dfs(i, g, vis);
}

int zdominowani(const vector<vector<bool>> &g)
{
    int n = g[0].size();
    queue<int> q;
    for(int i=0;i<n;i++)
    {
        int sum = 0;
        for(int j=0;j<n && sum==0;j++)
            sum+=g[j][i];
        if(sum == 0)
            q.push(i);
    }
    vector<int> vis(n);
    vector<int> cnt(n);
    while(q.size())
    {
        auto v = q.front();
        dfs(v, g, vis);
        cnt[v] = -1;
        for(int i=0;i<n;i++)
        {
            cnt[i] += vis[i];
            vis[i] = 0;
        }
    }
    int res = 0;
    for(int i=0;i<n;i++)
            res += (cnt[i] == 0);
    return res;
}

int main() 
{
    return 0;
}
