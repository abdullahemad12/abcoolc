#include <object-environment.h>
#include <cassert>

void ObjectEnvironment::add(Symbol id, Symbol type) 
{
    if(contains(id)) 
    {
        env[id].push(type);
    }
    else 
    {
        std::stack<Symbol> s;
        s.push(type);
        env[id] = s;
    }
}

void ObjectEnvironment::remove(Symbol id) 
{
    /*a bug if that is not true*/
    assert(contains(id));
    env[id].pop();
    if(env[id].empty()){
        env.erase(id);
    }
}

Symbol ObjectEnvironment::lookup(Symbol id) 
{
    assert(contains(id));
    return env[id].top();

}

bool ObjectEnvironment::contains(Symbol id)
{
    return env.find(id) != env.end();
}