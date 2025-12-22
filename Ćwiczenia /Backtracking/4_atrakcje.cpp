#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;

int solve(int v, int mask, int n, vector<vector<int>> &dp, const vector<vector<int>> &cost, const vector<int> &req)
{
    if (dp[mask][v] != INF)
        return dp[mask][v];
    for (int i = 1; i < n; i++)
        if ((req[i] & mask) == req[i] && (mask & (1 << i)) == 0)
            dp[mask][v] = min(dp[mask][v], cost[v][i] + solve(i, mask + (1 << i), n, dp, cost, req));
    return dp[mask][v];
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    vector<vector<int>> cost(n, vector<int>(n));
    vector<int> req(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> cost[i][j];
    for (int i = 0, a, b; i < k; i++)
    {
        cin >> a >> b;
        a--, b--;
        req[b] |= (1 << a);
    }
    for (int i = 0; i < n; i++)
        dp[(1 << n) - 1][i] = 0;
    cout << solve(0, 1, n, dp, cost, req);
    return 0;
}