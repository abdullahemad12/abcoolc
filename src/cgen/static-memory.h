////////////////////////////////////////////////////////////////////////
// StaticMemory
//
// Everything that lives in the static memory area of the 
// generated code is managed here. This includes ObjectPrototypes
// and all constants. This Class Abstracts all the interactions 
// with the static memory including generating code for static memory
///////////////////////////////////////////////////////////////////////
#ifndef STATIC_MEMORY_H
#define STATIC_MEMORY_H

#include <unordered_map>
#include <unordered_set>
#include "basic-symbols.h"
#include "cool-tree.h"
#include "object-prototype.h"
#include "code-container.h"
#include "emit.h"

using namespace std;

class StaticMemory 
{
    private:
      int str_ctr = 0;
      int int_ctr = 0;
      int tag_ctr = 0;
      unordered_map<string, string> string_consts;
      unordered_map<int, string> int_consts;
      unordered_map<Symbol, ObjectPrototype*> obj_prototypes;

      // may contain addition prototypes neccessary for correct construction
      // of initial object prototypes
      unordered_map<Symbol, ObjectPrototype*> construct_prototypes;

      void install_system_prototypes();
      void uninstall_system_prototypes();
      void cgen_global_declarations(CodeContainer& ccon);
      void cgen_global_word_declaration(CodeContainer& ccon, string label, string val);
      void cgen_gc_declarations(CodeContainer& ccon);
      void cgen_object_prototypes(CodeContainer& ccon);
      void cgen_object_header(CodeContainer& ccon, string label, int tag, int size, string dispatch_ptr);
      void cgen_string_consts(CodeContainer& ccon);
      void cgen_int_consts(CodeContainer& ccon);
      void cgen_true_const(CodeContainer& ccon);
      void cgen_false_const(CodeContainer& ccon);
      void cgen_class_table(CodeContainer& ccon);
      void cgen_global_text(CodeContainer& ccon);
      void cgen_ancestors_table_ptrs(CodeContainer& ccon);
      StaticMemory(const StaticMemory&) = delete;
      
    public:
        StaticMemory();

        /**
          * @brief finds a the label of a given constant
          * @requires: the constant to be present. Hangs the program if not found
          * @param the constant to be fetched
          * @returns string the label corresponding to the given constant
          */ 
        string const_label(int i);
        string const_label(string s);
        string false_lable();
        string true_label();
        
        /**
          * @brief looks up the object prototype of a given class 
          * @requires: StaticMemory to be initialized correctly
          * @param Symbol the name of the class to be looked up
          * @returns the object prototype of the given class 
          */
        ObjectPrototype& lookup_objectprot(Symbol class_name);

        /**
          * @brief adds a constant to the static memory. If the constant
          *        already exists does nothing
          * @modifies: this
          * @param constant to be added
          */
        void add_const(int i);
        void add_const(string str);

        /**
          * @brief looks up the label of a given constant
          * @requires: the constant to be added. Hangs if it is not found
          * @param constant to be looked up
          */ 
        string lookup_label(string str_const);
        string lookup_label(int int_const);

        /**
          * @brief creates a prototype for all the static informtion of given class 
          *        that needs to be written in the static memory
          * @requires: This is extremely important. The classes has to be inserted 
          *            in DFS order according to the inheritance graph. Thus for 
          *            any class, its parent must be installed first
          * @modifies: this
          * @param Class_ the class to be added
          */
        void install_class(Class_ class_);
        /**
          * @brief writes out all the static memory parts for this program
          * @requires: to be called once after all the object prototypes were added
          * @param CodeContainer& the code container
          */ 
        void cgen(CodeContainer& ccon);
};

#endif /* STATIC_MEMORY_H*/