//
// The following include files must come first.

#ifndef COOL_TREE_HANDCODE_H
#define COOL_TREE_HANDCODE_H

#include <iostream>
#include "tree.h"
#include "cool.h"
#include "stringtab.h"

#define LOCAL_TYPE "local_type"
#define yylineno curr_lineno;
extern int yylineno;

class UnionFind;
class Environment;
class TypeTable;
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
void dump_with_types(ostream&, int);  	\
private:							\
Classes original_classes; \
void install_basic_classes();	\
void uninstall_basic_classes(); \
void redefintions_detection();	\
void missing_main_detection();	\
void cycle_detection();	\
void builtin_duplication_detection(TypeTable& typetable); \
void validate_all(TypeTable& typetable);

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
virtual void sync_local_env(Environment& env) = 0; \
virtual void clean_local_env(Environment& env) = 0; \
virtual void sync_global_env(Environment& env) = 0; \
virtual bool is_main() = 0;				\
virtual void duplication_detected() = 0; \
virtual void builtin_duplication_detected() = 0;

#define class__EXTRAS                               \
Symbol get_filename() { return filename; }           \
Symbol get_name() { return name; }                    \
Symbol get_parent() { return parent; }                 \
Features& get_features() { return features; }            \
void dump_with_types(ostream&,int);                    	\
void sync_local_env(Environment& env); 						\
void clean_local_env(Environment& env); 					\
void sync_global_env(Environment& env);				\
void duplication_detected();			\
void builtin_duplication_detected();			\
private:					\
bool is_main();				\
void undefined_type_detection(TypeTable& tb);		\
void name_reserved_detection(TypeTable& tb);	\
void inheritance_reserved_detection(TypeTable& tb);	\
void basic_class_inheritance_detection(TypeTable& tb);		\
void feature_redefinition_detection();			\
void has_main();

#define Feature_EXTRAS                                        \
virtual void dump_with_types(ostream&,int) = 0; 				\
virtual void add_to_env(Symbol class_name, Environment& env) = 0;							\
virtual void remove_from_env(Environment& env) = 0;						\
virtual Symbol get_name() = 0; \
virtual Symbol get_type() = 0; \
virtual bool is_main() = 0; \
void duplication_detected();

#define Feature_SHARED_EXTRAS                                       \
void dump_with_types(ostream&,int);    \
void add_to_env(Symbol class_name, Environment& env);		\
void remove_from_env(Environment& env);						\
Symbol get_name() { return name; };					\
void reserved_symbols_misuse_detection(TypeTable& typetable);\
void undefined_types_detection(TypeTable& typetable); \
void formal_redefinition_detection(TypeTable& typetable); \
bool is_main();

#define Formal_EXTRAS                              \
virtual void dump_with_types(ostream&,int) = 0;		\
virtual Symbol get_name(void) = 0;				\
virtual Symbol get_type_decl(void) = 0;		\
virtual void add_to_env(Environment& env) = 0;		\
virtual void remove_from_env(Environment& env) = 0;	\
virtual void duplication_detected() = 0;

#define formal_EXTRAS                           \
void dump_with_types(ostream&,int);				\
Symbol get_name(void) { return name; }			\
Symbol get_type_decl(void) { return type_decl; } \
void add_to_env(Environment& env);			 \
void remove_from_env(Environment& env);		 \
void reserved_symbols_misuse_detection(TypeTable& typetable);\
void undefined_types_detection(TypeTable& typetable); \
void reserved_type_misuse_detection(TypeTable& typetable); \
void duplication_detected();

#define Case_EXTRAS                             \
virtual void dump_with_types(ostream& ,int) = 0; \


#define typcase_EXTRAS \
private: \
void redefinition_detection(TypeTable& typetable); \


#define branch_EXTRAS                                   \
void dump_with_types(ostream& ,int); \
void reserved_symbols_misuse_detection(TypeTable& typetable);\
void undefined_types_detection(TypeTable& typetable);


#define Expression_EXTRAS                    \
Symbol type;                                 \
Symbol get_type() { return type; }           \
Expression set_type(Symbol s) { type = s; return this; } \
virtual void dump_with_types(ostream&,int) = 0;  \
void dump_type(ostream&, int);               \
Expression_class() { type = (Symbol) NULL; } \
virtual void reserved_symbols_misuse_detection(TypeTable& typetable) = 0;\
virtual void undefined_types_detection(TypeTable& typetable) = 0; \




#define Expression_SHARED_EXTRAS           \
void dump_with_types(ostream&,int);  \
void reserved_symbols_misuse_detection(TypeTable& typetable);\
void undefined_types_detection(TypeTable& typetable); \

#define method_EXTRAS			  \
Formals& get_formals() { return formals; } \
Symbol get_type() { return return_type; } \
Expression& get_expression() { return expr; } \
void sync_environment(Environment& env);				\
void clean_environment(Environment& env); \
void formals_redefinition_detection();

#define attr_EXTRAS				\
Symbol get_type() { return type_decl; };






#endif
