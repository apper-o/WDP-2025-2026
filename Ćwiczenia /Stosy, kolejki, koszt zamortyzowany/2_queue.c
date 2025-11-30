#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

const int INF = 1e9;

typedef struct
{
    int *arr;
    int top;
    int cap;
} stack;

stack* create_stack()
{
    stack *s = malloc(sizeof(stack));
    s->cap = 1;
    s->top = -1;
    s->arr = malloc(sizeof(int));
    return s;
}

int stack_empty(stack *s)
{
    return (s->top == -1);
}

void stack_push(stack *s, int val)
{
    if(s->top + 1 == s->cap)
    {  
        s->cap *= 2;
        s->arr = realloc(s->arr, s->cap * sizeof(int));
    }
    s->arr[++(s->top)] = val;
}

int stack_pop(stack *s)
{
    if(s->top != -1)
        return s->arr[s->top--];
    return -1;
}

int stack_top(stack *s)
{
    if(s->top != -1)
        return s->arr[s->top];
    return -1;
}

typedef struct
{
    stack *in;
    stack *out;
} queue;

queue* create_queue()
{
    queue *q = malloc(sizeof(queue));
    q->in = create_stack();
    q->out = create_stack();
    return q;
}

void prepare_queue(queue *q)
{
    while(!stack_empty(q->in))
        stack_push(q->out, stack_pop(q->in));
}

int queue_front(queue *q)
{
    if(stack_empty(q->out))
        prepare_queue(q);
    return stack_top(q->out);
}

int queue_pop(queue *q)
{
    if(stack_empty(q->out))
        prepare_queue(q);
    return stack_pop(q->out);
}

void queue_push(queue *q, int val)
{
    stack_push(q->in, val);
}

int main()
{
    return 0;
}