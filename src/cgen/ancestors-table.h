//////////////////////////////////////////////////
// AncestorsTable
// 
// Represents all the ancestors of a given class
// The format of an ancestor table in the generated 
// code is as follows 
// o The size of the table not including this (in words)
// o ancestor 1
// o .....
// o .....
// o ancestor n (parent)
// o The class itself
// Thus the ancestors table is 1 indexed
//////////////////////////////////////////////////
#ifndef ANCESTORS_TABLE_H
#define ANCESTORS_TABLE_H

#include <string>
#include <vector>
#include <iterator>
#include "cool-tree.h"



#define ANC_HEADER_SIZE    1
#define ANC_LEN_OFFSET     0

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
        unsigned int size();
        void cgen(CodeContainer& ccon, StaticMemory& stat_mem);
};

#endif /*ANCESTORS_TABLE_H*/