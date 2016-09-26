#include <stdlib.h>
#include <stdio.h>

#include "a_star_bfs.h"

int main(void)
{
    struct problem problem;
    struct node node;
    struct solution *solution = NULL;
    enum STATUS status = FAILURE;

    init_problem(&problem);
    root_node(&problem, &node);

    /** printf("Initial state = \n"); */
    /** printf("%u\n", problem.initial_state[0]); */
    /** printf("%u\n", problem.initial_state[1]); */
    /** printf("%u\n", problem.initial_state[2]); */
    /** printf("%u\n", problem.initial_state[3]); */
    /** printf("%u\n", problem.initial_state[4]); */
    /** printf("%u\n", problem.initial_state[5]); */
    /** printf("%u\n", problem.initial_state[6]); */
    /** printf("%u\n", problem.initial_state[7]); */
    /** printf("%u\n", problem.initial_state[8]); */
    status = a_star_bfs(&problem, &node, &solution, 100);

    printf("status: %u\n", status);
    /** stest = push_solution(NOACT, stest); */
    /** print_solution(stest, 1); */
    print_solution(solution, 1);

    return 0;
}
