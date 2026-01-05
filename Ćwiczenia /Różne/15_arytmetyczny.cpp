#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

const int INF = 1e9;

int solve(int n, const vector<int> &arr)
{
    vector<unordered_map<int, int>> dp(n);
    int res = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int diff = arr[j] - arr[i];
            int val = (dp[i].count(diff) ? dp[i][diff] + 1 : 2);
            dp[j][diff] = max(dp[j][diff], val);
            res = max(res, val);
        }
    }
    return res;
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = solve(n, arr);
    cout<<res<<"\n";
    return 0;
}