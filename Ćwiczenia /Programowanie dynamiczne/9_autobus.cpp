#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
using namespace std;

const int INF = 1e9;

int autobus(int n, int m, const vector<vector<int>> &arr)
{
    vector<vector<int>> dp(n+1, vector<int>(m + 1, 0));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[i][j] = arr[i][j] + max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
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