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
    vector<int> dp(n+1); // ilosc sposobow
    dp[0] = 1;
    for(int i=1;i<=n;i+=2)
        for(int j=n;j>=i;j--)
            dp[j] += dp[j - i];
    return dp[n];
}

vector<int> represent(int n)
{
    vector<int> res;
    int sum = 0;
    int it = 1;
    while(n - sum - it > it)
    {
        sum += it;
        res.push_back(it);
        it += 2;
    }
    if((n - sum) % 2 == 0)
    {
        sum -= res.back();
        res.pop_back();
    }
    res.push_back(n - sum);
    return res;
}

int main()
{
    int n;
    cin>>n;
    auto res = solve(n);
    cout<<res<<"\n";
    auto vec = represent(n);
    for(int i : vec)
        cout<<i<<" ";
    
    return 0;
}