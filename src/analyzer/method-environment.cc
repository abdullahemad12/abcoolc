#include <method-environment.h>
#include <cassert>

void MethodEnvironment::add(Symbol class_name, method_class method)
{
    Signature sig = Signature(method.get_formals(), method.get_return_type());
    if(env.find(class_name) == env.end()){
        std::unordered_map<Symbol, Signature> meths; 
        env[class_name] = meths;
    }
    Symbol meth_name = method.get_name();
    env[class_name][meth_name] = sig;
}


void MethodEnvironment::remove(Symbol class_name, Symbol method_name)
{
    assert(env.find(class_name) != env.end());
    assert(env[class_name].find(method_name) != env[class_name].end());
    env[class_name].erase(method_name);
}

MethodEnvironment::Signature* MethodEnvironment::lookup(Symbol class_name, Symbol method_name)
{

}

