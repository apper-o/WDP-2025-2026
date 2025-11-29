#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct
{
    int a, b;
} pair;

int comp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int solve(int n, pair *arr)
{
    qsort(arr, n, sizeof(pair), comp);
    int *on = malloc((n+2) * sizeof(int));
    on[0] = on[n+1] = 0;
    for(int i=1;i<=n;i++)
        on[i] = 1;
    int res = 1, curr = 1;
    for(int i=0;i<n;i++)
    {
        int id = arr[i].b;
        on[id]=0;
        if(on[id-1] && on[id+1])
            curr++;
        if(!on[id-1] && !on[id+1])
            curr--;
        res = max(res, curr);
    }
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    pair *arr = malloc(n * sizeof(pair));
    for(int i=0;i<n;i++)
    {
        scanf("%d", &arr[i].a);
        arr[i].b = i+1;
    }
    printf("%d", solve(n, arr));
    return 0;
}