#ifndef _QUEUE_H
#define _QUEUE_H

#include <stdint.h>

#include "node.h"

struct queue {
    struct node     *node;
    struct queue    *next;
};

struct queue *enq(struct queue *q, struct node *node);
struct queue *deq(struct queue *q, struct node **node);

uint8_t compare(uint8_t a, uint8_t b);

#endif /* ifndef QUEUE_H */
