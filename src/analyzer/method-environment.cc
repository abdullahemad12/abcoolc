#include <method-environment.h>
#include <unordered_set>
#include <cassert>


using namespace std;

void MethodEnvironment::add(Symbol class_name, Symbol name, vector<Symbol> params, Symbol return_type)
{
    if(env.find(class_name) == env.end()){
        std::unordered_map<Symbol, MethodSignature*> meths; 
        env[class_name] = meths;
    }
    if(env[class_name].find(name) == env[class_name].end())
    {
        MethodSignature* sig = new MethodSignature(name, params, return_type);
        env[class_name][name] = sig;
    }
    ++env[class_name][name]->counter;
}


void MethodEnvironment::remove(Symbol class_name, Symbol method_name)
{
    assert(env.find(class_name) != env.end());
    assert(env[class_name].find(method_name) != env[class_name].end());
    --env[class_name][method_name]->counter;
    if(env[class_name][method_name]->counter == 0)
        env[class_name].erase(method_name);
}

MethodEnvironment::Signature MethodEnvironment::lookup(Symbol class_name, Symbol method_name)
{
    /*must check that the class is defined before calling this method*/
    assert(env.find(class_name) != env.end());
    assert(env[class_name].find(method_name) != env[class_name].end());
    std::unordered_map<Symbol, Signature*> map = env[class_name];
    return *map[method_name];
}

void MethodEnvironment::copy_methods(Symbol source_class, Symbol destination_class)
{
    assert(env.find(source_class) != env.end());
    std::unordered_map<Symbol, Signature*> map = env[source_class];
    if(env.find(destination_class) == env.end())
        env[destination_class] = map;
    else
        env[destination_class].insert(map.begin(), map.end());   
}

bool MethodEnvironment::contains(Symbol class_name, Symbol method_name)
{
    return (env.find(class_name) != env.end()) && (env[class_name].find(method_name) != env[class_name].end());
}

MethodEnvironment::~MethodEnvironment()
{
    unordered_set<MethodSignature*> signatures;
    for(auto& class_map : env)
        for(auto& entry : class_map.second)
            signatures.insert(entry.second);
    
    for(auto& signature : signatures)
        delete signature;

}


/***************
 *  Signature  *
 ***************/
MethodEnvironment::Signature::Signature(Symbol name, vector<Symbol> params , Symbol ret_type)
                            : params(params), ret_type(ret_type), counter(0)
{

}

vector<Symbol> MethodEnvironment::Signature::get_param_types()
{
    return params;
}

Symbol MethodEnvironment::Signature::get_return_type()
{
    return ret_type;
}

bool operator==(MethodSignature& sign, method_class& meth)
{
    vector<Symbol> params = sign.get_param_types();
    Formals formals = meth.get_formals();
    if((int)params.size() != formals->len())
        return false;
    for(unsigned int i = 0; i < params.size(); i++)
        if(params[i] != formals->nth(i)->get_type_decl())
            return false;
    return true;
}
bool operator!=(MethodSignature& sign, method_class& meth)
{
    vector<Symbol> params = sign.get_param_types();
    Formals formals = meth.get_formals();
    if((int)params.size() != formals->len())
        return true;
    for(unsigned int i = 0; i < params.size(); i++)
        if(params[i] != formals->nth(i)->get_type_decl())
            return true;
    return false;
}
