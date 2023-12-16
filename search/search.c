#include "search.h"
#include <limits.h>
#include <stdio.h>


int heuristic(int p[N]) {
    int distance = abs(p[1] - p[0]);

    return distance;
};

// This function adds a pointer to a new leaf search-tree node at the front of the frontier.
// This function is called by the depth-first search algorithm.
// Inputs:
//		struct tree_node *node	: A (leaf) search-tree node.
// Output:
//		0 --> The new frontier node has been added successfully.
//		-1 --> Memory problem when inserting the new frontier node .
int add_frontier_front(struct tree_node *node)
{
	// Creating the new frontier node
	struct frontier_node *new_frontier_node=(struct frontier_node*)
                                malloc(sizeof(struct frontier_node));
	if (new_frontier_node==NULL) {
        printf("Memory problem when inserting the new frontier node.\n");
        return -1;
    }

	new_frontier_node->n = node;
	new_frontier_node->previous = NULL;
	new_frontier_node->next = frontier_head;
// ERROR
	if (frontier_head==NULL) {
		frontier_head=new_frontier_node;
		frontier_tail=new_frontier_node;
	}
	else
	{
		frontier_head->previous=new_frontier_node;
		frontier_head=new_frontier_node;
	}

	return 0;
}

// This function adds a pointer to a new leaf search-tree node at the back of the frontier.
// This function is called by the breadth-first search algorithm.
// Inputs:
//		struct tree_node *node	: A (leaf) search-tree node.
// Output:
//		0 --> The new frontier node has been added successfully.
//		-1 --> Memory problem when inserting the new frontier node .
int add_frontier_back(struct tree_node *node)
{
	// Creating the new frontier node
	struct frontier_node *new_frontier_node=(struct frontier_node*) malloc(sizeof(struct frontier_node));
	if (new_frontier_node==NULL)
		return -1;

	new_frontier_node->n=node;
	new_frontier_node->next=NULL;
	new_frontier_node->previous=frontier_tail;

	if (frontier_tail==NULL)
	{
		frontier_head=new_frontier_node;
		frontier_tail=new_frontier_node;
	}
	else
	{
		frontier_tail->next=new_frontier_node;
		frontier_tail=new_frontier_node;
	}

	return 0;
}

// This function adds a pointer to a new leaf search-tree node within the frontier.
// The frontier is always kept in increasing order wrt the f values of the corresponding
// search-tree nodes. The new frontier node is inserted in order.
// This function is called by the heuristic search algorithm.
// Inputs:
//		struct tree_node *node	: A (leaf) search-tree node.
// Output:
//		0 --> The new frontier node has been added successfully.
//		-1 --> Memory problem when inserting the new frontier node .
int add_frontier_in_order(struct tree_node *node)
{
	// Creating the new frontier node
	struct frontier_node *new_frontier_node=(struct frontier_node*)
                malloc(sizeof(struct frontier_node));
	if (new_frontier_node==NULL)
		return -1;

	new_frontier_node->n=node;
	new_frontier_node->previous=NULL;
	new_frontier_node->next=NULL;

	if (frontier_head==NULL)
	{
		frontier_head=new_frontier_node;
		frontier_tail=new_frontier_node;
	}
	else
	{
		struct frontier_node *pt;
		pt=frontier_head;

		// Search in the frontier for the first node that corresponds to either a larger f value
		// or to an equal f value but larger h value
		// Note that for the best first search algorithm, f and h values coincide.
		while (pt!=NULL && (pt->n->f<node->f || (pt->n->f==node->f && pt->n->h<node->h))) {
            pt=pt->next;
        }

		if (pt!=NULL)
		{
			// new_frontier_node is inserted before pt .
			if (pt->previous!=NULL)
			{
				pt->previous->next=new_frontier_node;
				new_frontier_node->next=pt;
				new_frontier_node->previous=pt->previous;
				pt->previous=new_frontier_node;
			}
			else
			{
				// In this case, new_frontier_node becomes the first node of the frontier.
				new_frontier_node->next=pt;
				pt->previous=new_frontier_node;
				frontier_head=new_frontier_node;
			}
		}
		else
		{
			// if pt==NULL, new_frontier_node is inserted at the back of the frontier
			frontier_tail->next=new_frontier_node;
			new_frontier_node->previous=frontier_tail;
			frontier_tail=new_frontier_node;
		}
	}

	return 0;
}

// This function initializes the search, i.e. it creates the root node of the search tree
// and the first node of the frontier.
void initialize_search(int puzzle[N], int method)
{
	struct tree_node *root=NULL;	// the root of the search tree.

	// Initialize search tree
	root=(struct tree_node*) malloc(sizeof(struct tree_node));
	root->parent=NULL;
	root->operation=-1;
    root->p[0] = puzzle[0];
    root->p[1] = puzzle[1];
    root->step = 0;

	root->g=0;
	root->h=heuristic(root->p);
	if (method==BEST)
		root->f=root->h;
	else if (method==ASTAR)
		root->f=root->g+root->h;
	else
		root->f=0;

	// Initialize frontier
	add_frontier_front(root);
}

int is_solution(int p[N]){
    printf("%d, %d\n", p[0], p[1]);
    return p[0] == p[1];
}

// This function checks whether two puzzles are equal.
// Inputs:
//		p1[N]	: A puzzle
//		p2[N]	: A puzzle
// Output:
//		1 --> The puzzles are equal
//		0 --> The puzzles are not equal
int equal_puzzles(int p1[N],int p2[N])
{
    if (p1[0]!=p2[0]) {
	    return 0;
    }
	return 1;
}

// This function checks whether a node in the search tree
// holds exactly the same puzzle with at least one of its
// predecessors. This function is used when creating the childs
// of an existing search tree node, in order to check for each one of the childs
// whether this appears in the path from the root to its parent.
// This is a moderate way to detect loops in the search.
// Inputs:
//		struct tree_node *new_node	: A search tree node (usually a new one)
// Output:
//		0 --> No coincidence with any predecessor
//		1 --> Loop detection
int check_with_parents(struct tree_node *new_node)
{
	struct tree_node *parent=new_node->parent;
	while (parent!=NULL)
	{
		if (equal_puzzles(new_node->p, parent->p))
			return 1;
		parent=parent->parent;
	}
	return 0;
}

int calculate_child(struct tree_node *current_node, int method, int operation){

    // Initializing the new child
    int cost;
    struct tree_node *child=(struct tree_node*) malloc(sizeof(struct tree_node));
    if (child==NULL) return -1;

    child->parent = current_node;

    // MAKE SWITCH
    switch (operation) {
        case ADD:
            child->operation = ADD;
            cost = 2;
            child->p[0] = current_node->p[0] + 1;
            break;
        case SUBTRACT:
            child->operation = SUBTRACT;
            cost = 2;
            child->p[0] = current_node->p[0] - 1;
            break;
        case DUPLICATE:
            child->operation = DUPLICATE;
            cost = ceil((double)(abs(current_node->p[0]) / 2.0)) + 1;
            child->p[0] = current_node->p[0] * 2;
            break;
        case DOUBLE_DOWN:
            child->operation = DOUBLE_DOWN;
            cost = ceil((double)(abs(current_node->p[0]) / 4.0)) + 1;
            child->p[0] = (int)(current_node->p[0] / 2);
            break;
        case SQUARE:
            child->operation = SQUARE;
            cost = ((current_node->p[0]*current_node->p[0]) - abs(current_node->p[0])) / 4 + 1;
            child->p[0] = current_node->p[0] * current_node->p[0];
            break;
        case SQUARE_ROOT:
            child->operation = SQUARE_ROOT;
            cost = (abs(current_node->p[0]) - (int)sqrt((double)abs(current_node->p[0]))) / 4 + 1;
            child->p[0] = (int)sqrt((double)current_node->p[0]);
            break;
    }
    child->g = current_node->g + cost;	
    child->p[1] = current_node->p[1];
    child->step = current_node->step + 1;
    
    // Check for loops
    if (check_with_parents(child)){
        // In case of loop detection, the child is deleted
        free(child);
        // ORIGINALLY THE CHILD OF THE FIRST OPERATION WAS NOT SET TO NULL
        if (operation != ADD) {
            child=NULL;
        }
    }

    else
    {
        // Computing the heuristic value
        child->h=heuristic(child->p);
        if (method==BEST)
            child->f = child->h;
        else if (method==ASTAR)
            child->f = child->g + child->h;
        else
            child->f = 0;

        int err=0;
        if (method==DEPTH)
            err=add_frontier_front(child);
        else if (method==BREADTH)
            err=add_frontier_back(child);
        else if (method==BEST || method==ASTAR)
            err=add_frontier_in_order(child);
        if (err<0)
            return -1;
    }

    return 1;
}

// This function expands a leaf-node of the search tree.
// A leaf-node may have up to 4 childs. A table with 4 pointers
// to these childs is created, with NULLs for those childrens that do not exist.
// In case no child exists (due to loop-detections), the table is not created
// and a 'higher-level' NULL indicates this situation.
// Inputs:
//		struct tree_node *current_node	: A leaf-node of the search tree.
// Output:
//		The same leaf-node expanded with pointers to its children (if any).
int find_children(struct tree_node *current_node, int method)
{
    int last_err = 0;
    // Add 1,       final value: X+1,        cost: 2,               X<10^9
    if (current_node->p[0] < INT_MAX) {
        last_err = calculate_child(current_node, method, ADD);
        if (last_err < 0 ) return last_err;
    }
    // Subtract 1,  final value: X-1,        cost: 2,               X>0
    if (current_node->p[0] > 0) {
        last_err = calculate_child(current_node, method, SUBTRACT);
        if (last_err < 0 ) return last_err;
    }
    // Duplicate,   final value: 2X,         cost: ceil(X/2)+1,     X>0, 2X<=10^9
    if (current_node->p[0] > 0 && current_node->p[0] * 2 <= INT_MAX) {
        last_err = calculate_child(current_node, method, DUPLICATE);
        if (last_err < 0 ) return last_err;
    }
    // Double down, final value: floor(X/2), cost: ceil(X/4)+1,     X>0
    if (current_node->p[0] > 0) {
        last_err = calculate_child(current_node, method, DOUBLE_DOWN);
        if (last_err < 0 ) return last_err;
    }
    // Square,      final value: X^2,        cost: (X^2-X)/4+1,     X^2<=10^9
    if (current_node->p[0]*current_node->p[0] <= INT_MAX) {
        last_err = calculate_child(current_node, method, SQUARE);
        if (last_err < 0 ) return last_err;
    }
    // Square root, final value: sqrt(X),    cost: (X-sqrt(X))/4+1, X>1, X perfect square
    if (current_node->p[0] > 1 && sqrt((double)current_node->p[0])*sqrt((double)current_node->p[0]) == (double)current_node->p[0]) {
        last_err = calculate_child(current_node, method, SQUARE_ROOT);
        if (last_err < 0 ) return last_err;
    }

	return 1;
}


struct tree_node *search(int method) {
    clock_t t;
	int i, err;
	struct frontier_node *temp_frontier_node;
	struct tree_node *current_node;

	while (frontier_head!=NULL)
	{
		t=clock();
		if (t-t1 > CLOCKS_PER_SEC*TIMEOUT)
		{
			printf("Timeout\n");
			return NULL;
		}

		// Extract the first node from the frontier
		current_node = frontier_head->n;
		if (is_solution(current_node->p))
			return current_node;

		// Delete the first node of the frontier
		temp_frontier_node=frontier_head;
		frontier_head = frontier_head->next;
		free(temp_frontier_node);
		if (frontier_head==NULL)
			frontier_tail=NULL;
		else
			frontier_head->previous=NULL;

		// Find the children of the extracted node
		int err=find_children(current_node, method);

		if (err<0)
	        {
            		printf("Memory exhausted while creating new frontier node. Search is terminated...\n");
			return NULL;
        	}
	}

	return NULL;
}

