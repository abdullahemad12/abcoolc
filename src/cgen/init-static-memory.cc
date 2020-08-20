#include "cool-tree.h"
#include "static-memory.h"
#include "basic-symbols.h"

///////////////////////////////////////////////////////////////
// init_static_memory()
// Code to initialize the Static Memory
// To write out the static memory portion, the following
// need to be gathered first
// 1. All methods and their signatures
// 2. All classes and their object prototypes
// 3. All constants: Ints, Strings
// Important thing about classes is that they are traversed in
// DFS order according to the inheritance graph.
// This is especially helpful when creating method table and 
// object prototype
//////////////////////////////////////////////////////////////

void program_class::assign_classes_tags()
{
    int n = classes->len();
    for(int i = 0; i < n; i++)
        classes->nth(i)->tag = i;
}
void program_class::initialize_static_memory(StaticMemory& s_mem)
{
    assign_classes_tags();
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Class_ object_class = classes->nth(i);
        if(object_class->get_name() == idtable.add_string("object"))
        {
            ObjectPrototype empty_prot;
            s_mem.add_object_prot(NULL, empty_prot); // because object has no parent
            object_class->initialize_static_memory(s_mem);
        }
    }

}

void class__class::initialize_static_memory(StaticMemory& s_mem)
{
    // initialize this class first and its features
    ObjectPrototype& parent_prot = s_mem.lookup_objectprot(parent);
    ObjectPrototype obj_prot(this, features, parent_prot);
    s_mem.add_object_prot(name, obj_prot);
    recurse_init_static_mem(s_mem);
    
    for(Class_ child : children_classes)
        child->initialize_static_memory(s_mem);
}

void method_class::initialize_static_memory(StaticMemory& s_mem)
{
   recurse_init_static_mem(s_mem);
}

void attr_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void formal_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void assign_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void static_dispatch_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void dispatch_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void cond_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void loop_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void typcase_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void branch_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void block_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);  
}

void let_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void plus_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void sub_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void mul_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void divide_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void neg_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem); 
}

void lt_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void eq_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void leq_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void comp_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem); 
}

void int_const_class::initialize_static_memory(StaticMemory& s_mem)
{
    s_mem.add_const(stoi(token->get_string()));
    recurse_init_static_mem(s_mem);
}

void bool_const_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void string_const_class::initialize_static_memory(StaticMemory& s_mem)
{
    s_mem.add_const(token->get_string());
    recurse_init_static_mem(s_mem);
}

void new__class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void isvoid_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem); 
}

void no_expr_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);
}

void object_class::initialize_static_memory(StaticMemory& s_mem)
{
    recurse_init_static_mem(s_mem);   
}

