
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
static void cgen_arith(CodeContainer& ccon, MemoryManager& mem_man, Expression e1, 
                      Expression e2, GenArithOperation& arith);

static void cgen_comp(CodeContainer& ccon, MemoryManager& mem_man, Expression e1,
                      Expression e2, ComparisonCgen& op);


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
  // (acc still holds the object at this point
  //  because handle dispatch will not execute in this case)
  tmp = mem_man.tmp1();
  acc = mem_man.acc();
  ccon.lw(tmp, acc, DISPTABLE_OFFSET * WORD_SIZE);
  ccon.lw(tmp, tmp, method_offset * WORD_SIZE);
  ccon.jalr(tmp);
}

void cond_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *t1, *t2, *acc, *zero;
  string else_label, end_if;

  else_label = mem_man.gen_label();
  end_if = mem_man.gen_label();

  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();
  acc = mem_man.acc();
  zero = mem_man.zero();

  pred->cgen(ccon, mem_man);
  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);

  // if false go to else
  ccon.beq(acc, zero, else_label);

  then_exp->cgen(ccon, mem_man);
  ccon.jump(end_if);

  ccon.label(else_label);
  else_exp->cgen(ccon, mem_man);

  ccon.label(end_if);
  
}

void loop_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *t1, *t2, *acc, *zero;
  string start_loop, end_loop;

  start_loop = mem_man.gen_label();
  end_loop = mem_man.gen_label();

  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();
  acc = mem_man.acc();
  zero = mem_man.zero();

  ccon.label(start_loop);
  pred->cgen(ccon, mem_man);

  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  // if false exit loop
  ccon.beq(acc, zero, end_loop);
  
  body->cgen(ccon, mem_man);

  ccon.jump(start_loop);
  ccon.label(end_loop);
  
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
    int n = body->len();
    for(int i = 0; i < n; i++)
      body->nth(i)->cgen(ccon, mem_man);
}

void let_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *acc, *cache;
  MemSlot* slot;
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& obj_prot = stat_mem.lookup_objectprot(type_decl);
  acc = mem_man.acc();

  cache = obj_prot.default_value()->load_value(ccon, mem_man);
  acc->save(ccon, acc);

  init->cgen(ccon, mem_man);

  slot = mem_man.add_identifier(identifier);
  slot->save(ccon, mem_man.acc());

  body->cgen(ccon, mem_man);

  mem_man.remove_and_free_identifier(identifier);
}

void plus_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  PlusCgen arith;
  cgen_arith(ccon, mem_man, e1, e2, arith); 
}

void sub_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  SubCgen arith;
  cgen_arith(ccon, mem_man, e1, e2, arith);
}

void mul_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    MulCgen arith;
    cgen_arith(ccon, mem_man, e1, e2, arith);
}

void divide_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    DivCgen arith;
    cgen_arith(ccon, mem_man, e1, e2, arith);
}

void neg_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *acc, *zero, *t1, *cache;
  MemSlot* slot;
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& int_prot = stat_mem.lookup_objectprot(Int);
  MethodsTable& meth_tab = int_prot.methods_table();
  acc = mem_man.acc();
  zero = mem_man.zero();
  t1 = mem_man.tmp1();

  e1->cgen(ccon, mem_man);

  slot = mem_man.memalloc();

  slot->save(ccon, acc);

  ccon.la(acc, int_prot.label());
  ccon.jal(meth_tab.lookup_label(copyy));

  cache = slot->load(ccon);

  ccon.lw(t1, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.subu(t1, zero, t1);
  ccon.sw(t1, acc, DEFAULT_OBJFIELDS * WORD_SIZE);

  mem_man.memfree(slot);
}

void lt_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
    LtCgen comp;
    cgen_comp(ccon, mem_man, e1, e2, comp);
}

void leq_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  LeqCgen comp;
  cgen_comp(ccon, mem_man, e1, e2, comp);
}


void eq_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  MemSlot *slot;
  Register *cache, *acc, *a1, *t1, *t2;
  StaticMemory& stat_mem = mem_man.static_memory();
  string true_label, end_label;

  acc = mem_man.acc();
  a1 = mem_man.a1();
  t1 = mem_man.tmp1();
  t2 = mem_man.tmp2();
  true_label = mem_man.gen_label();
  end_label = mem_man.gen_label();

  e1->cgen(ccon, mem_man);
  
  slot = mem_man.memalloc();
  slot->save(ccon, acc);

  e2->cgen(ccon, mem_man);
  
  ccon.move(t1, acc);
  cache = slot->load(ccon);
  ccon.move(t2, cache);

  // check if the ptrs are equal
  ccon.beq(t1, t2, true_label);
  
  ccon.li(acc, 1);
  ccon.li(a1, 0);
  ccon.jal(EQUALITY_TEST);
  ccon.li(a1, 0);
  ccon.bne(acc, a1, true_label);
  
  //not equal
  ccon.la(acc, stat_mem.false_lable());
  ccon.jump(end_label);
  
  // equal
  ccon.label(true_label);
  ccon.la(acc, stat_mem.true_label());
  
  ccon.label(end_label);
  
  mem_man.memfree(slot);
}

void comp_class::cgen(CodeContainer& ccon, MemoryManager& mem_man)
{
  Register *acc, *t1, *zero;
  string true_label, end_label;
  StaticMemory& stat_mem = mem_man.static_memory();

  true_label = mem_man.gen_label();
  end_label = mem_man.gen_label();

  acc = mem_man.acc();
  t1 = mem_man.tmp1();
  zero = mem_man.zero();

  e1->cgen(ccon, mem_man);

  ccon.lw(t1, acc, DEFAULT_OBJFIELDS * WORD_SIZE);

  ccon.bne(t1, zero, true_label);
  ccon.la(acc, stat_mem.true_label());
  ccon.jump(end_label);
  
  ccon.label(true_label);
  ccon.la(acc, stat_mem.false_lable());
  ccon.label(end_label);
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
  Register *acc;
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& obj_prot = stat_mem.lookup_objectprot(type_name);
  MethodsTable& meth_table = obj_prot.methods_table();
  acc = mem_man.acc();

  ccon.la(acc, obj_prot.label());
  ccon.jal(meth_table.lookup_label(copyy));
  ccon.jal(obj_prot.init_method_label());
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

  unordered_set<Case> my_branches;
  
  n = cases->len();
  for(int i = 0; i < n; i++)
    my_branches.insert(cases->nth(i));
  
  // selection sort
  for(int i = 0; i < n; i++)
  {
      max = -1;
      max_case = NULL;
      for(auto my_branch : my_branches)
      {
        ObjectPrototype& prot = stat_mem.lookup_objectprot(my_branch->get_type());
        if(prot.depth() >= max)
        {
          max = prot.depth();
          max_case = my_branch;
        }
      }
      sorted_cases.push_back(max_case);
      my_branches.erase(max_case);
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

/////////////////////////
// Arithmetic Helpers
////////////////////////
static void cgen_arith(CodeContainer& ccon, MemoryManager& mem_man, Expression e1, 
                      Expression e2, GenArithOperation& arith)
{
  MemSlot* slot;
  Register *cache, *acc, *t1;
  acc = mem_man.acc();
  t1 = mem_man.tmp1();
  StaticMemory& stat_mem = mem_man.static_memory();
  ObjectPrototype& int_prot = stat_mem.lookup_objectprot(Int);
  MethodsTable& meth_tab = int_prot.methods_table();


  e1->cgen(ccon, mem_man);

  slot = mem_man.memalloc();
  slot->save(ccon, acc);

  // create new int object
  ccon.la(acc, int_prot.label());
  ccon.jal(meth_tab.lookup_label(copyy));

  // add the result to the new object
  cache = slot->load(ccon);
  ccon.lw(cache, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.sw(cache, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  slot->save(ccon, acc);

  // accumelate the result
  e2->cgen(ccon, mem_man);
  cache = slot->load(ccon);
  ccon.lw(t1, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  arith.cgen(ccon, acc, t1, acc);
  ccon.sw(acc, cache, DEFAULT_OBJFIELDS * WORD_SIZE);
  ccon.move(acc, cache);
  mem_man.memfree(slot);
}

void PlusCgen::cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2)
{
  ccon.add(dest, op1, op2);
}
void SubCgen::cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2)
{
  ccon.sub(dest, op1, op2);
}
void MulCgen::cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2)
{
  ccon.mul(dest, op1, op2);
}

void DivCgen::cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2)
{
  ccon.div(dest, op1, op2);

}

//////////////////
// Comparisons
//////////////////
static void cgen_comp(CodeContainer& ccon, MemoryManager& mem_man, Expression e1, Expression e2, ComparisonCgen& op)
{
  MemSlot* slot;
  Register *cache, *acc;
  string true_label, end_label;

  StaticMemory& stat_mem = mem_man.static_memory();

  true_label = mem_man.gen_label();
  end_label = mem_man.gen_label();

  acc = mem_man.acc();

  e1->cgen(ccon, mem_man);
  slot = mem_man.memalloc();
  slot->save(ccon, acc);

  e2->cgen(ccon, mem_man);
  ccon.lw(acc, acc, DEFAULT_OBJFIELDS * WORD_SIZE);
  cache = slot->load(ccon);
  ccon.lw(cache, cache, DEFAULT_OBJFIELDS * WORD_SIZE);

  ccon.sub(acc, cache, acc);
  op.cgen(ccon, acc, true_label);
  ccon.la(acc, stat_mem.false_lable());
  ccon.jump(end_label);

  ccon.label(true_label);
  ccon.la(acc, stat_mem.true_label());
  ccon.label(end_label);
  mem_man.memfree(slot);
}

void LeqCgen::cgen(CodeContainer& ccon, Register* res, string destination)
{
  ccon.blez(res, destination);
}

void LtCgen::cgen(CodeContainer& ccon, Register* res, string destination)
{
  ccon.bltz(res, destination);
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











