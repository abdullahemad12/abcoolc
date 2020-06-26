//////////////////////////////////////////////////////////////
//
// Scope and Type checking
//
//////////////////////////////////////////////////////////////
#include <cool-tree.h>
#include <environment.h>
#include <exceptions.h>
#include <class-tree.h>
#include <class-table.h>

void attr_class::scope_check()
{

}

void attr_class::type_check()
{

}

void method_class::scope_check()
{

}

void method_class::type_check()
{

}


//////////////////////////////////////////////////
//
// undefined identifiers check
//
///////////////////////////////////////////////////
Symbol cur_class;
void program_class::undefined_identifier_check()
{
    int n = classes->len();
    for(int i = 0; i < n; i++)
        classes->nth(i)->undefined_identifier_check();
}
void class__class::undefined_identifier_check()
{
    cur_class = name;
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->undefined_identifier_check();
}

void method_class::undefined_identifier_check()
{
    
    int n = formals->len();
    for(int i = 0; i < n; i++)
        formals->nth(i)->undefined_identifier_check();
    
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(return_type) && return_type != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, return_type));
        return_type = idtable.add_string("Object");
    }
    expr->undefined_identifier_check();
}

void attr_class::undefined_identifier_check()
{
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_decl) && type_decl != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_decl));
        type_decl = idtable.add_string("Object");
    }
    init->undefined_identifier_check();
}

void formal_class::undefined_identifier_check()
{
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_decl) && type_decl != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_decl));
        type_decl = idtable.add_string("Object");
    } 
}

void assign_class::undefined_identifier_check()
{   
    expr->undefined_identifier_check();
}

void static_dispatch_class::undefined_identifier_check()
{
    expr->undefined_identifier_check();
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_name) && type_name != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_name));
        type_name = idtable.add_string("Object");
    } 

    int n = actual->len(); 
    for(int i = 0; i < n; i++)
    {
        actual->nth(i)->undefined_identifier_check();
    }
}

void dispatch_class::undefined_identifier_check()
{
    expr->undefined_identifier_check();
    int n = actual->len(); 
    for(int i = 0; i < n; i++)
    {
        actual->nth(i)->undefined_identifier_check();
    }
}

void cond_class::undefined_identifier_check()
{
    pred->undefined_identifier_check();
    then_exp->undefined_identifier_check();
    else_exp->undefined_identifier_check();
}

void loop_class::undefined_identifier_check()
{
    pred->undefined_identifier_check();
    body->undefined_identifier_check();
}

void typcase_class::undefined_identifier_check()
{
   expr->undefined_identifier_check();
   int n = cases->len();
   for(int i = 0; i < n; i++)
        cases->nth(i)->undefined_identifier_check();
}
void branch_class::undefined_identifier_check()
{
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_decl) && type_decl != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_decl));
        type_decl = idtable.add_string("Object");
    }
    expr->undefined_identifier_check();
}

void block_class::undefined_identifier_check()
{
    int n = body->len();
    for(int i = 0; i < n; i++)
    {
        body->nth(i)->undefined_identifier_check();
    }
}

void let_class::undefined_identifier_check()
{
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_decl) && type_decl != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_decl));
        type_decl = idtable.add_string("Object");
    }
    init->undefined_identifier_check();
    body->undefined_identifier_check();
}

void plus_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}

void sub_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}

void mul_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}

void divide_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}

void neg_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
}

void lt_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}

void eq_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
    e2->undefined_identifier_check();
}
void leq_class::undefined_identifier_check()
{

}

void comp_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
}

void int_const_class::undefined_identifier_check()
{

}

void bool_const_class::undefined_identifier_check()
{

}

void string_const_class::undefined_identifier_check()
{

}

void new__class::undefined_identifier_check()
{
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    ClassTable& ct = ClassTable::instance();
    if(!ct.contains(type_name) && type_name != SELF_TYPE)
    {
        sem_err.raise(new UndefinedTypeException(cur_class, this, type_name));
        type_name = idtable.add_string("Object");
    } 
}

void isvoid_class::undefined_identifier_check()
{
    e1->undefined_identifier_check();
}

void no_expr_class::undefined_identifier_check()
{

}

void object_class::undefined_identifier_check()
{

}
