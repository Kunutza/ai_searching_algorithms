#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include "../definitions.h"

struct tree_node
{
	int h;				// the value of the heuristic function for this node
	int g;				// the depth of this node wrt the root of the search tree
	int f;				// f=0 or f=h or f=h+g, depending on the search algorithm used.
	struct tree_node *parent;	// pointer to the parrent node (NULL for the root).
    // CHANGE THE DIRECTION WITH OPERATION
	int operation;			// The direction of the last move
    int step;
    int p[N];
};

// A node of the frontier. Frontier is kept as a double-linked list,
// for efficiency reasons for the breadth-first search algorithm.
struct frontier_node
{
	struct tree_node *n;			// pointer to a search-tree node
	struct frontier_node *previous;		// pointer to the previous frontier node
	struct frontier_node *next;		// pointer to the next frontier node
};

#endif
