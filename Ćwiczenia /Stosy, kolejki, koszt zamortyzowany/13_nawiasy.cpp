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

int nawiasy(char znaki[])
{
    int n = 0;
    while(znaki[n] != '\0')
        n++;
    int cnt[2] = {0, 0};
    int curr = 0, res = 0;
    for(int i=0;i<n;i++)
    {
        curr++;
        cnt[(znaki[i] == '(')]++;
        if(cnt[0] == cnt[1])
            res = max(res, curr);
        else if(cnt[0] > cnt[1])
        {
            curr=0;
            cnt[0] = cnt[1] = 0;
        }
    }
    cnt[0] = cnt[1] = 0;    
    curr = 0;
    for(int i=n-1;i>=0;i--)
    {
        curr++;
        cnt[(znaki[i] == '(')]++;
        if(cnt [0] == cnt[1])
            res = max(res, curr);
        else if(cnt[1] > cnt[0])
        {
            curr = 0;
            cnt[0] = cnt[1] = 0;
        }
    }
    return res;
}

int main() 
{
    char test2[] = ")(()())";
    printf("Wynik: %d\n", nawiasy(test2));
    return 0;
}