#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;


int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> arr(k);
    vector<int> dp(n+1);
    for(int i=0;i<k;i++)
        cin>>arr[i];
    dp[0] = 1;
    for(int j=0;j<k;j++)
        for(int i=arr[j];i<=n;i++)
            dp[i] += dp[i - arr[j]];
    cout<<dp[n]<<"\n";
    return 0;
}