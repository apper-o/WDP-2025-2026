#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

struct SegTree
{
    int size;
    vector<int> st;

    SegTree(int n)
    {
        size = 1;
        while(size <= n)
            size *= 2;
        st.resize(2 * size, INF);
    }

    void update(int id, int val)
    {
        id += size;
        if(st[id] <= val)
            return;
        st[id] = val;
        while(id / 2)
        {
            id /= 2;
            st[id] = min(st[2 * id], st[2 * id + 1]);
        }
    }

    int query(int a, int b)
    {
        a += size;
        b += size;
        int res = min(st[a], st[b]);
        while(a / 2 != b / 2)
        {
            if(a % 2 == 0)
                res = min(res, st[a+1]);
            if(b % 2 == 1)
                res = min(res, st[b - 1]);
            a/=2;
            b/=2;
        }
        return res;
    }
};

int moc(const vector<pair<pair<int, int>, int>> &t, int n, int a, int b)
{
    vector<pair<pair<int, int>, int>> arr;
    for(int i=0;i<n;i++)
        if(!(t[i].first.second < a) && !(t[i].first.first > b))
            arr.push_back({{max(t[i].first.first - a + 1, 1), min(b, t[i].first.second) - a + 1}, t[i].second});
    sort(arr.begin(), arr.end(), [] (const auto &a, const auto &b) {
        return a.first.first < b.first.first;
    });
    b -= a - 1;
    n = arr.size();
    SegTree tree(b+1);
    tree.update(0, 0);
    for(int i=0;i<n;i++)
    {
        auto [a, b] = arr[i].first;
        int val = tree.query(a - 1, b - 1);
        tree.update(b, val + arr[i].second);
    }
    int res = tree.query(b, b);
    return (res == INF ? -1 : res);
}

int main()
{
    int n, a, b;
    cin>>n>>a>>b;
    vector<pair<pair<int, int>, int>> arr(n);
    for(int i=0;i<n;i++)
        cin>>arr[i].first.first>>arr[i].first.second>>arr[i].second;
    cout<<moc(arr, n, a, b);
    return 0;
}