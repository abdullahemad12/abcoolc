//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include "tree.h"
#include "cool.h"
#include "stringtab.h"

#define yylineno curr_lineno;
extern int yylineno;


class AnalysisException;
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
virtual void dump_with_types(ostream&, int) = 0;\
virtual void semant() = 0;


#define program_EXTRAS                          \
void semant();     				\
void dump_with_types(ostream&, int);            


////////////////////////
// Synch and clean adds and removes all the features 
// to and from the environment
////////////////////////
#define Class__EXTRAS                   \
virtual Symbol get_filename() = 0;      \
virtual Symbol get_name() = 0;		\
virtual Symbol get_parent() = 0;		\
virtual Features& get_features() = 0;	\
virtual void dump_with_types(ostream&,int) = 0; \
virtual void semant() = 0;	\
virtual void sync_local_env() = 0; \
virtual void clean_local_env() = 0; \
virtual void sync_global_env() = 0;
 


#define class__EXTRAS                               \
Symbol get_filename() { return filename; }           \
Symbol get_name() { return name; }                    \
Symbol get_parent() { return parent; }                 \
Features& get_features() { return features; }            \
void dump_with_types(ostream&,int);                    	\
void semant();											\
void sync_local_env(); 						\
void clean_local_env(); 					\
void sync_global_env();


#define Feature_EXTRAS                                        \
virtual void dump_with_types(ostream&,int) = 0; 				\
virtual void add_to_global_env(Symbol class_name) = 0;							\
virtual void add_to_local_env() = 0;							\
virtual void remove_from_local_env() = 0;						\
virtual void semant() = 0;										\
virtual Symbol get_name() = 0;									\
virtual void raise_redefinition_error() = 0;					\
bool is_malformed() { return malformed; }						\
protected:														\
void raise_error(AnalysisException* excep);											\
bool malformed = false;											

#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(ostream&,int);    \
void semant(); \
void add_to_global_env(Symbol class_name);							\
void add_to_local_env();							\
void remove_from_local_env();						\
Symbol get_name() { return name; };					\
void raise_redefinition_error();					\





#define Formal_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0;		\
virtual Symbol get_name(void) = 0;				\
virtual Symbol get_type_decl(void) = 0;		\
virtual void add_to_local_env() = 0;		\
virtual void remove_from_local_env() = 0;	\
virtual void semant() = 0;					\
bool is_malformed() { return malformed; } 	\
virtual void raise_redefinition_error() = 0; \
protected:									\
void raise_error(AnalysisException* excep);				\
bool malformed = false;

#define formal_EXTRAS                           \
void dump_with_types(ostream&,int);				\
Symbol get_name(void) { return name; }			\
Symbol get_type_decl(void) { return type_decl; } \
void add_to_local_env();			 \
void remove_from_local_env();		 \
void semant();						\
void raise_redefinition_error();

#define Case_EXTRAS                             \
virtual void dump_with_types(ostream& ,int) = 0; \
void semant();

#define branch_EXTRAS                                   \
void dump_with_types(ostream& ,int); \
void semant();


#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void dump_with_types(ostream&,int) = 0;  \
void dump_type(ostream&, int);               \
Expression_class() { type = (Symbol) NULL; } \
virtual void semant() = 0;


#define Expression_SHARED_EXTRAS           \
void dump_with_types(ostream&,int);  \
void semant();

#define method_EXTRAS			  \
Formals& get_formals() { return formals; } \
Symbol get_return_type() { return return_type; } \
Expression& get_expression() { return expr; } \
void raise_inconsistent_signature_error();

#define attr_EXTRAS				\
Symbol get_type_decl() { return type_decl; }


#endif
