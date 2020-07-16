

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
#include <class-visitor.h>
#include <cassert>

#define SET_CONTAINS(set, element) (set.find((element)) != set.end())

extern int semant_debug;
extern char *curr_filename;

// prototypes for helpers 
void classes_to_map(Classes classes, unordered_map<Symbol, Class_>& classes_map);


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
    // preprocessing validations
    TypeTable typetable(classes);
    Environment env;
    install_basic_classes();
    propagate_containing_class(NULL);
    validate_all(typetable);
    initialize_constants();

    // scope and type checking
    sync_global_env(env);
    ClassTree class_tree(classes, Object);
    type_check(class_tree, typetable, env);

    uninstall_basic_classes();

    SemantErrorHandler& sem_err = SemantErrorHandler::instance();
    sem_err.terminate_on_errors();
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
        cur->validate(typetable);
        vector<tree_node*> children = cur->get_children();
        for(auto child : children)
        {
            assert(visited.find(child) == visited.end());
            visited.insert(child);
            q.push(child);
        }
    }
}


//////////////////////////////////////////////////////////////
//
// Euler Walk on classes Implementation
//
//////////////////////////////////////////////////////////////

void program_class::euler_walk(ClassVisitor& visitor, ClassTree& class_tree, 
                                TypeTable& type_table, Environment& env)
{
    // for fast access 
    unordered_map<Symbol, Class_> classes_map;
    classes_to_map(classes, classes_map);

     // must traverse children in euler walk order
     Symbol prev = NULL;
     unordered_set<Symbol> visited;
     for(Symbol cur_class : class_tree) 
     {
        assert(SET_CONTAINS(classes_map, cur_class));
        if(!SET_CONTAINS(visited, cur_class))
        {
            visited.insert(cur_class);
            Class_ class_ = classes_map[cur_class];
            class_->sync_local_env(env);
            visitor.visit(class_, class_tree, type_table, env);
        }
        else 
        {
            // we went up a level (clean_up)
            Class_ prev_class = classes_map[prev];
            prev_class->clean_local_env(env);
        }
        
         prev = cur_class;
     }

     // for consistency remove the root class 
     assert(prev != NULL);
     classes_map[prev]->clean_local_env(env);
}


////////////////////////////
// helpers
///////////////////////////
void classes_to_map(Classes classes, unordered_map<Symbol, Class_>& classes_map)
{
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Class_ class_ = classes->nth(i);
        classes_map[class_->get_name()] = class_;
    }
}


