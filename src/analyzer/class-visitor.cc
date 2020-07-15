#include <class-visitor.h>
#include <type-table.h>
#include <environment.h>
#include <class-tree.h>
void TypeClassVisitor::visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    class_->type_check(class_tree, type_table, env);
}

void ScopeClassVisitor::visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    class_->scope_check(class_tree, type_table, env);
}