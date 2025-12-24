#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;

int klej(int n, const vector<int> &arr)
{
    vector<vector<int>> dp(n+1, vector<int>(n+1, INF));
    vector<int> pref(n+1);
    for(int i=1;i<=n;i++)
        dp[i][i] = 0;
    for(int i=1;i<=n;i++)
        pref[i] = pref[i-1] + arr[i-1];
    for(int i=1;i<=n;i++) // dlugosc przedzialu
        for(int j=1;j+i<=n;j++) // poczatek przedzialu
            for(int k=j;k<i+j;k++)
                dp[j][j+i] = min(dp[j][j+i], dp[j][k] + dp[k+1][j+i] + max(pref[k] - pref[j-1], pref[i+j] - pref[k]));
    return dp[1][n];
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    cout<<klej(n, arr);
    return 0;
}