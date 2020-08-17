#include <string>
#include "ancestors-table.h"
#include "labels.h"

using namespace std;

string AncestorsTable::label() { return label_attr; }
auto AncestorsTable::begin() { return ancestors_attr.begin(); } 
auto AncestorsTable::end() { return ancestors_attr.end(); }

AncestorsTable::AncestorsTable(AncestorsTable& parent_table, Class_ myself)
{
    string class_name(myself->get_name()->get_string());
    label_attr = ANCESTORS_TABLE_LABEL(class_name);

    for(auto ancestor : parent_table)
        ancestors_attr.push_back(ancestor);
    ancestors_attr.push_back(myself);
}

AncestorsTable::AncestorsTable()
{
    label_attr = "empty_ancestor";
}