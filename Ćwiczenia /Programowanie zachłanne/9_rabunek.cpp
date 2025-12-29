#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

int rabunek(const vector<int> &nominaly, int kwota)
{
    vector<int> dp(kwota + 1);
    dp[0] = 1;
    for(int i=nominaly.size()-1;i>=0 && dp[kwota] == 0;i--)
    {
        for(int j=nominaly[i];j<=kwota;j++)
        {
            if(dp[j - nominaly[i]])
                dp[j] = max(dp[j], nominaly[i]);
        }
    }
    if(dp[kwota] == 0)
        return -1;
    int a = INF, b = INF, p = kwota;
    while(p)
    {
        if(dp[p] < a)
        {
            b = a;
            a = dp[p];
        }
        else if(dp[p] < b)
            b = dp[p];
        p -= dp[p];
    }
    return a + b;
}

int main()
{
    vector<int> arr = {2, 7, 12, 15, 20};
    int kwota = 42;
    cout<<rabunek(arr, kwota);
    return 0;
}