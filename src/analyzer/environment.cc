#include "environment.h"
#include "object-environment.h"
#include "method-environment.h"





Environment::Environment()
{  

}
void Environment::add_object(Symbol name, Symbol type)
{ 
    object_env.add(name, type); 
}

void Environment::add_method(Symbol class_, method_class* method)
{ 
    Formals formals = method->get_formals();
    vector<Symbol> params;
    int n = formals->len();
    for(int i = 0; i < n; i++)
    {
        params.push_back(formals->nth(i)->get_type_decl());
    }
    method_env.add(class_, method->get_name(), params, method->get_type()); 
}


void Environment::remove_object(Symbol name) 
{ 
    object_env.remove(name);
}

void Environment::remove_method(Symbol class_name, Symbol name) 
{ 
    method_env.remove(class_name, name);
}

bool Environment::contains_object(Symbol name)
{
    return object_env.contains(name);
}
bool Environment::contains_method(Symbol class_name, Symbol name)
{
    return method_env.contains(class_name, name);
}


MethodSignature Environment::lookup_method(Symbol class_name, Symbol name)
{
    return method_env.lookup(class_name, name);
}


Symbol Environment::lookup_object(Symbol name)
{
    return object_env.lookup(name);
}


void Environment::sync_inherited_methods(Symbol derived, Symbol base)
{
    method_env.copy_methods(base, derived);
}

