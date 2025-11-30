#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct
{
    int id, t;
} *Counter;

int *tab;
int cnt = 0;
int time = 0;

Counter make()
{
    Counter c = malloc(sizeof(Counter));
    tab[cnt] = 0;
    c->id = cnt;
    c->t = time;
    cnt++;
    return c;
}

int inc(Counter c)
{
    if((*c).t < time)
    {
        tab[c->id] = 0;
        c->t = time;        
    }
    return ++tab[c->id];
}

void reset()
{
    time++;
}

int main()
{
    tab = malloc(1000 * sizeof(Counter));
    return 0;
}