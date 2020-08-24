////////////////////////////////////////////////////////////////
// MethodsTable
//
// Stores the methods of a given class and its parent methods
////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
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
        vector<method_class*> extract_methods(Features features);
        void label_self_methods(string class_name, vector<method_class*>& methods);
    public:
        MethodsTable();
        MethodsTable(MethodsTable& parent_method_table, Class_ class_, Features features);
        void cgen(CodeContainer& ccon);
        string label();
        vector<method_class*> methods();
        vector<method_class*> self_methods();
        auto begin();
        auto end();
};