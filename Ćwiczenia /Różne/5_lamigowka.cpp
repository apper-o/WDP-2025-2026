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

int lamigowka(const vector<int> &arr)
{
    int n = arr.size();
    int sum = 0;
    for(int i=0;i<n;i++)
        sum += arr[i];
    vector<int> dp(sum+1);
    dp[0] = 1;
    for(int i=0;i<n;i++)
        for(int j=sum;j>=arr[i];j--)
            dp[j] |= dp[j - arr[i]];
    for(int i=sum/2-(sum%2==0);i>=0;i--)
        if(dp[i])
            return sum - 2 * i;
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = lamigowka(arr);
    cout<<res<<"\n";
    return 0;
}