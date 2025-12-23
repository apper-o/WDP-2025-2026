#include <iostream>
#include <vector>
#include <deque>
#include <assert.h>
using namespace std;

struct element
{
    int id, value;
};

struct interval
{
    int a, b;
    double score;
};

void update(element x, deque<element> &mn, deque<element> &mx)
{
    while(mn.size() && mn.back().value >= x.value)
        mn.pop_back();
    mn.push_back(x);
    while(mx.size() && mx.back().value <= x.value)
        mx.pop_back();
    mx.push_back(x);
}

double get_score(int x1, int x2, int diff)
{
    return (double)(x1 - x2) * (x1 - x2) / diff;
}

bool valid(int new_y, const deque<element> &dq_mn, const deque<element> &dq_mx, int U)
{
    if(dq_mn.empty())
        return true;
    int mn = dq_mn.front().value;
    int mx = dq_mx.front().value;
    return abs(max(mx, new_y) - min(mn, new_y)) <= U;
}

vector<pair<int, int>> solve(int n, long long U, const vector<int> &X, const vector<int> &Y)
{
    deque<element> mx, mn;
    deque<interval> dq;
    vector<pair<int, int>> res;
    for(int a=0,b=0;a<n;a++)
    {
        int prev_b = b; 
        while(b < n && valid(Y[b], mn, mx, U))
        {
            update({b, Y[b]}, mn, mx);
            b++;
        }
        if(prev_b != b) // sprawdzam czy przedział jest maksymalny
        {
            double score = get_score(X[a], X[b-1], b-a); 
            while(dq.size() && dq.back().score < score)
                dq.pop_back();
            dq.push_back((interval){a, b-1, score});
        }
        if(mn.size() && mn.front().id == a)
            mn.pop_front();
        if(mx.size() && mx.front().id == a)
            mx.pop_front();
        res.push_back({dq.front().a+1, dq.front().b+1});
        if(dq.size() && dq.front().b == a)
            dq.pop_front();
    }
    return res;
}

int main()
{
    int n;
    long long U;
    cin>>n>>U;
    vector<int> X(n), Y(n);
    for(int i=0;i<n;i++)
        cin>>X[i]>>Y[i];
    vector<pair<int, int>> res = solve(n, U, X, Y);
    for(int i=0;i<n;i++)
        cout<<res[i].first<<" "<<res[i].second<<"\n";
    return 0;
}