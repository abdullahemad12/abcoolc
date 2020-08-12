////////////////////////////////////////////////////////////////
// MethodsTable
//
// Stores the methods of a given class and its parent methods
////////////////////////////////////////////////////////////////
#include <string>
#include "cool-tree.h"

using namespace std;

class MethodTable
{
    private:
        string label;
    public:
        MethodTable(Class_ class_);
        void copy_parent_table(MethodTable& meth_table);
};