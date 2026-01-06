#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

const int INF = 1e9;

bool check(int x, const vector<int> &p, const vector<int> &a)
{
    int sum = 0, j = 0;
    for(int i=0;i<p.size();i++)
    {
        sum += p[i];
        while(j < a.size() && i == a[j])
        {
            sum = max(0, sum - x);
            j++;
        }
    }
    sum = max(0, sum - x * ((int)a.size() - j));
    return sum == 0;
}

int solve(int n, int m, const vector<int> &p, const vector<int> &a)
{
    int last = n - 1;
    while(last >= 0 && p[last] == 0)
        last--;
    if(last == -1)
        return 0;
    if(last > a[m - 1])
        return -1;
    int lo = 0, hi = 0;
    for(int i=0;i<n;i++)
        hi += p[i];
    while(lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        if(check(mid, p, a))
            hi = mid;
        else
            lo = mid + 1;
    }
    return hi;
}

int main()
{
    int n, m;
    cin>>n>>m;
    vector<int> p(n);
    vector<int> a(m);
    for(int i=0;i<n;i++)
        cin>>p[i];
    for(int i=0;i<m;i++)
        cin>>a[i];
    auto res = solve(n, m, p, a);
    cout<<res<<"\n";
    return 0;
}