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

int solve(int n, int k, const vector<int> &arr)
{
    vector<vector<int>> dp(2, vector<int>(n+1, 0));
    vector<int> pref(n+1);
    for(int i=1;i<=n;i++)
        pref[i] = pref[i-1] + arr[i-1];
    for(int j=0;j<k;j++)
    {
        for(int i=1;i<=n;i++)
        {
            dp[j % 2][i] = dp[j % 2][i - 1];
            for(int a=1;a<=i;a++)
                dp[j % 2][i] = max(dp[j % 2][i], dp[(j + 1) % 2][a - 1] + max(pref[i] - pref[a - 1] - (i - a) * (i - a), 0));
        }
    }
    return dp[(k-1) % 2][n];
}


int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = solve(n, k, arr);
    cout<<res<<"\n";
    return 0;
}