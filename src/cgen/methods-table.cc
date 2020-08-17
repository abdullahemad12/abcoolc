#include <unordered_map>
#include <vector>
#include "cool-tree.h"
#include "methods-table.h"

auto MethodsTable::begin() { return methods_attr.begin(); }
auto MethodsTable::end() { return methods_attr.end(); }
string MethodsTable::label() { return label_attr; }
vector<method_class*> MethodsTable::methods() { return methods_attr; }


MethodsTable::MethodsTable() 
{
    label_attr = "empty";
}

MethodsTable::MethodsTable(MethodsTable& parent_method_table, Class_ class_, Features features)
{
    int i;
    unordered_map<Symbol, int> map;
    
    i = 0;
    for(method_class* method : parent_method_table)
    {
        map[method->get_name()] = i++;
        methods_attr.push_back(method);
    }

    vector<method_class*> self_methods = extract_methods(features);
    
    for(method_class* method : self_methods)
    {
        if(map.find(method->get_name()) != map.end())
        {
            methods_attr[map[method->get_name()]] = method;
        }
        else
        {
            methods_attr.push_back(method);
        }
    }
}

vector<method_class*> MethodsTable::extract_methods(Features features)
{
    vector<method_class*> methods;
    int n = 0;
    for(int i = 0; i < n; i++)
        features->nth(i)->filter_feature(methods);
    return methods;
}
