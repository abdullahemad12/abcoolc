/////////////////////////////////////////////////////////
// This file contains the implementation for 
// 1. get_children()
// 2. has_children()
// for all the non-abstract nodes inheriting from the AST
/////////////////////////////////////////////////////////

#include <vector>
#include "cool-tree.h"
#include "tree.h"
std::vector<tree_node*> program_class::get_children()
{
    std::vector<tree_node*> children;
    int n = classes->len();
    for(int i = 0; i < n; i++)
        children.push_back(classes->nth(i)); 
    return children;
}
std::vector<tree_node*> class__class::get_children()
{
    std::vector<tree_node*> children;
    int n = features->len();
    for(int i = 0; i < n; i++)
        children.push_back(features->nth(i));
    return children;
}
std::vector<tree_node*> method_class::get_children()
{
    std::vector<tree_node*> children;
    int n = formals->len();
    for(int i = 0; i < n; i++)
        children.push_back(formals->nth(i));
    children.push_back(expr);
    return children;
}
std::vector<tree_node*> attr_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(init);
    return children;
}
std::vector<tree_node*> formal_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> assign_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(expr);
    return children;
}
std::vector<tree_node*> static_dispatch_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(expr);
    int n = actual->len();
    for(int i = 0; i < n; i++)
        children.push_back(actual->nth(i));
    return children;
}
std::vector<tree_node*> dispatch_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(expr);
    int n = actual->len();
    for(int i = 0; i < n; i++)
        children.push_back(actual->nth(i));
    return children;
}
std::vector<tree_node*> cond_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(pred);
    children.push_back(then_exp);
    children.push_back(else_exp);
    return children;
}
std::vector<tree_node*> loop_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(pred);
    children.push_back(body);
    return children;
}
std::vector<tree_node*> typcase_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(expr);
    int n = cases->len();
    for(int i = 0; i < n; i++)
        children.push_back(cases->nth(i));
    return children;
}
std::vector<tree_node*> branch_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(expr);
    return children;
}
std::vector<tree_node*> block_class::get_children()
{
    std::vector<tree_node*> children;
    int n = body->len();
    for(int i = 0; i < n; i++)
        children.push_back(body->nth(i));
    return children;
}
std::vector<tree_node*> let_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(init);
    children.push_back(body);
    return children;
}
std::vector<tree_node*> plus_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> sub_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> mul_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> divide_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> neg_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    return children;
}
std::vector<tree_node*> lt_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> eq_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> leq_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    children.push_back(e2);
    return children;
}
std::vector<tree_node*> comp_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    return children;
}
std::vector<tree_node*> int_const_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> bool_const_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> string_const_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> new__class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> isvoid_class::get_children()
{
    std::vector<tree_node*> children;
    children.push_back(e1);
    return children;
}
std::vector<tree_node*> no_expr_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
std::vector<tree_node*> object_class::get_children()
{
    std::vector<tree_node*> children;

    return children;
}
