

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "utilities.h"
#include <semant-errors.h>
#include <type-table.h>
#include <class-tree.h>
#include <cassert>
#include <environment.h>

extern int semant_debug;
extern char *curr_filename;

// prototypes for helpers 
void semant_check_classes();
void terminate_on_errors(void);


/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    propagate_containing_class(NULL);
    initialize_constants();
    install_basic_classes();
}






//////////////////////////////////////////////////////////////
//
// Helpers for the semant methods
//
//////////////////////////////////////////////////////////////




