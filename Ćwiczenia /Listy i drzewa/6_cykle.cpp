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

int check(node *list)
{
    node *a = list->next;
    node *b = a->next;
    while(b != NULL && a != b)
    {
        a = a->next;
        node *tmp = b->next;
        if(tmp == NULL)
            b = NULL;
        else
            b = (b->next)->next;
    }
    if(b==NULL) 
        return -1;
    a = list;
    while(a != b)
    {
        a = a->next;
        b = b->next;
    }
    int res = 1;
    b = b->next;
    while(a != b)
    {
        b = b->next;
        res++;
    }
    return res;
}

int main()
{
    // Tworzymy listę: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
    //                           ^                   |
    //                           |___________________|
    // Cykl: 3 -> 4 -> 5 -> 6 -> 7 -> 3 (długość 5)

    node *head = (node*)malloc(sizeof(node)); head->val = 1;
    node *n2 = (node*)malloc(sizeof(node)); n2->val = 2;
    node *n3 = (node*)malloc(sizeof(node)); n3->val = 3;
    node *n4 = (node*)malloc(sizeof(node)); n4->val = 4;
    node *n5 = (node*)malloc(sizeof(node)); n5->val = 5;
    node *n6 = (node*)malloc(sizeof(node)); n6->val = 6;
    node *n7 = (node*)malloc(sizeof(node)); n7->val = 7;

    head->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n7;
    
    // TWORZENIE CYKLU: 7 wskazuje na 3
    n7->next = n3;

    int len = check(head);

    if (len > 0) {
        printf("Lista zawiera cykl o dlugosci: %d\n", len);
    } else {
        printf("Lista nie zawiera cyklu.\n");
    }
    return 0;
}