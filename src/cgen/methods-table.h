////////////////////////////////////////////////////////////////
// MethodsTable
//
// Stores the methods of a given class and its parent methods
////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <unordered_map>
#include "cool-tree.h"
#include "emit.h"
#include "code-container.h"


using namespace std;

#define DISPTABLE_LABEL(class_name) (class_name + DISPATCH_LABEL_SUFFIX)
#define METHOD_LABEL(class_name, method_name) (class_name + METHOD_SEP + method_name)
class MethodsTable
{
    private:
        string label_attr;
        vector<method_class*> methods_attr;
        vector<method_class*> self_methods_attr;
        unordered_map<Symbol, int> meth_offset;
        vector<method_class*> extract_methods(Features features);
        void label_self_methods(string class_name, vector<method_class*>& methods);
        void assign_offsets();
    public:
        MethodsTable();
        MethodsTable(MethodsTable& parent_method_table, Class_ class_, Features features);
        void cgen(CodeContainer& ccon);
        string label();
        vector<method_class*> methods();
        vector<method_class*> self_methods();
        /**
          * @brief gets offset of a given method in the dispatch table
          * @requires: method to be present in this table. Hangs if it is not
          * @param Symbol the name of the method
          * @returns int the offset of the method in the dispatch table
          */
        int operator[](Symbol method_name); 
        string lookup_label(Symbol method_name);
        
        auto begin();
        auto end();
};