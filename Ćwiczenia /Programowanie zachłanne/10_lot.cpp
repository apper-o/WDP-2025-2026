#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

vector<int> solve(int n, const vector<int> &p, const vector<int> &d)
{
    vector<int> res(n);
    vector<int> pref(2 * n + 1);
    for(int i=1;i<=2*n;i++)
        pref[i] = pref[i-1] + p[(i-1) % n] - d[(i-1) % n];
    deque<int> dq;
    for(int i=1;i<=2*n;i++)
    {
        while(dq.size() && dq.front() < i - n)
            dq.pop_front();
        while(dq.size() && pref[dq.back()] >= pref[i])
            dq.pop_back();
        dq.push_back(i);
        if(i >= n)
            res[i - n] = (pref[dq.front()] - pref[i - n] >= 0);
    }
    return res;
}

int main()
{
    int n;
    cin>>n;
    vector<int> p(n);
    vector<int> d(n);
    for(int i=0;i<n;i++)
        cin>>p[i]>>d[i];
    auto res = solve(n, p, d);
    for(int i : res)
        cout<<(i ? "TAK" : "NIE")<<"\n";
    return 0;
}