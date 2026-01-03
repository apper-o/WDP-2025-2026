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

bool dfs(vector<int> &path, int n, int max_steps)
{
    if(path.back() == n)
        return true;
    int steps = path.size();
    int x = path.back();
    if(x << (max_steps - steps) < n || steps == max_steps)
        return false;
    for(int i=0;i<steps;i++)
    {
        for(int j=i;j<steps;j++)
        {
            path.push_back(path[i] + path[j]);
            if(dfs(path, n, max_steps))
                return true;
            path.pop_back();
        }
    }
    return false;
}

vector<int> ciag(int n)
{
    vector<int> res;
    for(int i=2;i<=n;i++)
    {
        res.clear();
        res.push_back(1);
        if(dfs(res, n, i))
            break;
    }
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