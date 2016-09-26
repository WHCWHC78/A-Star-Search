#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#include "a_star_bfs.h"
#include "queue.h"

enum STATUS a_star_bfs(
        struct problem *problem, 
        struct node *node, 
        struct solution **solution, 
        uint8_t f_limit)
{
    enum STATUS status = FAILURE;
    struct queue *successors = NULL;
    uint8_t count;

    if (problem->goal_test(node->state)) {
        (*solution) = push_solution(node->action, NULL);
        status = SUCCESS;

        goto IDS_FREE;
    }

    for (count = 4; (status != SUCCESS) && count; --count) {
        if (((problem->actions(node->state[0], node->action)) >> 
                    (count - 1)) & 1) {
            struct node *child = child_node(problem, node, 1 << (count - 1));

            successors = enq(successors, child);
        }
    }

    if (successors == NULL) { // empty queue
        status = FAILURE;

        goto IDS_FREE;
    }

    while (successors != NULL) {
        struct node *best;

        if (status == SUCCESS) {
            successors = deq(successors, &best);
            free(best);
            continue;
        }

        successors = deq(successors, &best);
        /** printf("f_limit = %u\n", f_limit); */
        /** printf("best->f = %u\n", best->f); */

        if (best->f > f_limit) {
            node->f = best->f; // update parent's f-value
            status = CUTOFF;

            goto IDS_EXIT;
        }
        else if (successors != NULL) {
            status = a_star_bfs(
                    problem, 
                    best, 
                    solution,
                    (compare(f_limit, successors->node->f) <= 1 ? 
                     f_limit : 
                     successors->node->f));
        }
        else
            status = a_star_bfs(
                    problem, 
                    best, 
                    solution,
                    f_limit);;

        switch (status) {
            case CUTOFF:
                successors = enq(successors, best);
                /** printf("CUTOFF!!!\n"); */
                break;
            case FAILURE:
                // Impossible for 8-puzzle to have unavailable move.
                /** printf("FAILURE!!!\n"); */
                break;
            case SUCCESS:
                (*solution) = push_solution(node->action, *solution);
                /** printf("SUCCESS!!!\n"); */
                break;
        }
    }

IDS_FREE: 
    free(node->state);

    if (node->parent != NULL)
        free(node);

IDS_EXIT:
    return status;
}

