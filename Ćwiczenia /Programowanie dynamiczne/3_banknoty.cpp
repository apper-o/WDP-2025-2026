#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

const int INF = 1e9;

int main()
{
    int n, k;
    cin>>n>>k; // n = szukana kwota, k = liczba banknotow
    vector<int> b(k);
    for(int i=0;i<k;i++)
        cin>>b[i];
    vector<int> dp(n+1, INF);
    dp[0] = 0;
    for(int i=0;i<k;i++)
    {
        int nom = b[i];
        for(int j=0;j<nom;j++)
        {
            int prev = INF;
            for(int x=j;x<=n;x+=nom)
            {
                dp[x] = min(dp[x], prev + 1);
                prev = min(dp[x], prev);
            }
        }    
    }
    cout<<(dp[n] >= INF ? -1 : dp[n])<<"\n";
    return 0;
}