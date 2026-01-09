#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9;

bool check(const vector<int> &arr, int k, int x)
{
    int last = arr[0] + x;
    int placed = 1;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i] - x > last)
        {
            if(placed == k)
                return 0;
            placed++;
            last = arr[i] + x;
        }
    }
    return 1;
}

vector<int> solve(const vector<int> &arr, int k)
{
    int n = arr.size();
    int lo = 0, hi = arr[n-1] - arr[0];
    while(lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if(check(arr, k, mid))  
            hi = mid;
        else
            lo = mid + 1;
    }
    vector<int> res;
    res.push_back(arr[0] + lo);
    for(int i=1;i<n;i++)
        if(arr[i] - lo > res.back())
            res.push_back(arr[i] + lo);
    return res;
}


int main() 
{
    int n, k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = solve(arr, k);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}
