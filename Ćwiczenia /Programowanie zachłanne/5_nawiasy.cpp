#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <set>
#include <queue>
using namespace std;

const int INF = 1e9;

enum nawias{Otwierający, Zamykający};

int nawiasy(vector<enum nawias> arr)
{
    if(n % 2)
        return -1;
    int res = 0;
    int sum = 0;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i] == Otwierający)
            sum++;
        else
            sum--;
        if(sum == -1)
        {
            sum = 1;
            res++;
        }
    }
    return res + sum / 2;
}

int main()
{
    return 0;
}