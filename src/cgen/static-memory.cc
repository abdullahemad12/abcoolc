#include <math.h>
#include "basic-symbols.h"
#include "static-memory.h"
#include "cgen_gc.h"

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };

StaticMemory::StaticMemory()
{
    initialize_constants();
    add_const(0);
    add_const("");
}
void StaticMemory::gc_declaration(CodeContainer& ccon)
{
    //
    // Generate GC choice constants (pointers to GC functions)
    //
    ccon.global_word("_MemMgr_INITIALIZER", gc_init_names[cgen_Memmgr]);
    ccon.global_word("_MemMgr_COLLECTOR", gc_collect_names[cgen_Memmgr]);
    ccon.global_word("_MemMgr_TEST", (cgen_Memmgr_Test == GC_TEST));

}

void StaticMemory::write_object_header(CodeContainer& ccon, string label, int tag, int size, string dispatch_ptr)
{
    ccon.word(-1);
    ccon.label(label);
    ccon.word(tag);
    ccon.word(size);
    ccon.word(dispatch_ptr);
}
void StaticMemory::write_int_consts(CodeContainer& ccon)
{
    ObjectPrototype& int_prot = lookup_objectprot(Int);
    for(auto& entry : int_consts)
    {
        write_object_header(ccon, entry.second, int_prot.tag(), INT_OBJ_SIZE, int_prot.methods_table().label());
        ccon.word(entry.first);
    }
}
void StaticMemory::write_string_consts(CodeContainer& ccon)
{
    ObjectPrototype& string_prot = lookup_objectprot(Str);
    for(auto& entry : string_consts)
    {
        float bytes = 4 * (OBJ_HEADER_SIZE + 1) + (entry.first.length() + 1);
        float size = ceil(bytes / 4.0);
        write_object_header(ccon, entry.second, string_prot.tag(), size, string_prot.methods_table().label());
        ccon.word(lookup_label(entry.first.length()));
        ccon.ascii(entry.first);
        ccon.byte(0);
        ccon.align(2);
    }
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
    add_const(s.length());
    string_consts[s] = STR_CONST_LABEL(s);
}

void StaticMemory::add_object_prot(Symbol class_name, ObjectPrototype obj_prot)
{
    assert(obj_prototypes.find(class_name) == obj_prototypes.end());
    obj_prototypes[class_name] = obj_prot;
}



void StaticMemory::write_false_const(CodeContainer& ccon)
{
    ObjectPrototype& bool_prot = lookup_objectprot(Bool);
    write_object_header(ccon, FALSE, bool_prot.tag(), 4, bool_prot.methods_table().label());
    ccon.word(0);
}

void StaticMemory::write_true_const(CodeContainer& ccon)
{
    ObjectPrototype& bool_prot = lookup_objectprot(Bool);
    write_object_header(ccon, TRUE, bool_prot.tag(), 4, bool_prot.methods_table().label());
    ccon.word(1);
}

void StaticMemory::write_out(CodeContainer& ccon)
{
    gc_declaration(ccon);
    write_int_consts(ccon);
    write_string_consts(ccon);
}

string StaticMemory::lookup_label(string str_const)
{
    assert(this->string_consts.find(str_const) != this->string_consts.end());
    return this->string_consts[str_const];
}

string StaticMemory::lookup_label(int int_const)
{
    assert(this->int_consts.find(int_const) != this->int_consts.end());
    return this->int_consts[int_const];
}