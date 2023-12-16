#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#include "validate.h"
#include "../definitions.h"

void syntax_message()
{
	printf("puzzle <method> <starting-value> <goal-value> <output-file>\n\n");
	printf("where: ");
	printf("<method> = breadth|depth|best|astar\n");
    printf("<starting-value> integer of the initial value of the puzzle.\n");
    printf("<goal-value> integer of the desirable final value.\n");
	printf("<output-file> is the file where the solution will be written.\n");
}

int get_method(char* s)
{
	if (strcmp(s,"breadth")==0)
		return  BREADTH;
	else if (strcmp(s,"depth")==0)
		return DEPTH;
	else if (strcmp(s,"best")==0)
		return BEST;
	else if (strcmp(s,"astar")==0)
		return ASTAR;
	else
		return -1;
}

int is_integer(char* c) {
    int i;
    for (i = 0; c[i] != 0; i++) {
        if (!isdigit(c[i])) {
            return false;
        }
    }

    return true;
};

int is_valid_integer(char* nptr) {
    // Check if string number is a valid long and then check if it is small enough to be an integer
    
    // Check for validity of long
    char* endptr = NULL;
    int base = 10;
    long number = 0;

    number = strtol(nptr, &endptr, base);

    if (errno == ERANGE && number == LONG_MAX)
        // overflow occured
        return -1;
    else if (errno != 0 && number == 0)
        // unspecified error occured
        return -2;
    else if (errno == 0 && nptr && *endptr != 0)
        // valid, but additional characters remain (it is too big to be an integer)
        return -3;
    else if (errno == 0 && nptr && !*endptr) {
        // is valid but we are not still sure if it is too big
    };

    // Check if size if small enough to be an integer
    if (number >= INT_MAX)
        // number is too big to be an integer
        return -3;
    
    // the number is valid, return the number
    return number;
};

int validate_puzzle(char* sv, char* gv, int *starting_value, int *goal_value) {
    // check if sv and gv are integers
    if (!is_integer(sv)) {
        printf("<starting_value> is not an integer.\n");
        return -1;
    }
    if (!is_integer(gv)) {
        printf("<goal-value> is not an integer.\n");
        return -1;
    }

    // if one of two values is bigger than max int then termiminate
    int s_value = is_valid_integer(sv);
    switch (s_value) {
        case -1:
            // overflow occured
            printf("<starting-value> is too big.\n");
            return -1;
        case -2:
            // unspecified error occured
            printf("<starting-value> unspecified error occured.\n");
            return -1;
        case -3:
            // number is too big to be an integer
            printf("<starting-value> is too big to be an integer.\n"); 
            return -1;
    } 
    int g_value = is_valid_integer(gv);
    switch (g_value) {
        case -1:
            // overflow occured
            printf("<goal-value> is too big.\n");
            return -1;
        case -2:
            // unspecified error occured
            printf("<goal-value> unspecified error occured.\n");
            return -1;
        case -3:
            // number is too big to be an integer
            printf("<goal-value> is too big to be an integer.\n"); 
            return -1;
    } 

    // For puzzle to be valid s_value must be <= g_value
    // if (s_value > g_value) {
    //     printf("<starting-value> is bigger than <goal-value>.\n");
    //     return -1;
    // }

    *starting_value = s_value;
    *goal_value = g_value;

    return 0;
};
