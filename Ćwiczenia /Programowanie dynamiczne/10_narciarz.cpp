#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

bool valid(int y, int x, int n, int m)
{
    return min(x, y) >= 1 && x <= m && y <= n;
}

int autobus(int n, int m, const vector<vector<int>> &arr)
{
    vector<vector<int>> dp(n+1, vector<int>(m + 1, -1));
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    queue<pair<int, int>> q;
    q.push({1, 1});
    dp[1][1] = 0;
    int res = -1;
    while(q.size())
    {
        auto [x, y] = q.front();
        q.pop();
        if(x == m && y == n)
        {
            res = max(res, dp[y][x]);
            continue;
        }
        for(auto [dx, dy] : moves)
        {
            int xp = x + dx;
            int yp = y + dy;
            int val = max(dp[y][x], abs(yp - xp));
            if(valid(yp, xp, n, m) && arr[y][x] > arr[yp][xp] && dp[yp][xp] < val)
            {
                dp[yp][xp] = val;
                q.push({xp, yp});
            }
        }
    }
    return res;
}

int main()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>> arr(n + 1, vector<int>(m + 1));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>arr[i][j];
    cout<<autobus(n, m, arr);
    return 0;
}