////////////////////////////////////////////////////////////////////
// StaticMemory
//
// Everything that lives in the static memory area of the 
// generated code is managed here. This includes ObjectPrototypes
// and all constants
////////////////////////////////////////////////////////////////////

#include <cool-tree.h>

#ifndef STATIC_MEMORY_H
#define STATIC_MEMORY_H

#include <unordered_map>
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

    public:
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
        void add_object_prot(Symbol class_name, ObjectPrototype obj_prot);
};

#endif /* STATIC_MEMORY_H*/