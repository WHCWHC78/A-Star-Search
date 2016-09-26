#include <stdlib.h>

#include "queue.h"

uint8_t compare(uint8_t a, uint8_t b)
{
    if (a == b)
        return 0;
    else if (a < b)
        return 1;
    else
        return 2;
}

struct queue *enq(struct queue *q, struct node *node)
{
    struct queue *tmp;

    if (node == NULL) {
        return q;
    }
    else if (q == NULL) {
        tmp = (struct queue *)malloc(sizeof(struct queue));
        tmp->node = node;
        tmp->next = NULL;

        return tmp;
    }
    else {
        switch (compare(q->node->f, node->f)) {
            case 0:
            case 1:
                tmp = enq(q->next, node);
                q->next = tmp;

                return q;

            case 2:
                tmp = (struct queue *)malloc(sizeof(struct queue));
                tmp->node = node;
                tmp->next = q;

                return tmp;

            default:
                return q;
        }
    }
}

struct queue *deq(struct queue *q, struct node **node)
{
    if (q == NULL) {
        (*node) = NULL;

        return q;
    }
    else {
        struct queue *tmp = q->next;
        (*node) = q->node;
        free(q);

        return tmp;
    }
}

