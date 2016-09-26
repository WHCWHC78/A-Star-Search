#include <fcgi_stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "a_star_bfs.h"

int main(void)
{
    struct problem problem;
    struct node node;
    struct solution *solution = NULL;
    enum STATUS status = FAILURE;

    char str[50], *q_str;
    uint8_t count;

    init_problem(&problem);

    while(FCGI_Accept() >= 0) {
        printf( "Content-type: text/plain\r\n\r\n");

        q_str = getenv("QUERY_STRING");

        if (strcmp(q_str, "compute") == 0) {
            root_node(&problem, &node);
            status = a_star_bfs(&problem, &node, &solution, 100);
            if (status == SUCCESS) {
                solution_to_json(solution, str);
                printf("%s", str);
            }
            else
                printf("0");
        }
        else if (strncmp(q_str, "init=", 5) == 0) {
            if (strlen(q_str) != 14) {
                /** printf("You have to enter exactly 9 tiles."); */
                printf("0");
                continue;
            }

            for (count = 9; count; --count) {
                uint8_t val = (*(q_str + 5 + (count - 1))) - 0x30;
                problem.initial_state[count - 1] = val;
                /** printf("%u ", val); */
            }

            /** printf("\n"); */
            printf("1");
        }
        else if (strcmp(q_str, "get_init") == 0) {
            for (count = 0; count < 9; ++count)
                printf("%u", problem.initial_state[count]);
        }
        else
            printf("0");
            /** printf( "Please specify a valid parameter.\n" */
                    /** "Your parameter is \"%s\".", q_str); */
    }



    /** printf("status: %u\n", status); */
    /** stest = push_solution(NOACT, stest); */
    /** print_solution(stest, 1); */
    /** print_solution(solution, 1); */
    /** solution_to_json(solution, str); */
    /** printf("steps: \n%s\n", str); */

    return 0;
}
