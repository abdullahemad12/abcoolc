#include <unordered_map>
#include "cool-tree.h"
#include "basic-symbols.h"

using namespace std;


void program_class::create_inheritance_graph()
{
    int n;
    Class_ class_;
    unordered_map<Symbol, Class_> classes_map;
    n = classes->len();

    for(int i = 0; i < n; i++)
    {
        class_ = classes->nth(i);
        classes_map[class_->get_name()] = class_;
    }

    for(int i = 0; i < n; i++)
    {
        class_ = classes->nth(i);
        if(class_->get_parent() != NULL)
            classes_map[class_->get_parent()]->add_child_class(class_);
    }
       
}
void class__class::add_child_class(Class_ class_)
{
    children_classes.push_back(class_);
}
