#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

vector<int> iter_perm(const vector<int> &p, int k)
{
    int n = p.size();
    vector<int> cycle(n);
    vector<int> vis(n);
    vector<int> res(n);
    for(int i=0;i<n;i++)
    {
        if(vis[i])
            continue;
        int v = i;
        int len = 0;
        while(!vis[v])
        {
            vis[v] = 1;
            cycle[len++] = v;
            v = p[v];
        }        
        int delta = k % len;
        for(int j=0;j<len;j++)
            res[cycle[j]] = cycle[(j + delta) % len];
    }
    return res;
}

int main() 
{
    return 0;
}
