#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
using namespace std;

const int INF = 1e9;

void get(int k, const vector<pair<int, int>> &last, const vector<pair<int, int>> &first, map<int, vector<pair<int, int>>> &mp, set<int> &active)
{
    for(int i=0,j=0;j<first.size();j++)
    {
        while(i < last.size() && last[i].second < first[j].first - 1)
            i++;
        if(i == last.size())
            break;
        if(last[i].second == first[j].first - 1)
        {
            mp[k+1].push_back({last[i].first, first[j].second});
            active.insert(k+1);
        }
    }
}

int segment(int n, const vector<int> &arr)
{
    map<int, vector<pair<int, int>>> mp;
    set<int> active;

    int res = 0;

    for(int i=0;i<n;i++)
    {
        active.insert(arr[i]);
        mp[arr[i]].push_back({i, i});
        res = max(res, arr[i]);
    }

    while(!active.empty())
    {
        int k = *active.begin();
        active.erase(active.begin());
        res = max(res, k);
        if(!mp[k - 1].empty())
        {
            vector<pair<int, int>> last, first;
            // k po lewej | k - 1 po prawej
            for(auto i : mp[k])
                last.push_back(i);
            for(auto i : mp[k-1])
                first.push_back(i);
            sort(last.begin(), last.end());
            sort(first.begin(), first.end());
            get(k, last, first, mp, active);

            last.clear(), first.clear();
            // k - 1 po lewej | k po prawej
            for(auto i : mp[k-1])
                last.push_back(i);
            for(auto i : mp[k])
                first.push_back(i);
            sort(last.begin(), last.end());
            sort(first.begin(), first.end());
            get(k, last, first, mp, active);
        }
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
    cout<<segment(n, arr);
    return 0;
}