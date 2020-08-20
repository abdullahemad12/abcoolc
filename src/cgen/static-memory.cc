#include "static-memory.h"
#include "cgen_gc.h"

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };

void StaticMemory::gc_declaration(CodeContainer& ccon)
{
    //
    // Generate GC choice constants (pointers to GC functions)
    //
    ccon.global_string_const("_MemMgr_INITIALIZER", gc_init_names[cgen_Memmgr]);
    ccon.global_string_const("_MemMgr_COLLECTOR", gc_collect_names[cgen_Memmgr]);
    ccon.global_int_const("_MemMgr_TEST", (cgen_Memmgr_Test == GC_TEST));

}

StaticMemory::StaticMemory(CodeContainer& ccon)
{
    gc_declaration(ccon);
}

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
