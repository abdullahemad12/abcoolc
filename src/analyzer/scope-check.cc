//////////////////////////////////////////////////////////////
//
// Scope checking
//
//////////////////////////////////////////////////////////////
#include <cool-tree.h>
#include <environment.h>
#include <class-tree.h>
#include <vector>
#include <class-visitor.h>
#include <semant-errors.h>
using namespace std;



/////////////////////////////////////////////////////////////
// Scope Checks
// Semant functions for the program children
// These functions assume that type check has been done on 
// the children of the corresponding node, and that type attribute
// has been set already
//
// @brief: scope checks the tree node
// @param Environment& the environment
// @EFFECTS: raises an error if the identifier is not in the scope
// @MODIFIES: SemantErrorHandler
// @REQUIRES: type check to be done on it's children
// @returns true if the node scope checks 
//////////////////////////////////////////////////////////////


bool assign_class::scope_check(Environment& env)
{
    if(!env.contains_object(name)) 
    {
        UndefinedIdentifierError err(containing_class, this, name);
        RAISE(err);
        return false;
    }
    return true;
}

bool static_dispatch_class::scope_check(Environment& env)
{
   if(!env.contains_method(expr->type, name))
   {
       UndefinedMethodError err(containing_class, this, name);
       RAISE(err);
       return false;
   }
   return true; 
}

bool dispatch_class::scope_check(Environment& env)
{
   if(!env.contains_method(expr->type, name))
   {
       UndefinedMethodError err(containing_class, this, name);
       RAISE(err);
       return false;
   }
   return true; 
}

bool object_class::scope_check(Environment& env)
{
    if(env.contains_object(name))
    {
        UndefinedIdentifierError err(containing_class, this, name);
        RAISE(err);
        return false;
    }
    return true;
}