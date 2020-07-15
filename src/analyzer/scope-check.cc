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
using namespace std;



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


void program_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    ScopeClassVisitor visitor;
    euler_walk(visitor, class_tree, type_table, env); 
}

void class__class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->scope_check(class_tree, type_table, env);
}

void method_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    sync_environment(env);
    expr->scope_check(class_tree, type_table, env);
    clean_environment(env);
}

void attr_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    init->scope_check(class_tree, type_table, env);
}

void formal_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void assign_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void static_dispatch_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void dispatch_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void cond_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void loop_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void typcase_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void branch_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void block_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void let_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void plus_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void sub_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void mul_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void divide_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void neg_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void lt_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void eq_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void leq_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void comp_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void int_const_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void bool_const_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void string_const_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void new__class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void isvoid_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void no_expr_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void object_class::scope_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}


