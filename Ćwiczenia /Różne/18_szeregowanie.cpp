#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;

struct pii
{
    double a, b;
    int id;
};

vector<int> solve(int n, vector<pii> &arr)
{
    sort(arr.begin(), arr.end(), [] (const auto &a, const auto &b) {return a.b * b.a < b.b * a.a;});
    vector<int> res(n);
    for(int i=0;i<n;i++)
        res[i] = arr[i].id;
    return res;
}

int main() 
{
    int n;
    cin>>n;
    vector<pii> arr(n);
    for(int i=0;i<n;i++)
    {
        cin>>arr[i].a>>arr[i].b;
        arr[i].id = i + 1;
    }
    auto res = solve(n, arr);
    for(int i : res)
        cout<<i<<"\n";    
    return 0;
}
