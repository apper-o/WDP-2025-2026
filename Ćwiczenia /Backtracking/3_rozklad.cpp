#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

bool prime(long long n)
{
    if(n < 2)
        return false;
    if(n == 2)
        return true;
    for(int i=3;i*i<=n;i+=2)
        if(n % i == 0)
            return false;
    return true;
}

pair<long long, long long> solve(long long n)
{
    if(prime(n))
        return {n, 0};
    if(n % 2 == 0)
        for(int i=3;i<=n/2;i++)
            if(prime(i) && prime(n-i))
                return {i, n-i};
    return solve(n-3);
}

int main()
{
    // Hipoteza Goldbacha (słaba) - każdą liczbę naturalną da się przedstawić jako sumę co najwyżej 3 liczb pierwszych 
    long long n;
    cin>>n;
    pair<long long, long long> res = solve(n);
    if(res.first + res.second != n)
        cout<<3<<" "<<res.first<<" "<<res.second<<"\n";
    else if(res.second == 0)
        cout<<res.first<<"\n";
    else
        cout<<res.first<<" "<<res.second<<"\n";
    return 0;
}