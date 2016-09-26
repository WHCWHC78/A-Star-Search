#ifndef _A_STAR_BFS_H
#define _A_STAR_BFS_H

#include "problem.h"
#include "node.h"

enum STATUS { 
    SUCCESS = 0,
    FAILURE,
    CUTOFF
};

enum STATUS a_star_bfs(
        struct problem *problem, 
        struct node *node, 
        struct solution **solution, 
        uint8_t f_limit);

#endif 
