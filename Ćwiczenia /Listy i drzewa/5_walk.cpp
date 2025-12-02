#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct node{
    int val;
    struct node *lc;
    struct node *rc;
} node;

typedef struct
{
    node *vertex;  
    std::vector<node*> parent;  
} walk;

walk make_walk(node *t)
{
    walk res;
    res.vertex = t;
    return res;
}

void go_left(walk &w)
{
    if(w.vertex != NULL && w.vertex->lc != NULL)
    {
        w.parent.push_back(w.vertex);
        w.vertex = w.vertex->lc;
    }
}

void go_right(walk &w)
{
    if(w.vertex != NULL && w.vertex->rc != NULL)
    {
        w.parent.push_back(w.vertex);
        w.vertex = w.vertex->rc;
    }
}

void go_up(walk &w)
{
    if(w.parent.size())
    {
        w.vertex = w.parent.back();
        w.parent.pop_back();
    }
}

int lookup(const walk w)
{
    return w.vertex->val;
} 

node* new_node(int val)
{
    node* n = (node*)malloc(sizeof(node));
    n->val = val; n->lc = NULL; n->rc = NULL;
    return n;
}

int main() 
{
    // Budujemy drzewo:
    //      10
    //     /  \
    //    20   30
    node *root = new_node(10);
    root->lc = new_node(20);
    root->rc = new_node(30);

    // Tworzymy kursor
    walk w = make_walk(root); // Teraz przekazujemy wskaźnik 'root'

    printf("Korzen: %d\n", lookup(w)); // Powinno być 10

    go_left(w);
    printf("Lewy: %d\n", lookup(w));   // Powinno być 20

    go_up(w);
    printf("Powrot do gory: %d\n", lookup(w)); // Powinno być 10

    go_right(w);
    printf("Prawy: %d\n", lookup(w));  // Powinno być 30

    return 0;
}