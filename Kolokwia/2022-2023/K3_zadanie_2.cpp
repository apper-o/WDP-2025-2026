#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

bool dfs(vector<int> &path, int x, int len)
{
    if(path.back() == x)
        return true;
    if(path.size() == len)
        return false;
    for(int i=path.size()-1;i>=0;i--)
    {
        for(int j=i;j>=0;j--)
        {
            path.push_back(path[i] * path[j]);
            if(dfs(path, x, len))
                return true;
            path.pop_back();
        }
    }
    path.push_back(path.back() + 1);
    if(dfs(path, x, len))
        return true;
    path.pop_back();
    return false;
}

vector<int> ciag(int n)
{
    vector<int> path = {1};
    for(int i=1;!dfs(path, n, i);i++)
    {
        path.clear();
        path.push_back(1);
    }
    return path;
}

int main() 
{
    return 0;
}
