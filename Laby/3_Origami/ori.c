#include <stdio.h>
#include <stdlib.h>

#define eps 1e-9

/* type = 'P': Rectangle with lower left edge in x1, y1 and upper right edge in x2, y2 */
/* type = 'K': Circle in the point (x1, y1) with redius r */
/* type = 'Z': Fold operation. Folds the id-th paper along line (x1, y1), (x2, y2) */
typedef struct
{
    int type, id;
    double x1, y1, x2, y2, r;
} paper;

/* Global array that represents all sheets of paper. */
paper *papers;

/* Returns the cross product of two vectors. */
double cross(double x1, double y1, double x2, double y2)
{
    return  x1 * y2 - y1 * x2;
}

/* Returns the dot product of two vectors. */
double dot(double x1, double y1, double x2, double y2)
{
    return x1 * x2 + y1 * y2;
}

long long solve(int id, double x, double y)
{
    if(papers[id].type == 'P') // Rectangle
    {
        /* Checks whether the point is inside the rectangle. */
        return (papers[id].x1 - eps <= x && x <= papers[id].x2 + eps && papers[id].y1 - eps <= y && y <= papers[id].y2 + eps);
    }
    else if(papers[id].type == 'K') // Circle
    {
        /* Checks whether the distance from the middle of the circle is smaller or equal to its radius. */
        double dx = x - papers[id].x1, dy = y - papers[id].y1, r = papers[id].r + eps;
        return (dx * dx + dy * dy <= r * r);
    }
    else // Folding
    {
        double x1 = papers[id].x1, y1 = papers[id].y1, x2 = papers[id].x2, y2 = papers[id].y2;
        /* Cross product of the fold line vector and the vector from (x1, y1) to (x, y). */
        double cp = cross(x2 - x1, y2 - y1, x - x1, y - y1);
        if(-eps <= cp && cp <= eps) // Point on the line
            return solve(papers[id].id, x, y);
        else if(cp < 0) // Point on the right side
            return 0;
        else // Point on the left side
        {
            double dx_line = x2 - x1, dy_line = y2 - y1;
            /* Calculate the projection of the point on the line with dot product */
            /* and divide the length of this projection by dy_line to get proportion. */
            double proportion = dot(x - x1, y - y1, x2 - x1, y2 - y1) / (dx_line * dx_line + dy_line * dy_line);
            /* Point (xs, ys) is the projection of the point (x, y) on the line. */
            double xs = x1 + proportion * dx_line, ys = y1 + proportion * dy_line;
            /* Point (xk, yk) is the reflection of (x, y) across the fold line */
            double xk = x + 2 * (xs - x), yk = y + 2 * (ys - y);
            return solve(papers[id].id, xk, yk) + solve(papers[id].id, x, y);
        }
    }
}

int main()
{
    int n, q;
    if(scanf("%d %d", &n, &q) != 2)
    {
        printf("Error! Wrong inupt values: n, q\n");
        exit(1);
    }
    papers = malloc((size_t)n * sizeof(paper));
    if(papers == NULL)
    {
        printf("Error! Wrong memory allocation.\n");
        exit(0);
    }
    for(int i=0;i<n;i++)
    {
        char type;
        if(scanf(" %c", &type) != 1)
        {
            printf("Error! Wrong input values: type\n");
            exit(0);
        }
        if(type == 'P')
        {
            if(scanf("%lf %lf %lf %lf", &papers[i].x1, &papers[i].y1, &papers[i].x2, &papers[i].y2) != 4)
            {
                printf("Error! Wrong input values: x1, y1, x2, y2 (rectangle)\n");
                exit(0);
            }
        }   
        else if(type == 'K')
        {
            if(scanf("%lf %lf %lf", &papers[i].x1, &papers[i].y1, &papers[i].r) != 3)
            {
                printf("Error! Wrong input values: x1, y1, r (circle)\n");
                exit(0);
            }
        }
        else
        {
            if(scanf("%d %lf %lf %lf %lf", &papers[i].id, &papers[i].x1, &papers[i].y1, &papers[i].x2, &papers[i].y2) != 5)
            {
                printf("Error! Wrong input values: id, x1, y1, x2, y2 (folding)\n");
                exit(0);
            }
            papers[i].id -= 1;
        }
        papers[i].type = type;
    }
    for(int i=0;i<q;i++)
    {
        int id;
        double x, y;
        if(scanf("%d %lf %lf", &id, &x, &y) != 3)
        {
            printf("Error! Wrong input values: id, x, y (query)\n");
            exit(0);
        }
        printf("%lld\n", solve(id - 1, x, y));
    }
    free(papers);
    return 0;
}
