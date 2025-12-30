#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

void step(long long &a, long long &b)
{
    long long tmp = b;
    b = a + b;
    a = tmp;
}

vector<long long> get(const vector<long long> &fib, long long n)
{
    // rozklad nie moze zawierac 3 kolejnych liczb Fibonacciego
    int i = 0;
    while(fib[i] < n)
        i++;
    vector<long long> res;
    while(n && i>=1)
    {
        i--;
        if(fib[i] <= n)
        {
            n-=fib[i];
            res.push_back(fib[i]);
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<long long> fibo(long long n)
{
    vector<long long> fib;
    vector<long long> res;
    long long a = 1, b = 1;
    long long sum = 0;
    while(sum < n)
    {
        sum += b;
        fib.push_back(b);
        step(a, b);
    }
    fib.push_back(b);
    auto A = get(fib, sum - n);
    if(A.size() && A[0] == -1)
        return vector<long long>();
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
    auto res = fibo(42);
    for(int i : res)
        cout<<i<<" ";
    return 0;
}