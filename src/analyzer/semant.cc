

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "utilities.h"
#include <semant-errors.h>
#include <type-table.h>
#include <class-tree.h>
#include <cassert>
#include <environment.h>
#include <queue>

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
    TypeTable typetable(classes);
    Environment env;

    propagate_containing_class(NULL);
    validate_all(typetable);
    initialize_constants();
    install_basic_classes();

    ClassTree class_tree(classes, Object);
    scope_check(class_tree, typetable, env);
    type_check(class_tree, typetable, env);
}


///////////////////////////////////////////////////////////////
// To make sure classes are validated first (since class errors
// are fatal). The validation on the AST is done in a BFS fashion
// this requires propagate_containing_class to be called first 
// since there is no other way to know which class contains the 
// error if we are doing a BFS
////////////////////////////////////////////////////////////////
/**
  * @brief calls validate on all the nodes in the AST
  * @modifies: AST
  * @requires: prograpagate_containing_class to be called first
  * @param TypeTable the type table initialized with all the classes
  */ 
void program_class::validate_all(TypeTable& typetable)
{
    queue<tree_node*> q; 
    q.push(this);
    unordered_set<tree_node*> visited = { this };

    while(!q.empty())
    {
        tree_node* cur = q.front();
        q.pop();
        //cur->validate();

    }
} 


//////////////////////////////////////////////////////////////
//
// Helpers for the semant methods
//
//////////////////////////////////////////////////////////////




