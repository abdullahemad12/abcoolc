

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
    initialize_constants();
}


/////////////////////////////////////////////////////////////
// Type and Scope Checks
// Semant functions for the program children
// General Algorithm 
// 1) Add state as needed to the environment
// 2) call semant on all the children 
// 3) scope check
// 4) type check if scope checks sucessfully
// 5) if any fails set the type to Object
// 6) Remove the state from the environment
// 
// steps (1) and (6) are omitted at the class node and done 
// at the program node instead
//////////////////////////////////////////////////////////////

void class__class::scope_check(Environment& env)
{
   
}

void class__class::type_check(Environment& env)
{
   
}

void method_class::scope_check(Environment& env)
{
    
}

void method_class::type_check(Environment& env)
{
    
}

void attr_class::scope_check(Environment& env)
{
    
}

void attr_class::type_check(Environment& env)
{

}

void formal_class::scope_check(Environment& env)
{
   
}

void formal_class::type_check(Environment& env)
{
   
}

void assign_class::scope_check(Environment& env)
{   
}
void assign_class::type_check(Environment& env)
{   

}

void static_dispatch_class::scope_check(Environment& env)
{
    
}
void static_dispatch_class::type_check(Environment& env)
{

}

void dispatch_class::scope_check(Environment& env)
{
    
}

void dispatch_class::type_check(Environment& env)
{
    
}

void cond_class::scope_check(Environment& env)
{
    
}
void cond_class::type_check(Environment& env)
{
    
}


void loop_class::scope_check(Environment& env)
{
    
}

void loop_class::type_check(Environment& env)
{
    
}

void typcase_class::scope_check(Environment& env)
{
   
}
void typcase_class::type_check(Environment& env)
{
   
}

void branch_class::scope_check(Environment& env)
{
    
}


void branch_class::type_check(Environment& env)
{
    
}

void block_class::scope_check(Environment& env)
{
    
}

void block_class::type_check(Environment& env)
{

}

void let_class::scope_check(Environment& env)
{
    
}

void let_class::type_check(Environment& env)
{
    
}

void plus_class::scope_check(Environment& env)
{

}

void plus_class::type_check(Environment& env)
{

}

void sub_class::scope_check(Environment& env)
{

}

void sub_class::type_check(Environment& env)
{

}

void mul_class::scope_check(Environment& env)
{

}

void mul_class::type_check(Environment& env)
{

}

void divide_class::scope_check(Environment& env)
{

}

void divide_class::type_check(Environment& env)
{

}

void neg_class::scope_check(Environment& env)
{
}

void neg_class::type_check(Environment& env)
{
}

void lt_class::scope_check(Environment& env)
{
   
}

void lt_class::type_check(Environment& env)
{
   
}

void eq_class::scope_check(Environment& env)
{

}

void eq_class::type_check(Environment& env)
{

}
void leq_class::scope_check(Environment& env)
{

}

void leq_class::type_check(Environment& env)
{

}

void comp_class::scope_check(Environment& env)
{

}

void comp_class::type_check(Environment& env)
{

}

void int_const_class::scope_check(Environment& env)
{

}

void int_const_class::type_check(Environment& env)
{

}

void bool_const_class::scope_check(Environment& env)
{

}

void bool_const_class::type_check(Environment& env)
{

}

void string_const_class::scope_check(Environment& env)
{

}


void string_const_class::type_check(Environment& env)
{

}

void new__class::scope_check(Environment& env)
{
    
}

void new__class::type_check(Environment& env)
{
    
}


void isvoid_class::scope_check(Environment& env)
{

}
void isvoid_class::type_check(Environment& env)
{
    
}

void no_expr_class::scope_check(Environment& env)
{

}

void no_expr_class::type_check(Environment& env)
{

}

void object_class::scope_check(Environment& env)
{

}

void object_class::type_check(Environment& env)
{

}



//////////////////////////////////////////////////////////////
//
// Helpers for the semant methods
//
//////////////////////////////////////////////////////////////




