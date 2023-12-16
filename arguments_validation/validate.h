#ifndef VALIDATE_H
#define VALIDATE_H

void syntax_message();
int get_method(char* s);
int is_integer(char* c);
int is_valid_integer(char* nptr);
int validate_puzzle(char* sv, char* gv, int *starting_value, int *goal_value);

#endif
