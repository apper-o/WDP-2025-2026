#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int NO_SOLUTION = -1;
const int NOT_FOUND = -1;

/* Stores the information about a motel */
typedef struct{
    int type;
    int dist;
} motel;

/* Stores indices of the best and second closest / farthest motels */
typedef struct{
    int best;
    int sec_best;
} pair;

/* Calculates the final score */
/* mode = 0: Minimal maximum distance between 3 different motels */
/* mode = 1: Maximal minimum distance between 3 different motels */
int calculate(motel *arr, pair *pref, pair* suff, int n, int mode)
{
    int res = (mode ? 0 : INT_MAX);
    for(int i=0;i<n;i++)
    {
        int l1 = pref[i].best, l2 = pref[i].sec_best;
        int r1 = suff[i].best, r2 = suff[i].sec_best;
        /* Checks whether there exist a motel on the right and a motel on the left */
        if(l1 != NOT_FOUND && r1 != NOT_FOUND)
        {
            int dist1 = arr[i].dist - arr[l1].dist;
            int dist2 = arr[r1].dist - arr[i].dist;
            if(arr[l1].type != arr[r1].type)
            {
                if(mode)
                    res = max(res, min(dist1, dist2));
                else
                    res = min(res, max(dist1, dist2));
            }
            else 
            {
                /* If the best motel on the left is the same as on the right then it is necessary to use second best*/
                if(pref[i].sec_best != NOT_FOUND)
                {
                    if(mode)
                        res = max(res, min(arr[i].dist - arr[l2].dist, dist2));
                    else
                        res = min(res, max(arr[i].dist - arr[l2].dist, dist2));
                }
                if(suff[i].sec_best != NOT_FOUND)
                {
                    if(mode)
                        res = max(res, min(dist1, arr[r2].dist - arr[i].dist));
                    else
                        res = min(res, max(dist1, arr[r2].dist - arr[i].dist));
                }
            }
        }
    }
    return res;
}

/* Returns the best value for minimal maximum distance between 3 different motels */
int solve_min_max(motel *arr, pair *pref, pair *suff, int n)
{ 
    pref[0] = (pair){NOT_FOUND, NOT_FOUND};
    suff[n-1] = (pair){NOT_FOUND, NOT_FOUND};
    for(int i=1;i<n;i++)
    {
        if(arr[i].type == arr[i-1].type)
            pref[i] = pref[i-1];
        else
        {
            pref[i].best = i-1;
            if(pref[i-1].best != NOT_FOUND)
                pref[i].sec_best = (arr[pref[i-1].best].type == arr[i].type ? pref[i-1].sec_best : pref[i-1].best);
            else
                pref[i].sec_best = NOT_FOUND;
        }
    }
    for(int i=n-2;i>=0;i--)
    {
        if(arr[i].type == arr[i+1].type)
            suff[i] = suff[i+1];
        else
        {
            suff[i].best = i+1;
            if(suff[i+1].best!=NOT_FOUND)
                suff[i].sec_best = (arr[suff[i+1].best].type == arr[i].type ? suff[i+1].sec_best : suff[i+1].best);
            else
                suff[i].sec_best = NOT_FOUND;
        }
    }
    return calculate(arr, pref, suff, n, 0);
}

/* Returns the best value for maximal minimum distance between 3 different motels */
int solve_max_min(motel *arr, pair *pref, pair *suff, int n)
{
    pref[0] = (pair){NOT_FOUND, NOT_FOUND};
    suff[n-1] = (pair){NOT_FOUND, NOT_FOUND};
    /* p = index of the first motel different than arr[0] */
    int p = 1;
    while(p < n && arr[p].type == arr[0].type)
        p++;
    int q = p+1;
    /* q = index of the first motel different than arr[0] and arr[p] */
    while(q < n && (arr[q].type == arr[p].type || arr[q].type == arr[0].type))
        q++;
    /* q>=n means that there doesn't exist 3 different types of motels */
    if(q>=n)
        return NO_SOLUTION;
    for(int i=1;i<n;i++)
    {
        if(arr[i].type == arr[i-1].type)
            pref[i] = pref[i-1];
        else
        {
            pref[i].best = (arr[i].type == arr[0].type ? p : 0);
            if(arr[i].type == arr[0].type || arr[i].type == arr[p].type)
                pref[i].sec_best = (q >= i ? NOT_FOUND : q);
            else
                pref[i].sec_best = (p >=i ? NOT_FOUND : p);
        }
    }
    /* It has been checked that there exist at least 3 different motels so p, q < 0 is impossible*/
    /* now p = index of the first motel different than arr[n-1] */
    p = n-2;
    while(arr[p].type == arr[n-1].type)
        p--;
    /* q = index of the first motel different than arr[n-1] and arr[p] */
    q = p - 1;
    while(arr[q].type == arr[p].type || arr[q].type == arr[n-1].type)
        q--;
    for(int i=n-2;i>=0;i--)
    {
        if(arr[i].type == arr[i+1].type)
            suff[i] = suff[i+1];
        else
        {
            suff[i].best = (arr[i].type == arr[n-1].type ? p : n-1);
            if(arr[i].type == arr[n-1].type || arr[i].type == arr[p].type)
                suff[i].sec_best = (q <= i ? NOT_FOUND : q);
            else
                suff[i].sec_best = (p <= i ? NOT_FOUND : p);
        }
    }
    return calculate(arr, pref, suff, n, 1);
}

int main()
{
    int n;
    if(scanf("%d", &n) != 1)
        return 1;
    assert(n>0);
    motel *arr = (motel*)malloc((size_t)n * sizeof(motel)); 
    /* pref[i] = indices of the best and second best motel on the i-th pefix */
    pair *pref = (pair*)malloc((size_t)n * sizeof(pair)); 
    /* suff[i] = indices of the best and second best motel on the i-th suffix */
    pair *suff = (pair*)malloc((size_t)n * sizeof(pair)); 
    if(arr == NULL || pref == NULL || suff == NULL)
    {
        free(arr);
        free(pref);
        free(suff);
        return 1;
    }
    for(int i=0;i<n;i++)
        if(scanf("%d%d", &arr[i].type, &arr[i].dist) != 2)
            return 1;
    int resmx=NO_SOLUTION, resmn;
    if(n>2)
    {
        resmx = solve_max_min(arr, pref, suff, n);
        resmn = solve_min_max(arr, pref, suff, n);
    }
    if(resmx == NO_SOLUTION)
        printf("%d %d", 0, 0);
    else
        printf("%d %d", resmn, resmx);
    free(arr);
    free(pref);
    free(suff);
    return 0;
}
