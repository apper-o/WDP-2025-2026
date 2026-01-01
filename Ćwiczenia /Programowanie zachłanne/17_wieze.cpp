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

struct pii
{
    int a, b;
    int id;
};

vector<int> solve(int n, vector<pii> &arr)
{
    sort(arr.begin(), arr.end(), [] (const auto &a, const auto &b) { return (a.a == b.a ? a.b < b.b : a.a < b.a); });
    vector<int> res(n);
    priority_queue<pair<int, int>> pq;
    for(int i=1,j=0;i<=n;i++)
    {
        while(j < n && arr[j].a <= i)
        {
            pq.push({-arr[j].b, j});
            j++;
        }
        if(pq.empty())
            return {};
        auto [d, v] = pq.top();
        pq.pop();
        d = -d;
        if(d < i)
            return {};
        res[arr[v].id] = i;
    }
    return res;
}

int main()
{
    int n;
    cin>>n;
    vector<pii> X(n);
    vector<pii> Y(n);
    for(int i=0;i<n;i++)
    {
        cin>>X[i].a>>Y[i].a>>X[i].b>>Y[i].b;
        X[i].id = Y[i].id = i;
    }
    auto res_x = solve(n, X);
    auto res_y = solve(n, Y);
    if(res_y.empty() || res_x.empty())
        cout<<"NIE"<<"\n";
    else
        for(int i=0;i<n;i++)
            cout<<res_x[i]<<" "<<res_y[i]<<"\n";
    return 0;
}