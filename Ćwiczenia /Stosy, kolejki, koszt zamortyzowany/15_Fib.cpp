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

int find(char s[], int n, int num, int pos)
{
    if(num == 1)
    {
        for(int i=pos;i<n;i++)
            if(s[i] == 'b')
                return i;
        return -1;
    }
    else if(num == 2)
    {
        for(int i=pos;i<n;i++)
            if(s[i] == 'a')
                return i;
        return -1;
    }
    else
    {
        int next = find(s, n, num-1, pos);
        if(next == -1)
            return -1;
        return find(s, n, num-2, next + 1);
    }
}

int slowa(char s[], int n)
{
    int tmp = find(s, n, 1, 0);
    if(tmp == -1)
        return 0;
    tmp = find(s, n, 2, 0);
    if(tmp == -1)
        return 1;
    int res = 3, last_pos = tmp; 
    while(res < 49)
    {
        tmp = find(s, n, res - 2, last_pos + 1);
        if(tmp == -1)
            break;
        last_pos = tmp;
        res++;
    }
    return res -1 ;
}

int main() 
{
    int n = 13;
    char test[] = "abbabacababab";
    printf("Wynik: %d\n", slowa(test, n)); // Powinno być 6
    return 0;
}