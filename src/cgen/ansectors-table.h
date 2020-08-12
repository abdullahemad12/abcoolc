///////////////////////////////////////////////
// AncestorsTable
// 
// Represents the ancestors of a given class
///////////////////////////////////////////////
#ifndef ANCESTORS_TABLE_H
#define ANCESTORS_TABLE_H

#include <string>
#include "cool-tree.h"

using namespace std;
class AncestorsTable 
{
    private: 
        string label;
    public:
        AncestorsTable(Class_ parent_table);
        void copy_parent_table(AncestorsTable& meth_table);

};

#endif /*ANCESTORS_TABLE_H*/