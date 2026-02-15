#ifndef LS2_H_INCLUDED
#define LS2_H_INCLUDED

#include "stack.h"

// function declarations, globals, constants here
#define TRUE 1
#define FALSE 0
#define INDENT "    "
void mode1(const char *path, int depth);
void mode2(const char *path, const char *pattern, stack_t *results);
void print_chain(char *path);

extern stack_t *s;  // pointer to the stack to hold the listings

#endif
