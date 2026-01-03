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

vector<int> ciag(int n)
{
    vector<int> fib;
    int a = 1, b = 2;
    while(b <= n)
    {
        fib.push_back(b);
        int tmp = a;
        a = b;
        b += tmp;
    }
    vector<int> res;
    vector<int> vis(n + 1);
    queue<pair<int, int>> q;
    q.push({1, 1});
    while(q.size())
    {
        auto [val, steps] = q.front();
        q.pop();
        if(val == n)
            break;
        for(auto f : fib)
        {
            if(val * f > n)
                break;
            if(!vis[val * f])
            {
                q.push({val * f, steps + 1});
                vis[val * f] = f;
            }
        }
        if(!vis[val + 1])
        {
            q.push({val + 1, steps + 1});
            vis[val + 1] = -1;
        }
    }
    int p = n;
    while(vis[p])
    {
        res.push_back(p);
        p = (vis[p] == -1 ? p - 1 : p / vis[p]);
    }
    res.push_back(1);
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    int n;
    cin>>n;
    auto res = ciag(n);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}