
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
static void eval_and_push_actual(CodeContainer& ccon, MemoryManager& mem_man, Expressions actual);
static void handle_dispatch_on_void(CodeContainer& ccon, MemoryManager& mem_man, 
                                      string file_name, int line_no);

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
  propagate_containing_class(NULL);
  initialize_default_values();
  CodeContainer ccon(os);
  install_basic_classes();
  create_inheritance_graph();
  StaticMemory static_memory;
  initialize_static_memory(static_memory);
  static_memory.cgen(ccon);
  MemoryManager memory_manager(static_memory);
  create_init_methods(ccon, memory_manager);
  uninstall_basic_classes();
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
// code for subexpressions the generate code the expression. 
// Important invariant is that the result of evaluating an 
// expression is stored in the accumelator ($a0)
/////////////////////////////////////////////////////////////////
void program_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  int n = classes->len();
  for(int i = 0; i < n; i++)
    classes->nth(i)->cgen(ccon, mem_man);
}

void class__class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  // generate code for the local non-inherited methods only
  ObjectPrototype& prot = mem_man.static_memory().lookup_objectprot(name);
  vector<method_class*> methods = prot.methods_table().self_methods();
  int n = features->len();
  for(method_class* method : methods)
    method->cgen(ccon, mem_man);
}

void method_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  ccon.label(label);
  ActivationRecord ar(formals, mintmps());
  mem_man.enter_scope(ccon, containing_class, ar);
  expr->cgen(ccon, mem_man);
  mem_man.exit_scope(ccon);

}

void attr_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  StaticMemory& stat_mem = mem_man.static_memory();

  ObjectPrototype& type_proto = stat_mem.lookup_objectprot(type_decl);
  Register* acc = type_proto.default_value()->load_value(ccon, mem_man);

  assert(acc->get_name() == ACC);
  
  init->cgen(ccon, mem_man);

  MemSlot* attr_loc = mem_man.lookup_identifier(name);
  attr_loc->save(ccon, acc);

}

void formal_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void assign_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  expr->cgen(ccon, mem_man);
  MemSlot* attr_loc = mem_man.lookup_identifier(name);
  attr_loc->save(ccon, mem_man.acc());
}

void static_dispatch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  int n, method_offset;

  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& prot = stat_mem.lookup_objectprot(type_name);
  MethodsTable& meth_tab = prot.methods_table();
  string file_name(containing_class->get_filename()->get_string());
  
  eval_and_push_actual(ccon, mem_man, actual);

  expr->cgen(ccon, mem_man);
  handle_dispatch_on_void(ccon, mem_man, file_name, line_number);

  // call method if not void 
  ccon.jal(meth_tab.lookup_label(name));

}

void dispatch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  int n, method_offset;
  Register *tmp, *acc;

  // resolve class
  Symbol class_name = expr->type;
  if(class_name == SELF_TYPE)
    class_name = containing_class->get_name();
  
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& prot = stat_mem.lookup_objectprot(class_name);
  MethodsTable& meth_tab = prot.methods_table();
  string file_name(containing_class->get_filename()->get_string());

  method_offset = meth_tab[name];

  eval_and_push_actual(ccon, mem_man, actual);

  expr->cgen(ccon, mem_man);
  
  // terminates if not void
  handle_dispatch_on_void(ccon, mem_man, file_name, line_number);

  // call method if not void 
  tmp = mem_man.tmp1();
  acc = mem_man.acc();
  MemSlot* disp_ptr = mem_man.lookup_identifier(obj_disp_ptr);
  ccon.lw(tmp, disp_ptr->load(ccon), method_offset * WORD_SIZE);
  ccon.jalr(tmp);
}

void cond_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void loop_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void typcase_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  // declarations
  int n, index;
  Register *t1, *t2, *acc, *cache, *zero;
  MemSlot *anc_tab, *id_slot;
  string next_label, end_label;
  StaticMemory& stat_mem = mem_man.static_memory();

  zero = mem_man.zero();
  acc = mem_man.acc();
  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();

  expr->cgen(ccon, mem_man);

  case_on_void_check(ccon, mem_man);  

  id_slot = mem_man.memalloc();
  id_slot->save(ccon, acc);
  
  // load ancestors table into a memory location
  anc_tab = mem_man.memalloc();
  load_ancestors_table(ccon, mem_man, anc_tab);
  
  sort_branches(stat_mem);
  end_label = mem_man.gen_label();
  n = sorted_cases.size();
  for(int i = 0; i < n; i++)
  {
    next_label = mem_man.gen_label();
    Case branch = sorted_cases[i];
    ObjectPrototype& obj_prot = stat_mem.lookup_objectprot(branch->get_type());
    index = obj_prot.ancestors_table().size();
    cache = anc_tab->load(ccon);

    // ancestors table length check (avoids out of bound check)
    ccon.lw(t1, cache, ANC_LEN_OFFSET * WORD_SIZE);
    ccon.addi(t1, t1, -1 * (index));
    ccon.bltz(t1, next_label);
    
    // ancestors check
    ccon.lw(t1, cache, index * WORD_SIZE);
    ccon.li(t2, obj_prot.tag());
    ccon.bne(t1, t2, next_label);

    // generate code for branch
    id_slot = mem_man.add_identifier(branch->get_name(), id_slot);
    branch->cgen(ccon, mem_man);
    mem_man.remove_identifier(branch->get_name());
    ccon.jump(end_label);
    ccon.label(next_label);
  }

  no_match_error(ccon, mem_man, id_slot);

  ccon.label(end_label);
  
  // reclaim memory
  mem_man.memfree(id_slot);
  mem_man.memfree(anc_tab);
}

void branch_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    expr->cgen(ccon, mem_man);
}

void block_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void let_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void plus_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  MemSlot* slot;
  Register *cache, *acc, *t1;
  slot = mem_man.memalloc();
  acc = mem_man.acc();
  t1 = mem_man.tmp1();
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& int_prot = stat_mem.lookup_objectprot(Int);
  MethodsTable& meth_tab = int_prot.methods_table();

  // create new int object
  ccon.la(acc, int_prot.label());
  ccon.jal(meth_tab.lookup_label(copyy));

  slot->save(ccon, acc);

  e1->cgen(ccon, mem_man);

  // add the result to the new object
  cache = slot->load(ccon);
  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.sw(acc, cache, DEFAULT_OBJFIELDS * WORD_SIZE);

  // accumelate the result
  e2->cgen(ccon, mem_man);
  cache = slot->load(ccon);
  ccon.lw(t1, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.add(acc, t1, acc);
  ccon.sw(acc, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.move(acc, cache);
  mem_man.memfree(slot);
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
  StaticMemory& stat_mem = mem_man.static_memory();
  Register* acc = mem_man.acc();
  string s(token->get_string());
  ccon.la(acc, stat_mem.lookup_label(stoi(s)));
}

void bool_const_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  StaticMemory& stat_mem = mem_man.static_memory();
  Register* acc = mem_man.acc();

  if(val == 0)
    ccon.la(acc, stat_mem.false_lable());
  else
    ccon.la(acc, stat_mem.true_label());
}

void string_const_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  StaticMemory& stat_mem = mem_man.static_memory();
  string label = stat_mem.lookup_label(token->get_string());
  ccon.la(mem_man.acc(), label);
}

void new__class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void isvoid_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *acc, *zero;
  string is_not_void, end;
  StaticMemory& stat_mem = mem_man.static_memory();
  is_not_void = mem_man.gen_label();
  end = mem_man.gen_label();
  acc = mem_man.acc();
  zero = mem_man.zero();

  e1->cgen(ccon, mem_man);


  ccon.bne(acc, zero, is_not_void);
  ccon.la(acc, stat_mem.true_label());
  ccon.jump(end);
  ccon.label(is_not_void);
  ccon.la(acc, stat_mem.false_lable());
  ccon.label(end);
}

void no_expr_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    
}

void object_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    MemSlot* obj;
    Register* cache;
    obj = mem_man.lookup_identifier(name);
    cache = obj->load(ccon);
    ccon.move(mem_man.acc(), cache);
}







//////////////////////////////////////////////
// Helper functions for cgen
// 
/////////////////////////////////////////////


////////////////////////
// dispatch
///////////////////////
void eval_and_push_actual(CodeContainer& ccon, MemoryManager& mem_man, Expressions actual)
{
  int n = actual->len();
  for(int i = 0; i < n; i++)
  {
    actual->nth(i)->cgen(ccon, mem_man);
    mem_man.push_acc(ccon);
  }
}

// checks that the value in the accumelator is not zero
static void handle_dispatch_on_void(CodeContainer& ccon, MemoryManager& mem_man, 
                                    string file_name, int line_no)
{
  StaticMemory& stat_mem = mem_man.static_memory();
  string label = mem_man.gen_label();
  Register* acc = mem_man.acc();
  Register* zero = mem_man.zero();

  ccon.bne(acc, zero, label);
  ccon.li(mem_man.tmp1(), line_no);
  ccon.la(mem_man.acc(), stat_mem.lookup_label(file_name));
  ccon.jal(DISPATCH_ABORT);
  ccon.label(label);
}


/////////////////////
// Case Statement
/////////////////////
void typcase_class::load_ancestors_table(CodeContainer& ccon, MemoryManager& mem_man, MemSlot* mem_slot)
{
  Register *t1, *t2, *acc;
  StaticMemory& stat_mem = mem_man.static_memory();
  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();
  acc = mem_man.acc();
  ccon.la(t1, ANCESTORS_TAB_PTR);
  ccon.lw(t2, acc, TAG_OFFSET * WORD_SIZE);
  ccon.sli(t2, t2, 2);
  ccon.add(t1, t1, t2);
  ccon.lw(t1, t1, 0);
  mem_slot->save(ccon, t1);
}

void typcase_class::sort_branches(StaticMemory& stat_mem)
{
  int n, max;
  Case max_case;

  vector<Case> my_branches;
  
  n = cases->len();
  for(int i = 0; i < n; i++)
    my_branches.push_back(cases->nth(i));
  
  // selection sort
  for(int i = 0; i < n; i++)
  {
      max = -1;
      max_case = NULL;
      for(int j = i; j < n; j++)
      {
        ObjectPrototype& prot = stat_mem.lookup_objectprot(my_branches[j]->get_type());
        if(prot.depth() >= max)
        {
          max = prot.depth();
          max_case = my_branches[j];
        }
      }
      sorted_cases.push_back(max_case);
  }
}

void typcase_class::case_on_void_check(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *acc, *t1, *zero;
  string file_name(containing_class->get_filename()->get_string());
  string success = mem_man.gen_label();
  StaticMemory& stat_mem = mem_man.static_memory();

  acc = mem_man.acc();
  t1 = mem_man.tmp1();
  zero = mem_man.zero();

  // case on void
  ccon.bne(acc, zero, success);
  ccon.li(t1, line_number);
  ccon.la(acc, stat_mem.lookup_label(file_name));
  ccon.jal(CASE_ABORT_VOID);

  // begin the case check
  ccon.label(success);
}

void typcase_class::no_match_error(CodeContainer& ccon, MemoryManager& mem_man, MemSlot* id_slot)
{
  Register *t1, *t2, *acc;

  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();
  acc = mem_man.acc();

  // no match error
  ccon.lw(t2, id_slot->load(ccon), WORD_SIZE * TAG_OFFSET);
  ccon.sli(t2, t2, 2);
  ccon.la(t1, CLASSNAMETAB);
  ccon.add(t2, t2, t1);
  ccon.lw(acc, t2, 0);
  ccon.jal(CASE_ABORT);
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











