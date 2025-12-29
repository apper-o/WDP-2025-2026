#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

int wakacje(int k, int r, vector<int> arr)
{
    if(arr.empty())
        return 0;
    int res = 1;
    sort(arr.begin(), arr.end());
    for(int i=0,j=0;i<arr.size();i++)
    {
        if(arr[i] - arr[j] > 2 * r || i - j + 1 > k)
        {
            res++;
            j = i;
        }
    }
    return res;
}

int main()
{
    return 0;
}