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

vector<int> arr;

int solve(int n)
{
    sort(arr.begin(), arr.end());
    if(n == 1)
        return arr[0];
    int res = arr[1];
    for(int i=n-1;i>2;i-=2)
        res += min(arr[0] + 2 * arr[1] + arr[i], 2 * arr[0] + arr[i] + arr[i-1]);
    if(n % 2 == 1 && n > 2)
        return res += arr[0] + arr[2];
    return res;
}

int main()
{
    int n;
    cin>>n;
    arr.resize(n);
    for(int i=0;i<n;i++)
        cin>>arr[i];
    auto res = solve(n);
    cout<<res<<"\n";
    return 0;
}