////////////////////////////////////////////////////////////////////
// StaticMemory
//
// Everything that lives in the static memory area of the 
// generated code is managed here. This includes ObjectPrototypes
// and all constants
////////////////////////////////////////////////////////////////////
#ifndef STATIC_MEMORY_H
#define STATIC_MEMORY_H

#include <unordered_map>
#include "cool-tree.h"
#include "object-prototype.h"
#include "code-container.h"

using namespace std;

#define INT_CONST_LABEL(i) ("int_const_" + std::to_string(i))
#define STR_CONST_LABEL(s) ("string_const_" + s)

class StaticMemory 
{
    private:
      unordered_map<string, string> string_consts;
      unordered_map<int, string> int_consts;
      unordered_map<Symbol, ObjectPrototype> obj_prototypes;
      void gc_declaration(CodeContainer& ccon);
      void write_object_header(CodeContainer& ccon, string label, int tag, int size, string dispatch_ptr);
      void write_string_consts(CodeContainer& ccon);
      void write_int_consts(CodeContainer& ccon);
      void write_true_const(CodeContainer& ccon);
      void write_false_const(CodeContainer& ccon);
      StaticMemory(const StaticMemory&) = delete;
      
    public:
        StaticMemory();
        string const_label(int i);
        string const_label(string s);
        /**
          * @brief looks up the object prototype of a given class 
          * @requires: StaticMemory to be initialized correctly
          * @param Symbol the name of the class to be looked up
          * @returns the object prototype of the given class 
          */
        ObjectPrototype& lookup_objectprot(Symbol class_name);
        void add_const(int i);
        void add_const(string str);
        string lookup_label(string str_const);
        string lookup_label(int int_const);
        /**
          * @brief adds a new Object Prototype to the static memory.
          * @modifies: this
          * @param Symbol the name of the class 
          * @param ObjectPrototype the object prototype
          */
        void add_object_prot(Symbol class_name, ObjectPrototype obj_prot);
        /**
          * @brief writes out all the static memory parts for this program
          * @requires: to be called once after all the object prototypes were added
          * @param CodeContainer& the code container
          */ 
        void write_out(CodeContainer& ccon);
};

#endif /* STATIC_MEMORY_H*/