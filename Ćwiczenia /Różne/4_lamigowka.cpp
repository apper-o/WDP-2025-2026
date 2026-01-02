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
    map<long long, int> mp;
    for(int i=0;i<n;i++)
        mp[arr[i]]++;
    int res = 0;
    for(auto [a, b] : mp)
    {
        mp[2 * a] += b / 2; // zalozenie x > 0
        res += b%2;
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
    auto res = lamigowka(arr);
    cout<<res<<"\n";
    return 0;
}