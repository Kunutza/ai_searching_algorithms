#ifndef SEARCH_H
#define SEARCH_H

#include <stdlib.h>
#include <math.h>
#include "node.h"

int heuristic(int p[N]);
// This function adds a pointer to a new leaf search-tree node at the front of the frontier.
// This function is called by the depth-first search algorithm.
int add_frontier_front(struct tree_node *node);
// This function adds a pointer to a new leaf search-tree node at the back of the frontier.
// This function is called by the breadth-first search algorithm.
int add_frontier_back(struct tree_node *node);
// This function adds a pointer to a new leaf search-tree node within the frontier.
// The frontier is always kept in increasing order wrt the f values of the corresponding
// search-tree nodes. The new frontier node is inserted in order.
// This function is called by the heuristic search algorithm.
int add_frontier_in_order(struct tree_node *node);

// This function initializes the search, i.e. it creates the root node of the search tree
// and the first node of the frontier.
void initialize_search(int puzzle[N], int method);

int is_solution(int p[N]);
// This function checks whether two puzzles are equal.
// Inputs:
//		p1[N][N]	: A puzzle
//		p2[N][N]	: A puzzle
int equal_puzzles(int p1[N],int p2[N]);
// This function checks whether a node in the search tree
// holds exactly the same puzzle with at least one of its
// predecessors. This function is used when creating the childs
// of an existing search tree node, in order to check for each one of the childs
// whether this appears in the path from the root to its parent.
// This is a moderate way to detect loops in the search.
int check_with_parents(struct tree_node *new_node);
int calculate_child(struct tree_node *current_node, int method, int operation);
int find_children(struct tree_node *current_node, int method);
struct tree_node *search(int method);

#endif
