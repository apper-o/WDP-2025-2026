#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;

int unikat(const vector<int> &b, int k)
{
    vector<int> dp(k+1, 0);
    dp[0] = 1;
    for(int val : b)
        for(int i=val;i<=k;i++)
            dp[i] = min(2, dp[i] + dp[i-val]);
    for(int i=k;i>=0;i--)
        if(dp[i] == 1)
            return i;
}

int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> b(n);
    for(int i=0;i<n;i++)
        cin>>b[i];
    unikat(b, k);
    return 0;
}