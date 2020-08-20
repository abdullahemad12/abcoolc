//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include <vector>
#include "tree.h"
#include "cool.h"
#include "stringtab.h"


#define yylineno curr_lineno;
extern int yylineno;

class ObjectPrototype;
class method_class;
class attr_class;

inline Boolean copy_Boolean(Boolean b) {return b; }
inline void assert_Boolean(Boolean) {}
inline void dump_Boolean(ostream& stream, int padding, Boolean b)
	{ stream << pad(padding) << (int) b << "\n"; }

void dump_Symbol(ostream& stream, int padding, Symbol b);
void assert_Symbol(Symbol b);
Symbol copy_Symbol(Symbol b);

class Program_class;
typedef Program_class *Program;
class Class__class;
typedef Class__class *Class_;
class Feature_class;
typedef Feature_class *Feature;
class Formal_class;
typedef Formal_class *Formal;
class Expression_class;
typedef Expression_class *Expression;
class Case_class;
typedef Case_class *Case;

typedef list_node<Class_> Classes_class;
typedef Classes_class *Classes;
typedef list_node<Feature> Features_class;
typedef Features_class *Features;
typedef list_node<Formal> Formals_class;
typedef Formals_class *Formals;
typedef list_node<Expression> Expressions_class;
typedef Expressions_class *Expressions;
typedef list_node<Case> Cases_class;
typedef Cases_class *Cases;

#define Program_EXTRAS                          \
virtual void cgen(ostream&) = 0;		\
virtual void dump_with_types(ostream&, int) = 0; 



#define program_EXTRAS                          \
void cgen(ostream&);     			\
void dump_with_types(ostream&, int); \
private: \
Classes original_classes; \
void install_basic_classes(); \
void uninstall_basic_classes(); \
void create_inheritance_graph(); \
void assign_classes_tags();

#define Class__EXTRAS                   \
virtual Symbol get_name() = 0;  	\
virtual Symbol get_parent() = 0;    	\
virtual Symbol get_filename() = 0;      \
virtual void dump_with_types(ostream&,int) = 0; \
virtual void add_child_class(Class_ class_) = 0; \
int tag;

#define class__EXTRAS   				\
Symbol get_name()   { return name; }		       \
Symbol get_parent() { return parent; }     	       \
Symbol get_filename() { return filename; }             \
void add_child_class(Class_ class_);			\
void dump_with_types(ostream&,int);    \


#define Feature_EXTRAS                                        \
virtual void dump_with_types(ostream&,int) = 0; 	\
virtual void filter_feature(std::vector<attr_class*>& attrs) = 0; \
virtual void filter_feature(std::vector<method_class*>& meths) = 0; \
virtual Symbol get_name() = 0;

#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(ostream&,int);    		\
void filter_feature(std::vector<attr_class*>& attrs);	\
void filter_feature(std::vector<method_class*>& meths);\
Symbol get_name() { return name; }

#define method_EXTRAS			\
int mintmps();

#define Formal_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0;	\
virtual Symbol get_name() = 0;


#define formal_EXTRAS                           \
void dump_with_types(ostream&,int);			\
Symbol get_name() { return name; }


#define Case_EXTRAS                             \
virtual void dump_with_types(ostream& ,int) = 0; \
virtual int mintmps() = 0;

#define branch_EXTRAS                                   \
void dump_with_types(ostream& ,int);				\
int mintmps();



#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void code(ostream&) = 0; \
virtual void dump_with_types(ostream&,int) = 0;  \
void dump_type(ostream&, int);               \
Expression_class() { type = (Symbol) NULL; }  \
virtual int mintmps() = 0;

#define Expression_SHARED_EXTRAS           \
void code(ostream&); 			   \
void dump_with_types(ostream&,int);  \
int mintmps();


#endif
