#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef enum pora {Wiosna, Lato, Jesień, Zima} pora;

int pory(int n, pora arr[])
{
    int dp[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            dp[i][j] = INT_MAX;
    int res = INT_MAX;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(((arr[i] + j) % 4 == 0 && dp[j][1] == INT_MAX) || dp[j][(arr[i] + j - 1 + 4) % 4] < i) 
            {
                dp[j][(arr[i] + j) % 4] = i;
                if(dp[j][3] != INT_MAX && dp[j][0] < dp[j][1] && dp[j][1] < dp[j][2] && dp[j][2] < dp[j][3])
                    res = min(res, dp[j][3] - dp[j][0] + 1);
            }
        }
    }
    return (res == INT_MAX ? -1 : res);
}

int main()
{
    int n;
    scanf("%d", &n);
    pora arr[] = {Wiosna, Lato, Jesień, Wiosna, Zima}; 
    printf("%d", pory(n, arr));
    return 0;
}