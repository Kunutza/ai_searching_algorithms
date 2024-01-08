#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <time.h>

#define N 2

#define BREADTH 1
#define DEPTH   2
#define BEST    3
#define ASTAR   4

#define LOG 1 // When at 0 the programm does not print the operations that took place ("%d, %d", curret_value, goa_value)

// Add 1,       final value: X+1,        cost: 2,               X<10^9
// Subtract 1,  final value: X-1,        cost: 2,               X>0
// Duplicate,   final value: 2X,         cost: ceil(X/2)+1,     X>0, 2X<=10^9
// Double down, final value: floor(X/2), cost: ceil(X/4)+1,     X>0
// Square,      final value: X^2,        cost: (X^2-X)/4+1,     X^2<=10^9
// Square root, final value: sqrt(X),    cost: (X-sqrt(X))/4+1, X>1, X perfect square
#define ADD         1
#define SUBTRACT    2
#define DUPLICATE   3
#define DOUBLE_DOWN 4
#define SQUARE      5
#define SQUARE_ROOT 6

extern clock_t t1;				// Start time of the search algorithm
extern clock_t t2;				// End time of the search algorithm
#define TIMEOUT		10	// Program terminates after TIMEOUT secondss
                        
extern int solution_length;	// The lenght of the solution table.
extern int *solution;		// Pointer to a dynamic table with the moves of the solution.

extern struct frontier_node *frontier_head;	// The one end of the frontier
extern struct frontier_node *frontier_tail;	// The other end of the frontier

#endif
