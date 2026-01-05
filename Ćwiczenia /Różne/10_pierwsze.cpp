#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

const int INF = 1e9;

vector<int> primes(int n)
{
    vector<int> p(n+1, 1);
    vector<int> res;
    p[0] = p[1] = 0;
    for(int i=2;i<=n;i++)
    {
        if(p[i])
        {
            res.push_back(i);
            for(int j=i*i;j<=n;j+=i)
                p[j] = 0;
        }
    }
    return res;
}

vector<int> solve(int n)
{
    vector<int> prime = primes(n);
    vector<int> res;
    vector<int> vis(n+1);
    queue<int> q;
    vis[1] = -1;
    q.push(1);
    while(q.size())
    {
        auto v = q.front();
        q.pop();
        if(v == n)
            break;
        for(int u : prime)
        {
            if(v * u > n)
                break;
            if(!vis[v * u])
            {
                vis[v * u] = u;
                q.push(v * u);
            }
        }
        if(!vis[v + 1])
        {
            vis[v + 1] = -1;
            q.push(v + 1);
        }
    }
    int p = n;
    while(vis[p])
    {
        res.push_back(p);
        p = (vis[p] == -1 ? p-1 : p / vis[p]);
    }
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    int n;
    cin>>n;
    auto res = solve(n);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}