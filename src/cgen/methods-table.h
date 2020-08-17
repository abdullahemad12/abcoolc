////////////////////////////////////////////////////////////////
// MethodsTable
//
// Stores the methods of a given class and its parent methods
////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include "cool-tree.h"

using namespace std;


class MethodsTable
{
    private:
        string label_attr;
        vector<method_class*> methods_attr;
        vector<method_class*> extract_methods(Features features);
    public:
        MethodsTable();
        MethodsTable(MethodsTable& parent_method_table, Class_ class_, Features features);
        string label();
        vector<method_class*> methods();
        auto begin();
        auto end();
};