#include "environment.h"
#include "object-environment.h"
#include "method-environment.h"

Symbol Environment::resolve_type(Symbol type)
{
    Symbol self_type = idtable.add_string("SELF_TYPE");
    if(type == self_type)
    {
        return current_class;
    }
    return type;
}

void Environment::resolve_signature_type(MethodSignature& sign)
{
  sign.ret_type = resolve_type(sign.ret_type);
  for(unsigned int i = 0; i < sign.params.size(); i++)
  {
      sign.params[i] = resolve_type(sign.params[i]);
  }  
}


void Environment::add_local(Symbol name, Symbol type)
{ 
    local_object_env.add(name, type); 
}

void Environment::add_local(Symbol class_name, Symbol name, vector<Symbol> formals, Symbol return_type)
{ 
    local_method_env.add(class_name, name, formals, return_type); 
}
void Environment::add_global(Symbol class_name, Symbol name, vector<Symbol> formals, Symbol return_type)
{ 
    global_method_env.add(class_name, name, formals, return_type); 
}

void Environment::remove_local_method(Symbol class_name, Symbol name) 
{ 
    local_method_env.remove(class_name, name);
}

void Environment::remove_global_method(Symbol class_name, Symbol name) 
{ 
    global_method_env.remove(class_name, name);
}

void Environment::remove_local_object(Symbol name)
{
    local_object_env.remove(name);
}

bool Environment::contains_local_object(Symbol name)
{
    return local_object_env.contains(name);
}
bool Environment::contains_local_method(Symbol class_name, Symbol name)
{
    return local_method_env.contains(class_name, name);
}
bool Environment::contains_global_method(Symbol class_name, Symbol name)
{
    return global_method_env.contains(class_name, name);
}

MethodEnvironment::Signature Environment::lookup_local_method(Symbol class_name, Symbol name)
{
    MethodSignature sign = local_method_env.lookup(class_name, name);
    resolve_signature_type(sign);
    return sign;
}

MethodEnvironment::Signature Environment::lookup_global_method(Symbol class_name, Symbol name)
{
    MethodSignature sign = global_method_env.lookup(class_name, name);
    resolve_signature_type(sign);
    return sign;
}

Symbol Environment::lookup_local_object(Symbol name)
{
    return resolve_type(local_object_env.lookup(name));
}
