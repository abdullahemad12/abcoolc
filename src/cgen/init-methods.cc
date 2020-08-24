///////////////////////////////////////////////////////////
// create_init_methods
// 
// Code for generating the methods that is responsible
// for initializing the new objects
//////////////////////////////////////////////////////////
#include <string>
#include <algorithm>
#include "activation-record.h"
#include "cool-tree.h"
#include "code-container.h"
#include "memory-manager.h"
#include "emit.h"


using namespace std;

void program_class::create_init_methods(CodeContainer& ccon, MemoryManager& mem_man)
{
    int n = classes->len();
    for(int i = 0; i < n; i++)
        classes->nth(i)->create_init_method(ccon, mem_man);
}

void class__class::create_init_method(CodeContainer& ccon, MemoryManager& mem_man)
{
    int ntmps;
    string parent_init;
    string init_name;

    StaticMemory& stat_mem =  mem_man.static_memory();
    ObjectPrototype& prot = stat_mem.lookup_objectprot(name);
    vector<attr_class*> attrs = prot.self_attributes();
    parent_init = string(parent->get_string()) + CLASSINIT_SUFFIX;
    init_name = string(name->get_string()) + CLASSINIT_SUFFIX;
    ntmps = maxmintmp(attrs);

    ccon.label(init_name);

    ActivationRecord ar(nil_Formals(), ntmps);
    mem_man.enter_scope(ccon, this, ar);

    ccon.jal(parent_init);

    for(auto& attr : attrs)
        attr->cgen(ccon, mem_man);

    mem_man.exit_scope(ccon);
}



int class__class::maxmintmp(vector<attr_class*> attrs)
{
    int ans = 0;
    for(auto attr : attrs)
        ans = max(ans, attr->mintmps());
    return ans;
}