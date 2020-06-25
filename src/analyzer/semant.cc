

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "utilities.h"
#include <exceptions.h>
#include <class-table.h>
#include <class-tree.h>
#include <cassert>
#include <environment.h>

extern int semant_debug;
extern char *curr_filename;

// prototypes for helpers 
void semant_check_classes();
void terminate_on_errors(void);
Symbol resolve_self_type_c(Symbol type);


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
    ClassTable& classtable = ClassTable::instance();
    ClassTree& classtree = ClassTree::instance();
    SemantExceptionHandler& semant_error = SemantExceptionHandler::instance();
	
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


/////////////////////////////////////////////////////////////
//
// Semant functions for the program children
//
//////////////////////////////////////////////////////////////

/**
  * This method wont sync or clean the local environment unlike the other
  * semant methods. That is because it does not actually know when to sync
  * and when it is appropriate to clean. Note also self is bound to this 
  * class when synching. 
  */
void class__class::semant()
{
    // analyze the children
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->semant();
}

void method_class::semant()
{
    // get global data structures
    ClassTable& classtable = ClassTable::instance();
    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();
    Environment& env = Environment::instance();

    // add formals to ObjectEnvironment
    sync_local_environment();

    // semant check formals
    int n = formals->len();
    for(int i = 0; i < n; i++)
        formals->nth(i)->semant();

    expr->semant();

    // type check 
    type_check(return_type, expr->type);

    // remove formals from object Environment
    clean_local_environment();
}

void attr_class::semant()
{
    init->semant();
    type_check(type_decl, init->type);   
}

void formal_class::semant()
{
    if(type_decl == SELF_TYPE)
    {
        SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
        Environment& env = Environment::instance();
        sem_err.raise(new SelfTypeAsArgumentException(env.current_class, this));
        return;
    }

    // we only need to know if the type 
    // references a defined method
    type_check(type_decl, type_decl);
}

void assign_class::semant()
{   
    expr->semant();
    if(scope_check())
    {
        Environment& env = Environment::instance();
        Symbol type = env.lookup_local_object(name);
        type_check(type, expr->type);
    }
}

void static_dispatch_class::semant()
{

}

void dispatch_class::semant()
{

}

void cond_class::semant()
{

}

void loop_class::semant()
{

}

void typcase_class::semant()
{

}

void block_class::semant()
{

}

void let_class::semant()
{

}

void plus_class::semant()
{

}

void sub_class::semant()
{

}

void mul_class::semant()
{

}

void divide_class::semant()
{

}

void neg_class::semant()
{

}

void lt_class::semant()
{

}

void eq_class::semant()
{

}
void leq_class::semant()
{

}

void comp_class::semant()
{

}

void int_const_class::semant()
{

}

void bool_const_class::semant()
{

}

void string_const_class::semant()
{

}

void new__class::semant()
{

}

void isvoid_class::semant()
{

}

void no_expr_class::semant()
{

}

void object_class::semant()
{

}



//////////////////////////////////////////////////////////////
//
// Scope and Type checking
//
//////////////////////////////////////////////////////////////

bool assign_class::scope_check()
{
    Environment& env = Environment::instance();
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    if(!env.contains_local_object(name))
    {
        sem_err.raise(new UndefinedAttributeException(env.current_class, this, name));
        return false;
    }
    return true;
}
bool tree_node::type_check(Symbol given_type, Symbol inferred_type)
{
    // this is common with declaration without intialization
    if(inferred_type == No_type)
    {
        return true;
    }

    Environment& env = Environment::instance();
    ClassTable& class_table = ClassTable::instance();
    ClassTree& class_tree = ClassTree::instance();
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    given_type = resolve_self_type_c(given_type);
    inferred_type = resolve_self_type_c(inferred_type);
    if(!class_table.contains(given_type))
    {
        sem_err.raise(new UndefinedTypeException(env.current_class, this, given_type));
        return false;
    }
    if(!class_tree.is_derived(inferred_type, given_type))
    {
        sem_err.raise(new TypeMismathcException(env.current_class, this,  inferred_type, given_type));
        return false;
    }
    return true;
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
    ClassTree& class_tree = ClassTree::instance();
    ClassTable& class_table = ClassTable::instance();

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
            
            // this will take care features defined multiple times 
            cur_class->sync_local_env();
            
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


Symbol resolve_self_type_c(Symbol type)
{
    Environment& env = Environment::instance();
    if(type == SELF_TYPE)
    {
        return env.current_class;
    }
    return type;
}


