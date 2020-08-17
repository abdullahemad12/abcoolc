#include "static-memory.h"

string StaticMemory::const_label(int i)
{
    assert(int_consts.find(i) != int_consts.end());
    return int_consts[i];    
}
string StaticMemory::const_label(string s)
{
    assert(string_consts.find(s) != string_consts.end());
    return string_consts[s];
}

ObjectPrototype& StaticMemory::lookup_objectprot(Symbol class_name)
{
    assert(obj_prototypes.find(class_name) != obj_prototypes.end());
    return obj_prototypes[class_name];
}

void StaticMemory::add_const(int i)
{
    int_consts[i] = INT_CONST_LABEL(i);   
}

void StaticMemory::add_const(string s)
{
    string_consts[s] = STR_CONST_LABEL(s);
}

void StaticMemory::add_object_prot(Symbol class_name, ObjectPrototype obj_prot)
{
    assert(obj_prototypes.find(class_name) == obj_prototypes.end());
    obj_prototypes[class_name] = obj_prot;
}
