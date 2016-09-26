#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "node.h"

struct node *child_node(
        struct problem *problem, 
        struct node *parent, 
        uint8_t action)
{
    struct node *child = (struct node*)malloc(sizeof(struct node));

    child->state    = problem->result(parent->state, action);
    child->parent   = parent;
    child->action   = action;
    child->g        = parent->g + 1;
    child->h        = problem->h_func(child->state);
    child->f        = (child->g) + (child->h);

    return child;
}

/** @brief: Create root node */
void root_node(struct problem *problem, struct node *node)
{
    node->state = (uint8_t *)malloc(sizeof(uint8_t) * 9);

    memcpy(node->state, problem->initial_state, 9);

    node->parent    = NULL;
    node->action    = NOACT;
    node->g         = 0;
    node->h         = problem->h_func(node->state);
    node->f        = (node->g) + (node->h);
}

struct solution *push_solution(uint8_t action, struct solution *solution)
{
    if (solution == NULL) {
        solution = (struct solution *)malloc(sizeof(struct solution));

        solution->action    = action;
        solution->next      = NULL;
        solution->prev  = NULL;
    }
    else {
        struct solution *tmp = 
            (struct solution *)malloc(sizeof(struct solution));

        tmp->action         = action;
        tmp->next           = solution;
        tmp->prev       = NULL;
        solution->prev  = tmp;
        solution            = tmp;
    }

    return solution;
}

void print_solution(struct solution *solution, uint8_t count)
{
    printf("%02u: ", count);

    if (solution == NULL) {
        printf("No solution found!\n");

        return;
    }

    switch (solution->action) {
        case LEFT:
            printf("LEFT\n");
            break;
        case UP:
            printf("UP\n");
            break;
        case RIGHT:
            printf("RIGHT\n");
            break;
        case DOWN:
            printf("DOWN\n");
            break;
        default:
            printf("NOACT\n");
    }

    if (solution->next != NULL)
        print_solution(solution->next, count + 1);

    free(solution);
}

