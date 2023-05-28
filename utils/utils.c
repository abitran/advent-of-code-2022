#include "../include/utils.h"
#include <stdbool.h>

#define VAL 500

int compare(const void *a, const void *b)
{
    int aval = *((int *)a);
    int bval = *((int *)b);
    if (aval == bval)
        return 0;
    else if (aval < bval)
        return -1;
    else
        return 1;
}

typedef struct{
    int front;
    int rear;
    int data[VAL];
}queue;

bool qfull(queue *q)
{
    return q->rear == VAL-1 ? true:false;
}


bool qempty(queue *q)
{

    return q->rear < q->front ? true:false;
}


void enqueue(queue *q, int el)
{
    if (!qfull(q))
        q->data[++q->rear] = el;
}

void dequeue(queue *q)
{
    int ret;

    if (!qfull(q))
        ret = q->data[q->front++];

}


int peekq(queue *q)
{
    return q->data[q->front];
}
