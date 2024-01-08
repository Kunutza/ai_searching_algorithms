#include <stdlib.h>
#include <time.h>

#include "search/search.h"
#include "arguments_validation/validate.h"
#include "solution_writer/writer.h"
#include "definitions.h"

clock_t t1;				// Start time of the search algorithm
clock_t t2;				// End time of the search algorithm
                        
int solution_length;	// The lenght of the solution table.
int *solution;		// Pointer to a dynamic table with the moves of the solution.

struct frontier_node *frontier_head;	// The one end of the frontier
struct frontier_node *frontier_tail;	// The other end of the frontier

int main(int argc, char** argv) {
    // argv[1] = method
    // argv[2] = starting-value
    // argv[3] = goal-value
    // argv[4] = output file
    
    int err;
	struct tree_node *solution_node;
	int starting_value = 0;
    int goal_value = 0;
	int method;			

	if (argc!=5)
	{
		printf("Wrong number of arguments. Use correct syntax:\n");
		syntax_message();
		return -1;
	}

	method=get_method(argv[1]);
	if (method<0)
	{
		printf("Wrong method. Use correct syntax:\n");
		syntax_message();
		return -1;
	}

	err=validate_puzzle(argv[2], argv[3], &starting_value, &goal_value);
	if (err<0)
		return -1;

	printf("Solving %s using %s... ",argv[2],argv[1]);
	t1=clock();

    int puzzle[2] = {starting_value, goal_value};
 	initialize_search(puzzle, method);
 	solution_node = search(method);			// The main call
 
 	t2=clock();
 
 	if (solution_node!=NULL)
 		extract_solution(solution_node);
 	else
 		printf("No solution found.\n");
 
 	if (solution_node!=NULL)
 	{
 		printf(" Solution found! (%d steps)",solution_length);
 		printf(" Time spent: %f secs",((float) t2-t1)/CLOCKS_PER_SEC);
 		write_solution_to_file(argv[4], solution_length, solution, puzzle[0]);
 	}
 
 	return 0;

}
