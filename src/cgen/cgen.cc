
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include "cgen.h"
#include "cgen_gc.h"
#include "basic-symbols.h"
#include "code-container.h"
#include "memory-manager.h"
#include "default-value.h"

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

//////////////////////////////////////////////////////////////////////////
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//////////////////////////////////////////////////////////////////////////

static char *gc_init_names[] =
  { "_NoGC_Init", "_GenGC_Init", "_ScnGC_Init" };
static char *gc_collect_names[] =
  { "_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect" };



//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void program_class::cgen(ostream &os) 
{
  initialize_constants();
  initialize_default_values();
  CodeContainer ccon(os);
  install_basic_classes();
  create_inheritance_graph();
  StaticMemory static_memory;
  initialize_static_memory(static_memory);
  static_memory.cgen(ccon);
  MemoryManager memory_manager(static_memory);
  create_init_methods(ccon, memory_manager);
  cgen(ccon, memory_manager);
  
  ccon.write_out();
}

void program_class::initialize_default_values()
{
  int n = classes->len();
  for(int i = 0; i < n; i++)
    classes->nth(i)->default_value = new DefaultNull();
}


///////////////////////////////////////////////////////////////// 
// Cgen
//
// The implementation of the actual code generation of methods 
// and their expressions. Main theme is to recursively generate
// code for subexpressions the generate code the expression
/////////////////////////////////////////////////////////////////
void program_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void class__class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void method_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void attr_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void formal_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void assign_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void static_dispatch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void dispatch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void cond_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void loop_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void typcase_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void branch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void block_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void let_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void plus_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void sub_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void mul_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void divide_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void neg_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void lt_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void eq_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void leq_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void comp_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void int_const_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void bool_const_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void string_const_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void new__class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void isvoid_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void no_expr_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void object_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

















//////////////////////////////////////////////////////////////////////////////
//
// Garbage Collector
//
//////////////////////////////////////////////////////////////////////////////

/*static void emit_gc_assign(ostream& s)
{ s << JAL << "_GenGC_Assign" << endl; }


static void emit_test_collector(ostream &s)
{
  emit_push(ACC, s);
  emit_move(ACC, SP, s); // stack end
  emit_move(A1, ZERO, s); // allocate nothing
  s << JAL << gc_collect_names[cgen_Memmgr] << endl;
  emit_addiu(SP,SP,4,s);
  emit_load(ACC,0,SP,s);
}

static void emit_gc_check(char *source, ostream &s)
{
  if (source != (char*)A1) emit_move(A1, source, s);
  s << JAL << "_gc_check" << endl;
*/
















