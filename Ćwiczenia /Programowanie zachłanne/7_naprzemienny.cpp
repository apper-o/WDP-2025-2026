#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

int naprzemienny(const vector<int> &arr)
{
    if(arr.empty())
        return 0;
    int res = 0;
    for(int j=0;j<2;j++)
    {
        int tick = j;
        int curr = 1;
        int last = arr[0];
        for(int i=1;i<arr.size();i++)
        {
            if(tick == 0 ? arr[i] > last : arr[i] < last)
            {
                curr++;
                tick ^= 1;
            }
            last = arr[i];
        }
        res = max(res, curr);

    }
    return res;
}

int main()
{
    return 0;
}