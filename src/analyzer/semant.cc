

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include <exceptions.h>
#include <singleton.h>
#include <class-table.h>
#include <class-tree.h>

extern int semant_debug;
extern char *curr_filename;

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
    catch(const GraphException& e)
    {
        semant_error.report_one(e);
    }
    

    /*Add classes and methods to the envirnment*/
    
    /* report errors and exit if any */
    err = semant_error.report_all();
    if (err) {
	cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
    }
}




