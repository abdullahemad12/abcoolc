#include "ancestors-table.h"
#include <string>

using namespace std;

string AncestorsTable::label() { return alabel; }
auto AncestorsTable::begin() { return ancestors.begin(); } 
auto AncestorsTable::end() { return ancestors.end(); }

AncestorsTable::AncestorsTable(AncestorsTable& parent_table, Class_ myself)
{
    string class_name(myself->get_name()->get_string());
    alabel = class_name + "." + "Ancestors";

    for(auto ancestor : parent_table)
        ancestors.push_back(ancestor);
    ancestors.push_back(myself);
}
