/////////////////////////////////////////////////////////////////////////
// This class contains functions that adds and remove a 
// collection of objects and methods to and from the environment
// It is split into their own methods for the following reasons
// 1) It is not possible to check duplication when looking for one thing
//    at a time; espically, when it is possible for the environment to
//    have duplicates due to shadowing and overriding.
// 2) The objects and methods being synched must be in the environment
//    before doing any semantic checks because it is legal to reference 
//    a feature before it is defined
//////////////////////////////////////////////////////////////////////////

#include "cool-tree.h"
#include <environment.h>
#include <symtab.h>
#include <unordered_set>

#define CONTAINS(set, elem) ((set.find(elem)) != (set.end()))

using namespace std;

// helpers prototypes
vector<Symbol> extract_formals_type(Formals formals);


////////////////////////////////////////////////////////////////
// if a global synching was to occur the name of the class will 
// be the name of the current class that is synching its features
// Otherwise, methods are place under class symbol "SELF_TYPE"
// indicating that it is a local method. Note that a local method
// need not be defined in the same class. It can also be defined 
// in a parent class
/////////////////////////////////////////////////////////////////

void method_class::add_to_env(Symbol class_name, Environment& env)
{
    if(!duplicate)
        env.add_method(class_name, this);
}

void attr_class::add_to_env(Symbol class_name, Environment& env)
{
    if(!duplicate)
        env.add_object(name, type_decl);
}

void formal_class::add_to_env(Environment& env)
{
    if(!duplicate)
        env.add_object(name, type_decl);
}

///////////////////////////////////////////////////////////////////////
// Cleaning only happen on local attributes. Global Attributes are never 
// removed. Thus, we remove the methods under the type "SELF_TYPE"
/////////////////////////////////////////////////////////////////////////

void method_class::remove_from_env(Environment& env)
{
    if(!duplicate)
        env.remove_method(idtable.add_string("SELF_TYPE"), name);
}

void attr_class::remove_from_env(Environment& env)
{
    if(!duplicate)
        env.remove_object(name);
}

void formal_class::remove_from_env(Environment& env)
{
    if(!duplicate)
        env.remove_object(name);
}



/////////////////////////////////////////
//
//      Method Environment interaction
//
////////////////////////////////////////
void method_class::sync_environment(Environment& env)
{
    int n = formals->len();
    for(int i = 0; i  < n; i++)
        formals->nth(i)->add_to_env(env);
}

void method_class::clean_environment(Environment& env)
{
    int n = formals->len();
    for(int i = 0; i < n; i++)
        formals->nth(i)->remove_from_env(env);
}
/////////////////////////////////////////
//
// Class-Environment interactions
//
/////////////////////////////////////////


/* 
 * this is preprocessing pass that adds features to the global environment
 * no need for error checking
 */ 
void class__class::sync_global_env(Environment& env)
{
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->add_to_env(name, env);
    clean_local_env(env); /*clean features that might have been added by mistake*/
}

/*
 * this is called on the second pass. Error checking is needed in here
 * for detecting malformed feature definitions. Error are passed to the 
 * error handler accordingly without interrupting execution
 */ 
void class__class::sync_local_env(Environment& env)
{
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->add_to_env(idtable.add_string("SELF_TYPE"), env); 
}

/*
 * this is typically done after this class and all its children
 * has been visited, At this point we dont need its features anymore
 */ 
void class__class::clean_local_env(Environment& env)
{
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->remove_from_env(env);
}
