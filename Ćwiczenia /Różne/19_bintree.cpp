#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int INF = 1e9;

typedef struct node *bin_tree;
struct node{
    int val;
    bin_tree left, right; 
};
const int NWD = -2;
const int NWW = -3;

pair<int, int> get(bin_tree t, int x)
{
    if(t->val >= 0)
    {
        if(x == 0)
            return {0, 30};
        int res = 0;
        int val = t->val;
        while(val % x == 0)
        {   
            res++;
            val /= x;
        }
        return {res, res};
    }
    else
    {
        auto [la, lb] = get(t->left, x);
        auto [ra, rb] = get(t->right, x);
        if(t->val == NWW)
            return {max(la, ra), max(lb, rb)};
        else
            return {min(la, ra), min(lb, rb)};
    }
}

void collect(bin_tree t, set<int> &primes)
{
    if(t->val > 0)
    {
        int x = t->val;
        for(int i=2;i*i<x;i++)
        {
            if(x % i == 0)
            {
                primes.insert(i);
                while(x % i == 0)
                    x /= i;
            }
        }
        if(x > 1)
            primes.insert(x);
    }
    else if(t->val < 0)
    {
        collect(t->left, primes);
        collect(t->right, primes);
    }
}

int wstaw(bin_tree t, int n)
{
    set<int> primes;
    collect(t, primes); 
    vector<pair<int, int>> p;
    vector<int> pow;
    for(int i=2;i*i<=n;i++)
    {   
        if(n % i == 0)
        {
            p.push_back({i, 0});
            pow.push_back(1);
            while(n % i == 0)
            {
                n /= i;
                pow.back() *= i;
                p.back().second++;
            }
        }
    }
    if(n > 1)
        p.push_back({n, 1});
    int res = 1;
    int i = 0;
    for(int d : primes)
    {
        auto [lo, hi] = get(t, d);
        if(i < p.size() && p[i].first == d)
        {
            auto [a, b] = p[i];
            if(b < lo || b > hi)
                return -1;
            if(lo < b)
                res *= pow[i];
        }
        else if(lo > 0)
            return -1;
    }
    return res;
}


int main() 
{
    int n;
    cin>>n;
    
    return 0;
}
