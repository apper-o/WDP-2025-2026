#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

int valid(int n, int m, int x, int y)
{
    return min(x, y) >= 0 && x < m && y < n;
}

int dfs(int x, int y, int n, int m, const vector<vector<int>> &v, vector<vector<int>> &dp, const vector<pair<int, int>> &moves)
{
    if(y == n-1 && x == m-1)
        return 1
    if(dp[y][x])
        return dp[y][x];
    int res = 1;
    for(auto [dx, dy] : moves)
    {
        int new_x = x + dx;
        int new_y = y + dy;
        if(valid(n, m, new_x, new_y) && g[new_y][new_x] < g[y][x])
            res = max(res, dfs(new_x, new_y, n, m, v, dp, moves) + 1);
    }
    return dp[y][x] = res;
}

int sadzawka(const vector<vector<int>> &v)
{
    int n = v.size();
    int m = v[0].size();
    vector<vector<int>> dp(n, vector<int>(m));
    vector<pair<int, int>> moves = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    dp[0][0] = 1;
    dfs(0, 0, n, m, v, dp, moves);
    cout<<(dp[n-1][m-1] == 0 ? -1 : dp[n-1][m-1]);
}

int main() 
{
    return 0;
}
