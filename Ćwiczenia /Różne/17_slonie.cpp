#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

// https://szkopul.edu.pl/problemset/problem/hVt8GQhxDxdYzrhLngOSJuzS/site/?key=statement

const int INF = 1e9;

long long solve(const vector<int> &m, const vector<int> &a, const vector<int> &b)
{
    int n = m.size();
    vector<int> p(n); // id of value i in the b permutation
    for(int i=0;i<n;i++)
        p[b[i]] = i;
    vector<int> vis(n);
    int mn_global = INF;
    long long res = 0;
    for(int i=0;i<n;i++)
        mn_global = min(mn_global, m[i]);
    for(int i=0;i<n;i++)
    {
        if(vis[i])
            continue;
        vis[i] = 1;
        if(p[a[i]] != i)
        {
            int v = p[a[i]];
            long long sum = m[a[i]];
            int mn_local = m[a[i]];
            int len = 1;
            while(!vis[v])
            {
                len++;
                vis[v] = 1;
                sum += m[a[v]];
                mn_local = min(mn_local, m[a[v]]);
                v = p[a[v]];
            }
            res += min(mn_local + sum + (len + 1) * mn_global, sum + (len - 2) * mn_local);
        }
    }
    return res;
}

int main()
{
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> m(n);
    vector<int> a(n);
    vector<int> b(n);
    for(int i=0;i<n;i++)
        cin>>m[i];
    for(int i=0;i<n;i++)
    {
        cin>>a[i];
        a[i]--;
    }
    for(int i=0;i<n;i++)
    {
        cin>>b[i];
        b[i]--;
    }
    auto res = solve(m, a, b);
    cout<<res<<"\n";
    return 0;
}