#ifndef WRITER_H
#define WRITER_H

#include <stdlib.h>
#include "../search/node.h"
#include "../definitions.h"
// Giving a (solution) leaf-node of the search tree, this function computes
// the moves of the blank that have to be done, starting from the root puzzle,
// in order to go to the leaf node's puzzle.
// Inputs:
//		struct tree_node *solution_node	: A leaf-node
// Output:
//		The sequence of blank's moves that have to be done, starting from the root puzzle,
//		in order to receive the leaf-node's puzzle, is stored into the global variable solution.
void extract_solution(struct tree_node *solution_node);
// This function writes the solution into a file
// Inputs:
//		char* filename	: The name of the file where the solution will be written.
// Outputs:
//		Nothing (apart from the new file)
void write_solution_to_file(char* filename, int solution_length, int *solution, int starting_value);

#endif
