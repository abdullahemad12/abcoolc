#include <math.h>
#include <string>
#include "basic-symbols.h"
#include "static-memory.h"
#include "cgen_gc.h"
#include "emit.h"


using namespace std;

static string escape_string(string str);
static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };


////////////////////////////////////////////////
// StaticMemory API
//
// Functions that are used by other parts of the 
// Compilers to generate the static memory parts 
// of the program and access it
////////////////////////////////////////////////

StaticMemory::StaticMemory()
{
    SystemObjectPrototype* nil_obj_prot = new SystemObjectPrototype();
    initialize_constants();
    int_consts[0] = ZERO_INT;
    string_consts[""] = EMPTY_STRING;
    construct_prototypes[NULL] = nil_obj_prot;
}

string StaticMemory::true_label() { return TRUE; }
string StaticMemory::false_lable() { return FALSE; }

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
    return *obj_prototypes[class_name];
}

void StaticMemory::add_const(int i)
{
    if(int_consts.find(i) == int_consts.end())
        int_consts[i] = INT_CONST_LABEL(int_ctr++);   
}

void StaticMemory::add_const(string s)
{
    add_const(s.length());
    if(string_consts.find(s) == string_consts.end())
        string_consts[s] = STR_CONST_LABEL(str_ctr++);
}
void StaticMemory::cgen(CodeContainer& ccon)
{
    cgen_global_declarations(ccon);
    cgen_gc_declarations(ccon);
    cgen_false_const(ccon);
    cgen_true_const(ccon);
    cgen_int_consts(ccon);
    cgen_string_consts(ccon);
    cgen_class_table(ccon);
    cgen_ancestors_table_ptrs(ccon);
    cgen_object_prototypes(ccon);
    cgen_global_text(ccon);
    install_system_prototypes();
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

void StaticMemory::install_class(Class_ class_)
{
    assert(construct_prototypes.find(class_->get_name()) == construct_prototypes.end());
    Symbol parent = class_->get_parent();
    Symbol name = class_->get_name();

    ObjectPrototype* parent_prot = construct_prototypes[parent]; 
    ObjectPrototype* obj_prot = new ObjectPrototype(class_, tag_ctr++, *parent_prot);

    obj_prototypes[name] = obj_prot;
    construct_prototypes[name] = obj_prot;
}



////////////////////////////////////////////////////////////
// StaticMemory Helpers
//
// Helper functions for static memory public functions 
// Mostly for the write_out function
////////////////////////////////////////////////////////////

void StaticMemory::cgen_false_const(CodeContainer& ccon)
{
    ObjectPrototype& bool_prot = lookup_objectprot(Bool);
    cgen_object_header(ccon, FALSE, bool_prot.tag(), 4, bool_prot.methods_table().label());
    ccon.word(0);
}

void StaticMemory::cgen_true_const(CodeContainer& ccon)
{
    ObjectPrototype& bool_prot = lookup_objectprot(Bool);
    cgen_object_header(ccon, TRUE, bool_prot.tag(), 4, bool_prot.methods_table().label());
    ccon.word(1);
}

void StaticMemory::cgen_global_declarations(CodeContainer& ccon)
{
    ObjectPrototype& main    = lookup_objectprot(Main);
    ObjectPrototype& str  = lookup_objectprot(Str);
    ObjectPrototype& integer = lookup_objectprot(Int);
    ObjectPrototype& boolc   = lookup_objectprot(Bool);

    // start
    ccon.data();
    ccon.align(2);
    
    // Conventional labels
    ccon.global(CLASSNAMETAB);
    ccon.global(main.label());
    ccon.global(integer.label());
    ccon.global(str.label());
    ccon.global(FALSE);
    ccon.global(TRUE);

    // global tags
    ccon.global(INTTAG);
    ccon.global(BOOLTAG);
    ccon.global(STRINGTAG);

    // tags
    ccon.label(INTTAG);
    ccon.word(integer.tag());
    ccon.label(BOOLTAG);
    ccon.word(boolc.tag());
    ccon.label(STRINGTAG);
    ccon.word(str.tag());
}

void StaticMemory::cgen_object_prototypes(CodeContainer& ccon)
{
    install_system_prototypes();
    for(auto prot_pair : obj_prototypes)
        prot_pair.second->cgen(ccon, *this);
    uninstall_system_prototypes();
}

void StaticMemory::cgen_class_table(CodeContainer& ccon)
{
    ccon.label(CLASSNAMETAB);
    
    // sort them
    ObjectPrototype* ordered_protos = new ObjectPrototype[obj_prototypes.size()];
    for(auto prot : obj_prototypes)
        ordered_protos[prot.second->tag()] = *prot.second;
    
    for(unsigned int i = 0; i < obj_prototypes.size(); i++)
        ccon.word(lookup_label(ordered_protos[i].name()));

    delete[] ordered_protos;
}

void StaticMemory::cgen_global_word_declaration(CodeContainer& ccon, string label, string val)
{
    ccon.global(label);
    ccon.label(label);
    ccon.word(val);
}
void StaticMemory::cgen_gc_declarations(CodeContainer& ccon)
{
    //
    // Generate GC choice constants (pointers to GC functions)
    //
    cgen_global_word_declaration(ccon, "_MemMgr_INITIALIZER", gc_init_names[cgen_Memmgr]);
    cgen_global_word_declaration(ccon, "_MemMgr_COLLECTOR", gc_collect_names[cgen_Memmgr]);
    cgen_global_word_declaration(ccon, "_MemMgr_TEST", to_string((cgen_Memmgr_Test == GC_TEST)));

}

void StaticMemory::cgen_object_header(CodeContainer& ccon, string label, int tag, int size, string dispatch_ptr)
{
    ccon.word(-1);
    ccon.label(label);
    ccon.word(tag);
    ccon.word(size);
    ccon.word(dispatch_ptr);
}
void StaticMemory::cgen_int_consts(CodeContainer& ccon)
{
    ObjectPrototype& int_prot = lookup_objectprot(Int);
    for(auto& entry : int_consts)
    {
        cgen_object_header(ccon, entry.second, int_prot.tag(), INT_OBJ_SIZE, int_prot.methods_table().label());
        ccon.word(entry.first);
    }
}
void StaticMemory::cgen_string_consts(CodeContainer& ccon)
{
    ObjectPrototype& string_prot = lookup_objectprot(Str);
    for(auto& entry : string_consts)
    {
        float bytes = 4 * (OBJ_HEADER_SIZE + 1) + (entry.first.length() + 1);
        float size = ceil(bytes / 4.0);
        cgen_object_header(ccon, entry.second, string_prot.tag(), size, string_prot.methods_table().label());
        ccon.word(lookup_label(entry.first.length()));
        ccon.ascii(escape_string(entry.first));
        ccon.byte(0);
        ccon.align(2);
    }
}


void StaticMemory::install_system_prototypes()
{
    for(Symbol sym : system_symbols)
        obj_prototypes[sym] = new SystemObjectPrototype();
}

void StaticMemory::uninstall_system_prototypes()
{
    for(Symbol sym : system_symbols)
    {
        ObjectPrototype* prot = obj_prototypes[sym];
        obj_prototypes.erase(sym);
        delete prot;
    }
}

void StaticMemory::cgen_global_text(CodeContainer& ccon)
{
    ccon.global(HEAP_START);
    ccon.label(HEAP_START);
    ccon.word(0);
    ccon.text();
    ccon.global(string(MAINNAME) + CLASSINIT_SUFFIX);
    ccon.global(string(INTNAME) + CLASSINIT_SUFFIX);
    ccon.global(string(STRINGNAME) + CLASSINIT_SUFFIX);
    ccon.global(string(BOOLNAME) + CLASSINIT_SUFFIX);
    ccon.global(string(MAINNAME) + METHOD_SEP + MAINMETHOD);
}

void StaticMemory::cgen_ancestors_table_ptrs(CodeContainer& ccon)
{

    vector<string> labels(obj_prototypes.size());
    for(auto prot : obj_prototypes)
        labels[prot.second->tag()] = prot.second->ancestors_table().label();

    ccon.label(ANCESTORS_TAB_PTR);
    for(auto label : labels)
        ccon.word(label);
}


static string escape_char(char c)
{
    string s(1, c);
    switch(c)
    {
        case '\n': return "\\n";
        case '\b': return "\\b";
        case '\f': return "\\f";
        case '\t': return "\\t";
        case '\0': return "\\0";
        default  : return s; 
    }
}
static string escape_string(string str)
{
    string ret;
    for(unsigned int i = 0; i < str.length(); i++)
        ret += escape_char(str[i]);
    return ret;
}