////////////////////////////////////////////////////////////////
// MethodsTable
//
// Stores the methods of a given class and its parent methods
////////////////////////////////////////////////////////////////
#include <string>
#include <list>
#include "cool-tree.h"
using namespace std;


class MethodsTable
{
    private:
        std::list<method_class*> methods;
        string label;
    public:
        MethodsTable(Class_ class_);
        void copy_parent_table(MethodsTable& meth_table);
};