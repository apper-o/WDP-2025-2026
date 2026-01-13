#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MOD = 1e9 + 7;

vector<int> get_fib(int x)
{
    vector<int> f = {1, 2};
    while(f.back() < x)
        f.push_back(f[f.size()-2] + f[f.size()-1]);
    vector<int> res;
    for(int i=f.size()-1;i>=0;i--)
    {
        if(x >= f[i])
        {
            res.push_back(i + 1);
            x -= f[i];
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int rozklady(int x)
{
    vector<int> d = get_fib(x);
    int v0 = 1; // ostatnia rozbita
    int v1 = (d[0] - 1) / 2; // ostatnia nierozbita
    for(int i=1;i<d.size();i++)
    {
        int new_v0 = v0 + v1;
        int new_v1 = v0 * (d[i] - d[i-1]) / 2 + v1 * (d[i] - d[i-1] + 1) / 2;
        v0 = new_v0;
        v1 = new_v1;
    }
    return v0 + v1;
}

int main() 
{
    return 0;
}
