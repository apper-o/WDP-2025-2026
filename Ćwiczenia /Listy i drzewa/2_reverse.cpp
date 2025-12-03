#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <stack>
#include <vector>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct Node{
    int val;
    struct Node *next;
    // struct Node *prev;
} node; 

void update(node *list)
{
    node *prev = list;
    node *curr = list->next;
    while(curr != NULL)
    {
        node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list -> next = prev;
}

int main()
{
    node **head = (node**)malloc(5 * sizeof(node*));
    for(int i=0;i<5;i++)
        head[i] = (node*)malloc(sizeof(node));
    for(int i=0;i<5;i++)
        head[i]->val = i;
    for(int i=0;i<4;i++)
        head[i]->next = head[i+1];
    head[4]->next = NULL;

    update(head[0]);

    // Sprawdzenie wyniku (0 1 2 3 4) -> (0 4 3 2 1)
    node *tmp = head[0];
    for(int i=0;i<5;i++)
    {
        printf("%d ", tmp->val);
        tmp = tmp->next;
    }
    
    return 0;
}