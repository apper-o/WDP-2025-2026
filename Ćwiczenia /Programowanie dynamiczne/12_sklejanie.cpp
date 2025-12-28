#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

int solve(int n, const vector<int> &arr)
{
    vector<int> pref(n+1);
    vector<int> last(n+1);
    vector<int> dp(n+1);
    for(int i=1;i<=n;i++)
        pref[i] = pref[i-1] + arr[i-1];
    
    deque<int> q;
    q.push_front(0);
    for(int i=1;i<=n;i++)
    {
        int j = q.front();
        q.pop_front();
        while(q.size() && last[q.front()] < pref[i] - pref[q.front()])
        {
            j = q.front();
            q.pop_front();
        }
        q.push_front(j);

        dp[i] = dp[j] + 1;
        last[i] = pref[i] - pref[j];

        while(q.size() && last[i] + pref[i] < last[q.back()] + pref[q.back()])
            q.pop_back();
        q.push_back(i);
    }
    return n - dp[n];
}

int main()
{
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    cout<<solve(n, arr);
    return 0;
}