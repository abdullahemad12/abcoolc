#include <method-environment.h>
#include <cassert>
#include <exceptions.h>


using namespace std;

void MethodEnvironment::add(Symbol class_name, Symbol name, vector<Symbol> params, Symbol return_type)
{
    MethodSignature* sig = new MethodSignature(name, params, return_type);
    if(env.find(class_name) == env.end()){
        std::unordered_map<Symbol, MethodSignature*> meths; 
        env[class_name] = meths;
    }
    env[class_name][name] = sig;
}


void MethodEnvironment::remove(Symbol class_name, Symbol method_name)
{
    assert(env.find(class_name) != env.end());
    assert(env[class_name].find(method_name) != env[class_name].end());
    env[class_name].erase(method_name);
}

MethodEnvironment::Signature& MethodEnvironment::lookup(Symbol class_name, Symbol method_name)
{
    /*must check that the class is defined before calling this method*/
    assert(env.find(class_name) != env.end());
    assert(env[class_name].find(method_name) != env[class_name].end());
    std::unordered_map<Symbol, Signature*> map = env[class_name];
    return *map[method_name];
}

bool MethodEnvironment::contains(Symbol class_name, Symbol method_name)
{
    assert(env.find(class_name) != env.end());
    return env[class_name].find(method_name) != env[class_name].end();
}

MethodEnvironment::~MethodEnvironment()
{
    for(auto& class_map : env)
    {
        for(auto& entry : class_map.second)
        {
            delete entry.second;
        }
    }
}


/***************
 *  Signature  *
 ***************/
MethodEnvironment::Signature::Signature(Symbol name, vector<Symbol> params , Symbol ret_type){
    this->params = params;
    this->ret_type = ret_type;
}

vector<Symbol> MethodEnvironment::Signature::get_param_types()
{
    return params;
}

Symbol MethodEnvironment::Signature::get_return_type()
{
    return ret_type;
}
