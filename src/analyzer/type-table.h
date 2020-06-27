#ifndef _TYPE_TABLE_H_
#define _TYPE_TABLE_H_

#include <cool-tree.h>

#include <unordered_set>

using namespace std;
static char* no_type = "_no_type"; 

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copyy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copyy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}


class TypeTable
{
    private:
        unordered_set<Symbol> all_defined_types;
        // those you cannot inherit
        unordered_set<Symbol> basic_types;
        // those you cannot redefine 
        unordered_set<Symbol> reserved_types;
        // usage of those are restricted
        unordered_set<Symbol> reserved_identifiers;
        // this cannot be redefined
        unordered_set<Symbol> built_in_types;

    public:
        TypeTable(Classes classes);
        /**
          * @brief checks if the given type exists in the type table. the type can be 
          *        built-in or user defined
          * @param type 
          * @return true if it is found (i.e defined)
          */
        bool contains(Symbol type);
        /**
          * @brief checks if the given symbol is one of the basic types 
          * @param type
          * @return true if type is a basic type
          */ 
        bool is_basic_type(Symbol type);
        /**
          * @brief checks if the given symbol is one of the reserved types
          * @param type
          * @return true if type is a reserved type
          */ 
        bool is_reserved_type(Symbol type);

        /**
         * @brief checks if the given type is one of the built-in types
         * @param id
         * @return true if type is a built-in identifier
         */ 
        bool is_built_in_type(Symbol type);

        /**
         * @brief checks if the given identifier is one of the reserved identifiers
         * @param id
         * @return true if type is a reserved identifier
         */ 
        bool is_reserved_identifier(Symbol id);

};



#endif /*_TYPE_TABLE_H_*/