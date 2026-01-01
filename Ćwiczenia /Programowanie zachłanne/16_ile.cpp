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

int ile(const vector<pair<int, int>> &t, int a, int b)
{
    vector<pair<int, int>> arr; 
    for(auto [x, y] : t)
    {
        if(x <= a && y >= b)
            return 1;
        if(y >= a && x <= b)
        {
            x = max(a, x);
            y = min(b, y);
            arr.push_back({x, y});
        }
    }
    int n = arr.size();
    sort(arr.begin(), arr.end(), [] (pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    });
    int res = 0;
    int mx = a;
    int mx_nxt = a;
    for(int i=0;i<n;i++)
    {
        if(arr[i].first > mx_nxt)
            return -1;
        if(arr[i].first > mx)  
        {
            res++;
            mx = mx_nxt;
        }
        mx_nxt = max(mx_nxt, arr[i].second);
    }
    if(mx < b)
    {
        mx = mx_nxt;
        res++;
    }
    return (mx == b ? res : -1);
}

int main()
{
    int n;
    int a, b;
    cin>>n;
    vector<pair<int, int>> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i].first>>arr[i].second;
    cin>>a>>b;
    auto res = ile(arr, a, b);
    return 0;
}