#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

vector<int> silnie(int n)
{
    vector<int> res;
    int s = 1;
    int i = 2;
    while(s * i <= n)
    {
        s*=i;
        i++;
    }
    while(n)
    {
        res.push_back(i - 1);
        n -= s;
        while(n > 0 && s > n)
        {
            i--;
            s /= i;
        }
    }
    return res;
}

int main()
{
    int n;
    cin>>n;
    vector<int> res = silnie(n);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}