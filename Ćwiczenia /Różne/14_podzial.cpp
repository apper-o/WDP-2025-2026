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

bool check(int max_sum, int k, const vector<int> &arr)
{
    for(int i=0,sum=0;i<arr.size();i++)
    {
        if(arr[i] > max_sum)
            return 0;
        if(sum + arr[i] > max_sum)
        {
            if(k == 0)
                return 0;
            k--;
            sum = arr[i];
        }
    }
    return 1;
}

vector<vector<int>> solve(int n, int k, const vector<int> &arr)
{
    vector<vector<int>> res(k);
    int lo = 0, hi = 0;
    for(int i=0;i<n;i++)
        hi += arr[i];
    while(lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if(check(mid, k, arr))
            lo = mid;
        else
            hi = mid - 1;
    }
    for(int i=0,sum=0,it=0;i<n;i++)
    {
        if(sum + arr[i] > lo)
        {
            sum = arr[i];
            it++;
        }
        res[it].push_back(arr[i]);
    }
    return res;
}

int main()
{
    int n, k;
    cin>>n>>k;
    vector<int> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = solve(n, k, arr);
    for(int i : res)
    {
        for(int j : i)
            cout<<j<<" ";
        cout<<"\n";
    }
    return 0;
}