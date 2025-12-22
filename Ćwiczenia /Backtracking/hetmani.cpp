#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

bool valid(int x, int y, const vector<vector<int>> &arr, vector<pair<int, int>> &res)
{
    if(arr[y][x])
        return 0;
    for(auto [yp, xp] : res)
        if(x == xp || y == yp || xp - yp == x - y || xp + yp == x + y)
            return 0;
    return 1;
}

bool solve(int x, int n, const vector<vector<int>> &arr, vector<pair<int, int>> &res)
{
    if(x == n)
        return 1;
    for(int y=0;y<n;y++)
    {
        if(valid(x, y, arr, res))
        {
            res.push_back({y, x});
            if(solve(x + 1, n, arr, res))
                return 1;
            res.pop_back();
        }
    }
    return 0;
}

int main()
{
    // 0 oznacza pole wolne, 1 oznacza pole zablokowane
    int n;
    cin>>n;
    vector<vector<int>> arr(n, vector<int>(n));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>arr[i][j];
    vector<pair<int, int>> res; 
    solve(0, n, arr, res);
    if(res.size() == n)
        for(auto [y, x] : res)
            cout<<x<<" "<<y<<"\n";
    else
        cout<<"NIE\n";
    return 0;
}