#include <tree.h>
#include <cool-tree.h>
#include <vector>

using namespace std;

void program_class::propagate_containing_class(Class_ class_)
{
    vector<tree_node*> children = get_children();
    containing_class = class_;
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}

void class__class::propagate_containing_class(Class_ class_)
{
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(this);
}

void method_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void attr_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void formal_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void assign_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void static_dispatch_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void dispatch_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void cond_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void loop_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void typcase_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void branch_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void block_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void let_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void plus_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void sub_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void mul_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void divide_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void neg_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void lt_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void eq_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void leq_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void comp_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void int_const_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void bool_const_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void string_const_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void new__class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void isvoid_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void no_expr_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
void object_class::propagate_containing_class(Class_ class_)
{
    containing_class = class_;
    vector<tree_node*> children = get_children();
    for(tree_node* child : children)
        child->propagate_containing_class(class_);
}
