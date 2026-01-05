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

long long gcd(long long a, long long b)
{
    return (b == 0 ? a : gcd(b, a % b));
}

bool dfs(long long a, long long b, int limit, long long min_s, vector<int> &fractions)
{
    if(a == 0)
        return true;
    if(limit == 0)
        return false;
    // 1 / s <= a / b => s >= b / a
    long long down = max(min_s, (b + a - 1) / a);
    // 1 / s * limit >= a / b => s <= b * limit / a
    long long up = b * limit / a;
    for(long long s=down;s<=up;s++)
    {
        // a / b - 1 / s = (as - b) / bs 
        long long l = a * s - b;
        long long m = b * s;

        fractions.push_back(s);
        long long g = gcd(l, m);
        l /= g;
        m /= g;
        if(dfs(l, m, limit - 1, s + 1, fractions))
            return true;
        fractions.pop_back();
    }
    return false;
}

vector<int> rozklad(int l, int m)
{
    if(l == 1)
        return vector<int>(1, m);
    vector<int> fractions;
    for(int max_cnt=2;!dfs(l, m, max_cnt, 2, fractions);max_cnt++)
        fractions.clear();
    return fractions;
}

int main()
{
    int l, m;
    cin>>l>>m;
    auto res = rozklad(l, m);
    for(int i : res)
        cout<<1<<"/"<<i<<" ";
    return 0;
}