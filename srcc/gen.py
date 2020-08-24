
import pyperclip


types = ['program_class', 'class__class', 'method_class', 'attr_class', 'formal_class', 'assign_class', 'static_dispatch_class', 'dispatch_class', 'cond_class', 'loop_class', 'typcase_class', 'branch_class', 'block_class', 'let_class', 'plus_class', 'sub_class', 'mul_class', 'divide_class', 'neg_class', 'lt_class', 'eq_class', 'leq_class', 'comp_class', 'int_const_class', 'bool_const_class', 'string_const_class', 'new__class', 'isvoid_class', 'no_expr_class', 'object_class']
code = ''
for typ in types:
	sign = 'void %s::cgen(CodeContainer& ccon, MemoryManager& mem_man)\n\
{\n\
    \n\
}\n\n' % (typ)
	code = code + sign
pyperclip.copy(code)

