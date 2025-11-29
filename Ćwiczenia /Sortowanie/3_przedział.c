#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int comp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int przedzial(int *arr, int n, int r)
{
    qsort(arr, n, sizeof(int), comp);
    int res = 0, cnt = 0;
    for(int i=0,j=0;i<n;i++)
    {
        while(j < n - 1 && arr[j+1] - arr[i] <= 2*r)
            j++;
        if(cnt < j - i + 1) 
        {
            cnt = j - i;
            res = arr[j] - r; 
        }
    }
    return res;
}

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    int *arr = malloc(n * sizeof(int));
    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);
    printf("%d", przedzial(arr, n, r));
    return 0;
}