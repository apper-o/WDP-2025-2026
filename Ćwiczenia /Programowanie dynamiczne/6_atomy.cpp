#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;

vector<int> energia(int k, const vector<int> &t, int e, int n)
{
    vector<int> res;
    vector<vector<int>> dp(k + 1, vector<int>(e + 1));
    dp[0][0] = -1;
    for(int j=0;j<n;j++)
    {
        int val = t[j];
        for(int c=k;c>0;c--)
            for(int i=e;i>=val;i--)
                if(dp[c - 1][i - val])
                    dp[c][i] = j + 1;
    }
    if(dp[k][e] == 0)
        return res;
    for(int i=k,j=e;i>0;i--)
    {
        res.push_back(dp[i][j] - 1);
        j-=t[dp[i][j] - 1];
    }
    return res;
}

int main()
{
    int n, k, e;
    cin>>n>>k>>e; // n = liczba powłok, k = liczba elektronów, e = szukana energia
    vector<int> t(n); // energia elektronu na i-tej powłoce
    for(int i=0;i<n;i++)
        cin>>t[i];
    vector<int> res = energia(k, t, e, n);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}