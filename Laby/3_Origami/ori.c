#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define eps 1e-9

/* type = 'P': Rectangle with lower left edge in x1, y1 and upper right edge in x2, y2 */
/* type = 'K': Circle in the point (x1, y1) with redius r */
/* type = 'Z': Fold operation. Folds the id-th paper along line (x1, y1), (x2, y2) */
typedef struct
{
    int type, id;
    double x1, y1, x2, y2, r;
} paper;

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

void get_reflection(double *x_res, double *y_res, double x, double y, double x1, double y1, double x2, double y2)
{
    double dx_line = x2 - x1, dy_line = y2 - y1;
    /* Calculates the projection of the point on the line with a dot product */
    /* and divides the length of this projection by dy_line to get proportion. */
    double proportion = dot(x - x1, y - y1, x2 - x1, y2 - y1) / (dx_line * dx_line + dy_line * dy_line);
    /* Point (x_projection, y_projection) is the projection of the point (x, y) about the line. */
    double x_projection = x1 + proportion * dx_line, y_projection = y1 + proportion * dy_line;
    /* Point (x_reflection, y_reflection) is the reflection of (x, y) about the fold line */
    *x_res = x + 2 * (x_projection - x);
    *y_res = y + 2 * (y_projection - y);
}

long long solve(paper *papers, int id, double x, double y)
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
            return solve(papers, papers[id].id, x, y);
        else if(cp < 0) // Point on the right side
            return 0;
        else // Point on the left side
        {
            double x_reflection, y_reflection;
            get_reflection(&x_reflection, &y_reflection, x, y, x1, y1, x2, y2);
            return solve(papers, papers[id].id, x_reflection, y_reflection) + solve(papers, papers[id].id, x, y);
        }
    }
}

void get_input(paper *papers, int n)
{
    for(int i=0;i<n;i++)
    {
        char type;
        int input_type = scanf(" %c", &type);
        assert(input_type == 1);
        if(type == 'P')
        {
            int input_P = scanf("%lf %lf %lf %lf", &papers[i].x1, &papers[i].y1, &papers[i].x2, &papers[i].y2);
            assert(input_P == 4);
        }   
        else if(type == 'K')
        {
            int input_K = scanf("%lf %lf %lf", &papers[i].x1, &papers[i].y1, &papers[i].r);
            assert(input_K == 3);
        }
        else
        {
            int input_F = scanf("%d %lf %lf %lf %lf", &papers[i].id, &papers[i].x1, &papers[i].y1, &papers[i].x2, &papers[i].y2);
            assert(input_F == 5);
            papers[i].id -= 1;
        }
        papers[i].type = type;
    }
}

int main()
{
    int n, q;
    int input_init = scanf("%d %d", &n, &q);
    assert(input_init == 2);
    /* Array that represents all sheets of paper. */
    paper *papers = (paper *)malloc((size_t)n * sizeof(paper));
    assert(papers != NULL);
    get_input(papers, n);
    for(int i=0;i<q;i++)
    {
        int id;
        double x, y;
        int input_query = scanf("%d %lf %lf", &id, &x, &y);
        assert(input_query == 3);
        printf("%lld\n", solve(papers, id - 1, x, y));
    }
    free(papers);
    return 0;
}
