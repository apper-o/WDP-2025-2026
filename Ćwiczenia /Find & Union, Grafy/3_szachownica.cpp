#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

int get(int *p, int v)
{
    return (v == p[v] ? v : p[v] = get(p, p[v]));
}

void unite(int *p, int *sz, int a, int b)
{
    int ra = get(p, a);
    int rb = get(p, b);
    if(ra == rb)
        return;
    if(sz[ra] < sz[rb])
        std::swap(ra, rb);
    sz[ra] += sz[rb];
    p[rb] = ra;
}

int solve(const std::vector<std::pair<int, int>> &towers)
{
    std::vector<std::pair<int, std::pair<int, int>>> v;
    for(int i=0;i<towers.size();i++)
        v.push_back({i, towers[i]});
    int *p = (int *)malloc(((int)towers.size() + 1) * sizeof(int));
    int *sz = (int *)calloc((int)towers.size(), sizeof(int));
    for(int i=1;i<=towers.size();i++)
        p[i] = i;
    sort(v.begin(), v.end(), [] (std::pair<int, std::pair<int, int>> a, std::pair<int, std::pair<int, int>> b) {
        return a.second.first < b.second.first;
    });
    for(int i=1;i<v.size();i++)
        if(v[i].second.first == v[i-1].second.first)
            unite(p, sz, v[i].first, v[i-1].first);
    sort(v.begin(), v.end(), [] (std::pair<int, std::pair<int, int>> a, std::pair<int, std::pair<int, int>> b) {
        return a.second.second < b.second.second;  
    });
    for(int i=1;i<v.size();i++)
        if(v[i].second.second == v[i-1].second.second)
            unite(p, sz, v[i].first, v[i-1].first);
    int res = 0;
    for(int i=0;i<=v.size();i++)
        if(p[i] == i)
            res++;
    free(p);
    free(sz);
    return res;
}

int main() 
{
    return 0;
}