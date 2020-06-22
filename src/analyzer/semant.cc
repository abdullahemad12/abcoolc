

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include <exceptions.h>
#include <singleton.h>
#include <class-table.h>
#include <class-tree.h>
#include <cassert>

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

    int err; 
    /*Get singleton data structure*/
    ClassTable& classtable = Singleton<ClassTable>::instance();
    ClassTree& classtree = Singleton<ClassTree>::instance();
    SemantExceptionHandler& semant_error = Singleton<SemantExceptionHandler>::instance();
	
    /*Initialize the the class data structures*/
    try
    {
        classtable.init(classes);
        classtree.init(classes, Object);
    }
    catch(GraphException& e)
    {
        semant_error.report_one(classes, e);
        terminate_on_errors();
    }

    semant_check_classes();
    /* report errors and exit if any */
    err = semant_error.report_all();
    if (err) 
    {
        terminate_on_errors();
    }
}



//////////////////////////////////////////////////////////////
//
// Helpers for the semant methods
//
//////////////////////////////////////////////////////////////
/**
  * Runs the semant function of all the classes in the program in a special 
  * order (namely euler walk order on the inheritance graph). Also tells each class
  * When to add its features to the global and local environments. This should only 
  * be called when all the singleton where initialized as needed 
  */ 
void semant_check_classes()
{
    ClassTree& class_tree = Singleton<ClassTree>::instance();
    ClassTable& class_table = Singleton<ClassTable>::instance();

    // first add all the methods to the global environment
    for(auto& class_entry : class_table)
    {
        Class_ c = class_entry.second;
        c->sync_global_env();
    }

    // these variables detects change in depth and avoids 
    // performing semantic check more than once on a class
    unordered_set<Symbol> visited;
    Symbol prev_class = NULL; 

    // Now do semantic check on the classes
    for(Symbol class_name : class_tree)
    {
        // if visited we went up a level
        if(visited.count(class_name))
        {
            assert(class_table.contains(prev_class));
            Class_ c = class_table[prev_class];
            c->clean_local_env();
        }
        else // we went down a level
        {
            assert(class_table.contains(class_name));
            Class_ cur_class = class_table[class_name];
            cur_class->semant();
            visited.insert(class_name);
        }
    }
}

void terminate_on_errors(void)
{
    cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
}
