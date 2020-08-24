//////////////////////////////////////////////////
// AncestorsTable
// 
// Represents all the ancestors of a given class
//////////////////////////////////////////////////
#ifndef ANCESTORS_TABLE_H
#define ANCESTORS_TABLE_H

#include <string>
#include <vector>
#include <iterator>
#include "cool-tree.h"


using namespace std;

class StaticMemory;
class CodeContainer;

class AncestorsTable 
{
    private:
        string label_attr;
        vector<Class_> ancestors_attr;
    public:
        AncestorsTable();
        /**
          * @param AncestorsTable the ancestors table of the parent
          * @param myself the class that this ancestors table belongs to
          */ 
        AncestorsTable(AncestorsTable& parent_table, Class_ myself);
        string label();
        auto begin();
        auto end();
        void cgen(CodeContainer& ccon, StaticMemory& stat_mem);
};

#endif /*ANCESTORS_TABLE_H*/