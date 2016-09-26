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
        else
            printf("Please specify a valid parameter");
    }



    /** printf("status: %u\n", status); */
    /** stest = push_solution(NOACT, stest); */
    /** print_solution(stest, 1); */
    /** print_solution(solution, 1); */
    /** solution_to_json(solution, str); */
    /** printf("steps: \n%s\n", str); */

    return 0;
}
