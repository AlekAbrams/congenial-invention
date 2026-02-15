#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "ls2.h"

/**
 * Main function
 * Usage: ls2 <path> [exact-match-pattern]
 */
int main(int argc, char* argv[]) {
	// stack stores the lines to print out
	stack_t *s = initstack();


	if (argc < 2 || argc > 3) {
        // Not enough arguments
        fprintf(stderr, "Usage: %s <path> [exact-match-pattern]\n", argv[0]);
        return 1;
    }

	if (argc == 2){
		//Mode 1
		printf("DEBUG: Mode 1 selected\n");
		mode1(argv[1], 0);
		
	} else if (argc == 3){
		//Mode 2
		printf("DEBUG: Mode 2 selected\n");

		stack_t *results = initstack();
		mode2(argv[1], argv[2], results);
		while (results->size > 0) {
    		char *path = pop(results);
    		print_chain(path);
    		free(path);
		}
		freestack(results);
	}
	
	// free stack
	freestack(s);
	return 0;
}
