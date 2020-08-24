#include <unordered_map>
#include <vector>
#include "cool-tree.h"
#include "methods-table.h"
#include "emit.h"

auto MethodsTable::begin() { return methods_attr.begin(); }
auto MethodsTable::end() { return methods_attr.end(); }
string MethodsTable::label() { return label_attr; }
vector<method_class*> MethodsTable::methods() { return methods_attr; }
vector<method_class*> MethodsTable::self_methods() { return self_methods_attr; }

MethodsTable::MethodsTable() 
{
    label_attr = "empty";
}

MethodsTable::MethodsTable(MethodsTable& parent_method_table, Class_ class_, Features features)
{
    string class_name(class_->get_name()->get_string());
    label_attr = DISPTABLE_LABEL(class_name);
    int i;
    unordered_map<Symbol, int> map;
    
    i = 0;
    for(method_class* method : parent_method_table)
    {
        map[method->get_name()] = i++;
        methods_attr.push_back(method);
    }

    self_methods_attr = extract_methods(features);
    label_self_methods(class_name, self_methods_attr);

    for(method_class* method : self_methods_attr)
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
    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->filter_feature(methods);
    return methods;
}

void MethodsTable::label_self_methods(string class_name, vector<method_class*>& methods)
{
    for(auto meth : methods)
        meth->label = METHOD_LABEL(class_name, meth->get_name()->get_string());
}

void MethodsTable::cgen(CodeContainer& ccon)
{
    ccon.label(label());
    for(auto meth : methods_attr)
        ccon.word(meth->label);
}

