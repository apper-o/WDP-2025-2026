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

int solve(int n)
{
    vector<int> dp(n+1);
    dp[0] = 1;
    int a = 1, b = 1;
    while(b <= n)
    {
        for(int i=n;i>=b;i--)
            dp[i] += dp[i - b];
        int tmp = a;
        a = b;
        b += tmp;
    }
    return dp[n];
}

int main()
{
    int n;
    cin>>n;
    auto res = solve(n);
    cout<<res<<"\n";
    return 0;
}