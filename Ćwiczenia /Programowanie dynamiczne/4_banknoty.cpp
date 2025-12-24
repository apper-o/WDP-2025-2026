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
    vector<int> b(n);
    vector<int> c(n);
    for(int i=0;i<n;i++)
        cin>>b[i];
    for(int i=0;i<n;i++)
        cin>>c[i];
    vector<int> dp(k+1, INF);
    vector<int> used(k+1);
    dp[0] = 0;
    for(int j=0;j<n;j++)
    {
        int val = b[j];
        int lim = c[j];
        for(int i=0;i<=k;i++)
            used[i] = 0; 
        for(int i=val;i<=k;i++)
        {
            if(used[i - val] < lim && dp[i] > dp[i - val] + 1)
            {
                used[i] = used[i-val] + 1;
                dp[i] = dp[i -val] + 1;
            }
        }
    }
    cout<<(dp[k] == INF ? -1 : dp[k]);
    return 0;
}