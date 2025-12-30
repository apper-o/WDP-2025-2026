#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

void step(int &a ,int &b)
{
    int tmp = b;
    b = a + b;
    a = tmp;
}

vector<int> get(const vector<int> &fib, int n)
{
    vector<int> res;
    int i = 0;
    while(fib[i] < n)
        i++;
    while(n)
    {
        i--;
        if(fib[i] <= n)
        {
            res.push_back(fib[i]);
            n -= fib[i];
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> podzial(int n)
{
    vector<int> fib;
    int sum = 0;
    int a = 1, b = 1;
    while(sum < n)
    {
        sum += b;
        fib.push_back(b);
        step(a, b);
    }
    fib.push_back(b);
    vector<int> A = get(fib, sum - n);
    vector<int> res;
    for(int i=0,j=0;i<fib.size()-1;i++)
    {
        if(j < A.size() && A[j] == fib[i])
            j++;
        else
            res.push_back(fib[i]);
    }
    return res;
}

int main()
{
    auto res = podzial(42);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}