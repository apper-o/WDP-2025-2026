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

bool reachable(int a, int b, int steps)
{
    long long x = a;
    for(int i=0;i<steps;i++)
    {
        x *= x;
        if(x >= b)
            return true;
    }
    return false;
}

bool dfs(int current_depth, int max_depth, int n, vector<int> &path)
{
    if(path.back() == n)
        return true;
    if(current_depth == max_depth)
        return false;
    if(path.back() > 1 && !reachable(path.back(), n, max_depth - current_depth))
        return false;
    for(int i=path.size()-1;i>=0;i--)
    {
        for(int j=i;j>=0;j--)
        {
            if((long long)path[i] * path[j] <= n && (long long)path[i] * path[j] > path.back())
            {
                path.push_back(path[i] * path[j]);
                if(dfs(current_depth + 1, max_depth, n, path))
                    return true;
                path.pop_back();
            }
        }
    }
    path.push_back(path.back()+1);
    if(dfs(current_depth+1, max_depth, n, path))
        return true;
    path.pop_back();
    return false;
}

vector<int> solve(int n)
{
    vector<int> path = {1};
    for(int depth=1;!dfs(1, depth, n, path);depth++)
    {
        path.clear();
        path.push_back(1);
    }
    return path;
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