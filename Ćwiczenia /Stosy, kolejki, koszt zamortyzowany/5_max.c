#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

void solve(int arr[], int n)
{
    int l = 1, r = 1;
    int *res = malloc((n+1) * sizeof(int));
    int *num = malloc((n+1) * sizeof(int));
    res[1] = 1;
    num[1] = arr[1];
    for(int i=2;i<=n;i++)
    {  
        int lo = l, hi = r + 1;
        while(lo < hi)
        {
            int mid = lo + (hi - lo) / 2;
            if(num[mid] > arr[i])
                lo = mid + 1;
            else
                hi = mid; 
        }
        res[i] = hi;
        while(r > 0 && num[r] < arr[i])
            r--;
        num[++r] = arr[i];
    }
    for(int i=1;i<=n;i++)
        printf("%d ", i - res[i] + 1);
}

int main()
{
    int n;
    scanf("%d", &n);
    int *arr = malloc((n+1) * sizeof(int));
    for(int i=1;i<=n;i++)
        scanf("%d", &arr[i]);
    solve(arr, n);
    return 0;
}