#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

void nawiasy(std::vector<int> arr)
{
    int n = arr.size();
    std::deque<int> q;
    int ra = 0, rb = -1;
    for(int a=0,b=0;b<n;b++)
    {
        while(q.size() && arr[q.back()] >= arr[b])
            q.pop_front();
        q.push_back(b);
        while(a <= b)
        {
            if(b - a + 1 <= arr[q.front()])
                break;
            if(q.front() == a)
                q.pop_front();
            a++;
        }
        if(rb - ra + 1 < b - a + 1)
        {
            rb = b;
            ra = a;
        }
    }
    printf("%d %d\n", ra, rb);
}

int main() {
    std::vector<int> a = {1, 5, 4, 3, 1};
    nawiasy(a);
    return 0;
}