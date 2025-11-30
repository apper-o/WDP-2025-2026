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
    return (*(int *)a - *(int *)b);
}

int solve(int *arr, int n, int k)
{
    int *q = malloc(n * sizeof(int));
    int a=0, b=0, c=-1;
    for(int i=0;i<k;i++)
    {
        int sum = 0;
        for(int j=0;j<2;j++)
        {
            if(b <= c && arr[a] < q[b])
                sum += arr[a++];
            else
                sum += q[b++];
        }
        q[++c] = sum;
    }
    return min(arr[a], q[b]);
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    int *arr = malloc((n+1) * sizeof(int));
    arr[n] = INF;
    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);
    printf("%d", solve(arr, n, k));
    return 0;
}