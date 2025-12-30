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

vector<pair<int, int>> solve(int n, const vector<int> &d)
{
    int it = 0;
    for(int i=0;i<n;i++)
        it = max(it, d[i]);
    vector<vector<int>> lvl(it + 1);
    vector<pair<int, int>> adj;
    priority_queue<pair<int, int>> pq;
    for(int i=0;i<n;i++)
        pq.push({d[i], i});
    while(pq.size())
    {
        auto [d, v] = pq.top();
        pq.pop();
        stack<pair<int, int>> st;
        for(int i=0;i<d;i++)
        {
            st.push(pq.top());
            pq.pop();
            adj.push_back({v, st.top().second});
        }
        while(st.size())
        {
            pq.push({st.top().first - 1, st.top().second});
            st.pop();
        }
    }    
    return adj;
}

int main()
{
    int n;
    cin>>n;
    vector<int> d(n);
    for(int i=0;i<n;i++)
        cin>>d[i];
    auto res = solve(n, d);
    for(auto [a, b] : res)
        cout<<a+1<<" "<<b+1<<"\n";
    return 0;
}