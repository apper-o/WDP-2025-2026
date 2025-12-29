#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

vector<int> ciag(int n)
{
    n--;
    int a=1, b=1, c=1;
    vector<int> res;
    vector<int> fib = {1, 1};
    while(fib.back() < n)
        fib.push_back({fib[fib.size() - 1] + fib[fib.size() - 2]});
    for(int i=fib.size()-1;i>=0;i--)
    {
        if(fib[i] <= n)
        {
            n -= fib[i];
            res.push_back(fib[i]);
        }
    }
    res.push_back(1);
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    int n = 6;
    vector<int> res = ciag(n);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}