#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct
{
    int a, b;
} pair;

int comp(const void *a, const void *b)
{
    if(((*(pair *)a).a == (*(pair *)b).a))
        return ((*(pair *)a).b - (*(pair *)b).b);
    return ((*(pair *)a).a - (*(pair *)b).a);
}

int check(pair *arr, int n, int k, int mid)
{   
    int start = INF, cnt = 0;
    for(int i=0;i<2*n;i++)
    {
        if(arr[i].a - start + 1 >= k)
            return 1;
        cnt += (arr[i].b == 0 ? 1 : -1);
        if(start != INF && cnt < mid)
            start = INF;
        else if(start == INF && cnt >= mid)
            start = arr[i].a;
    }
    return 0;
}

int solve(pair *arr, int n, int k)
{
    qsort(arr, 2*n, sizeof(pair), comp);
    int lo = 0, hi = n;
    while(lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        if(check(arr, n, k, mid))
            lo = mid;
        else
            hi = mid - 1;
    }
    return lo;
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    pair *arr = malloc(2 * n * sizeof(pair));
    for(int i=0;i<n;i++)
    {
        scanf("%d%d", &arr[2*i].a, &arr[2*i+1].a);
        arr[2*i].b = 0;
        arr[2*i+1].b = 1;
    }
    printf("%d", solve(arr, n, k));
    return 0;
}