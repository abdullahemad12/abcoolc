//////////////////////////////////////////////////////////////
//
// Type checking
//
//////////////////////////////////////////////////////////////
#include <cool-tree.h>
#include <environment.h>
#include <class-tree.h>
#include <class-visitor.h>
#include <type-table.h>
#include <semant-errors.h>


// prototypes
Symbol arithmetic_type_check(tree_node* node, Class_ containing_class, Expression_class* e1, Expression_class* e2);
Symbol compare_type_check(tree_node* node, Class_ containing_class, Expression_class* e1, Expression_class* e2);


/////////////////////////////////////////////////////////////
// Type and Scope Checks
// Semant functions for the program children
// General Algorithm 
// 1) Add state as needed to the environment
// 2) call type_check on all the children 
// 3) scope check
// 4) type check if scope checks sucessfully
// 5) if any fails set the type to No_type
// 6) Remove the state from the environment
// 
// steps (1) and (6) are omitted at the class node and done 
// at the program node instead
// Refer to the manual for type checking rules
//////////////////////////////////////////////////////////////

void tree_node::type_check_children(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    auto children = get_children();
    for(auto child : children)
        child->type_check(class_tree, type_table, env);
}
void program_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    initialize_constants();
    TypeClassVisitor visitor;
    class_tree.visit_all(visitor, type_table, env);
}

void class__class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    // Due to the nature of the algorithm,
    // the environment is updated and cleaned in the program node
    type_check_children(class_tree, type_table, env);
}

void method_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    TypeMismathcError* err;

    sync_environment(env);
    type_check_children(class_tree, type_table, env);
    clean_environment(env);

    if(!class_tree.is_derived(env.current_class, expr->type, return_type))
    {
        err = new TypeMismathcError(containing_class, this, expr->type, return_type);
        RAISE(err);
    }
}

void attr_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    TypeMismathcError* err;
    env.remove_object(name);
    type_check_children(class_tree, type_table, env);
    env.add_object(name, type_decl);
    
    if(!class_tree.is_derived(env.current_class, init->type, type_decl))
    {
        err = new TypeMismathcError(containing_class, this, init->type, type_decl);
        RAISE(err);
    }
}

void formal_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    
}

void assign_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    TypeMismathcError* err;
    
    type_check_children(class_tree, type_table, env);

    type = No_type;
    if(!scope_check(env))
        return;

    Symbol T0 = env.lookup_object(name);
    if(class_tree.is_derived(env.current_class, expr->type, T0))
    {
        type = T0;
    }
    else 
    {
        err = new TypeMismathcError(containing_class, this, expr->type, T0);
        RAISE(err);
    }
}

void static_dispatch_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

    InheritanceMismatchError* err;
    type_check_children(class_tree, type_table, env);
    
    type = No_type;
    if(!scope_check(env))
        return;
    
    if(!class_tree.is_derived(env.current_class, expr->type, type_name))
    {
        err = new InheritanceMismatchError(containing_class, this, type_name, expr->type);
        RAISE(err);
        return;
    }

    MethodSignature sign = env.lookup_method(type_name, name);
    if(!type_check_arguments(sign.get_param_types(), class_tree))
        return;
    
    if(sign.get_return_type() == SELF_TYPE)
        type = expr->type;
    else
        type = sign.get_return_type();

}

void dispatch_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    
    type = No_type;
    if(!scope_check(env))
        return;
    
    MethodSignature sign = env.lookup_method(expr->type, name);
    if(!type_check_arguments(sign.get_param_types(), class_tree))
        return;

    if(sign.get_return_type() == SELF_TYPE)
        type = expr->type;
    else
        type =  sign.get_return_type();
    
}

void cond_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    ConditionTypeError* err;
    type_check_children(class_tree, type_table, env);
    
    type = No_type;
    if(pred->type != Bool)
    {
        err = new ConditionTypeError(containing_class, this, pred->type);
        RAISE(err);
        return;
    }

    type = class_tree.lub(env.current_class, then_exp->type, else_exp->type);
}

void loop_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    ConditionTypeError* err;
    type_check_children(class_tree, type_table, env);

    type = No_type;

    if(pred->type != Bool)
    {
        err = new ConditionTypeError(containing_class, this, pred->type);
        RAISE(err);
        return;        
    }
    type = Object;
}

void typcase_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = No_type;

    int n = cases->len();
    for(int i = 0; i < n; i++)
        type = class_tree.lub(env.current_class, type, cases->nth(i)->type);
}

void branch_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    env.add_object(name, type_decl);
    type_check_children(class_tree, type_table, env);
    env.remove_object(name);
    type = expr->type;
}

void block_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = body->nth(body->len() - 1)->type;
}

void let_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    TypeMismathcError* err;
    init->type_check(class_tree, type_table, env);
    
    type = No_type;

    // type check body
    env.add_object(identifier, type_decl);
    body->type_check(class_tree, type_table, env);
    env.remove_object(identifier);

    if(!class_tree.is_derived(env.current_class, init->type, type_decl))
    {
        cout << "here";
        err = new TypeMismathcError(containing_class, this, init->type, type_decl);
        RAISE(err);
        return;
    }
    type = body->type;
}

void plus_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = arithmetic_type_check(this, containing_class, e1, e2);
}

void sub_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = arithmetic_type_check(this, containing_class, e1, e2);
}

void mul_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = arithmetic_type_check(this, containing_class, e1, e2);
}

void divide_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = arithmetic_type_check(this, containing_class, e1, e2);
}

void neg_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = No_type;
    TypeMismathcError* err;
    type_check_children(class_tree, type_table, env);
    if(e1->type != Int)
    {
        err = new TypeMismathcError(containing_class, this, e1->type, Int);
        RAISE(err);
        return;
    }
    type = Int;
}

void lt_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = compare_type_check(this, containing_class, e1, e2); 
}

void eq_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    SemantError* err;

    type_check_children(class_tree, type_table, env);
    type = No_type;
    if(type_table.is_basic_type(e1->type) || type_table.is_basic_type(e2->type))
    {
        if(e1->type != e2->type)
        {
            err = new NonBasicTypeError(containing_class, this, e1->type);
            RAISE(err);
            return;
        }
    }
    type = Bool;
}

void leq_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = compare_type_check(this, containing_class, e1, e2);
}

void comp_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = No_type;
    TypeMismathcError* err;
    type_check_children(class_tree, type_table, env);
    if(e1->type != Bool)
    {
        err = new TypeMismathcError(containing_class, this, e1->type, Bool);
        RAISE(err);
        return;
    }
    type = Bool;
}

void int_const_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = Int;
}

void bool_const_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = Bool;
}

void string_const_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = Str;
}

void new__class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = No_type;
    if(!faulty)
        type = type_name;
}

void isvoid_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type_check_children(class_tree, type_table, env);
    type = Bool;
}

void no_expr_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = No_type;
}

void object_class::type_check(ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    type = No_type;
    if(!scope_check(env))
        return;

    type = env.lookup_object(name);
}






////////////////////////////////////////////
//
// Helper functions
//
////////////////////////////////////////////
bool static_dispatch_class::type_check_arguments(vector<Symbol> param_types, ClassTree& class_tree)
{
    SemantError* err;
    unsigned int n = actual->len();
    if(param_types.size() != n)
    {
        err = new UnexpectedNumberOfArgsError(containing_class, this, param_types.size(), n);
        RAISE(err);
        return false;
    }

    bool type_checks = true;

    for(unsigned int i = 0; i < n; i++)
    {
        Symbol Ti = actual->nth(i)->type;
        if(!class_tree.is_derived(containing_class->get_name(), Ti, param_types[i]))
        {
            type_checks = false;
            err = new TypeMismathcError(containing_class, this, Ti, param_types[i]);
            RAISE(err);
        }
    }

    return type_checks;
}

bool dispatch_class::type_check_arguments(vector<Symbol> param_types, ClassTree& class_tree)
{
    SemantError* err;
    unsigned int n = actual->len();
    if(param_types.size() != n)
    {
        err = new UnexpectedNumberOfArgsError(containing_class, this, param_types.size(), n);
        RAISE(err);
        return false;
    }

    bool type_checks = true;

    for(unsigned int i = 0; i < n; i++)
    {
        Symbol Ti = actual->nth(i)->type;
        if(!class_tree.is_derived(containing_class->get_name(), Ti, param_types[i]))
        {
            type_checks = false;
            err = new TypeMismathcError(containing_class, this, Ti, param_types[i]);
            RAISE(err);
        }
    }

    return type_checks;
}


Symbol arithmetic_type_check(tree_node* node, Class_ containing_class, Expression_class* e1, Expression_class* e2)
{
    SemantError* err;
    if(e1->type != Int)
    {
        err = new TypeMismathcError(containing_class, node, e1->type, Int);
        RAISE(err);
        return No_type;
    }
    if(e2->type != Int)
    {
        err = new TypeMismathcError(containing_class, node, e2->type, Int);
        RAISE(err);
        return No_type; 
    }
    return Int;
}

Symbol compare_type_check(tree_node* node, Class_ containing_class, Expression_class* e1, Expression_class* e2)
{
    SemantError* err;
    if(e1->type != Int)
    {
        err = new TypeMismathcError(containing_class, node, e1->type, Int);
        RAISE(err);
        return No_type;
    }
    if(e2->type != Int)
    {
        err = new TypeMismathcError(containing_class, node, e2->type, Int);
        RAISE(err);
        return No_type; 
    }
    return Bool;
}
