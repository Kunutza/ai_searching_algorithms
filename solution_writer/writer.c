#include "writer.h"
#include <math.h>

// Giving a (solution) leaf-node of the search tree, this function puts
// the solution of the puzzle into a seperate dynamic table, and also finds
// the sum of the moves
// Inputs:
//		struct tree_node *solution_node	: A leaf-node
void extract_solution(struct tree_node *solution_node) {
	int i;

	struct tree_node *temp_node=solution_node;

    solution_length = solution_node->step;
	solution= (int*) malloc(solution_length*sizeof(int));
	temp_node=solution_node;
	i=solution_length;
	while (temp_node->parent!=NULL)
	{
		i--;
		solution[i] = temp_node->operation;
		temp_node=temp_node->parent;
	}
}
// This function writes the solution into a file
// Inputs:
//		char* filename	: The name of the file where the solution will be written.
// Outputs:
//		Nothing (apart from the new file)
// This function writes the solution into a file
// Inputs:
//		char* filename	: The name of the file where the solution will be written.
// Outputs:
//		Nothing (apart from the new file)
void write_solution_to_file(char* filename, int solution_length, int *solution, int starting_value)
{
    int current_value = starting_value;
    int cost = 0;
    int total_cost = 0;

	int i;
	FILE *fout;
	fout=fopen(filename,"w");
	if (fout==NULL)
	{
		printf("Cannot open output file to write solution.\n");
		printf("Now exiting...");
		return;
	}

	for (i=0;i<solution_length;i++){
        switch(solution[i]) {
            case ADD:
                cost = 2;
                break;
            case SUBTRACT:
                cost = 2;
                break;
            case DUPLICATE:
                cost = ceil((double)(abs(current_value) / 2.0)) + 1;
                break;
            case DOUBLE_DOWN:
                cost = ceil((double)(abs(current_value) / 4.0)) + 1;
                break;
            case SQUARE:
                cost = ((current_value*current_value) - abs(current_value)) / 4 + 1;
                break;
            case SQUARE_ROOT:
                cost = (abs(current_value) - (int)sqrt((double)abs(current_value))) / 4 + 1;
                break;
        }

        total_cost += cost;
    }
    fprintf(fout, "%d %d\n", solution_length, total_cost);

	for (i=0;i<solution_length;i++){
        switch(solution[i]) {
            case ADD:
                cost = 2;
                current_value += 1;
                fprintf(fout,"ADD %d %d\n", current_value, cost);
                break;
            case SUBTRACT:
                cost = 2;
                current_value -= 1;
                fprintf(fout,"SUBTRACT %d %d\n", current_value, cost);
                break;
            case DUPLICATE:
                cost = ceil((double)(abs(current_value) / 2.0)) + 1;
                current_value *= 2;
                fprintf(fout,"DUPLICATE %d %d\n", current_value, cost);
                break;
            case DOUBLE_DOWN:
                cost = ceil((double)(abs(current_value) / 4.0)) + 1;
                current_value = (int)(current_value / 2);
                fprintf(fout,"DOUBLE_DOWN %d %d\n", current_value, cost);
                break;
            case SQUARE:
                cost = ((current_value*current_value) - abs(current_value)) / 4 + 1;
                current_value *= current_value;
                fprintf(fout,"SQUARE %d %d\n", current_value, cost);
                break;
            case SQUARE_ROOT:
                cost = (abs(current_value) - (int)sqrt((double)abs(current_value))) / 4 + 1;
                current_value = (int)sqrt((double)current_value);
                fprintf(fout,"SQUARE_ROOT %d %d\n", current_value, cost);
                break;
        }
    }
    fclose(fout);
}
