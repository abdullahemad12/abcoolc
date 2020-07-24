#include <class-visitor.h>
#include <type-table.h>
#include <environment.h>
#include <class-tree.h>
void TypeClassVisitor::visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    if(!type_table.is_built_in_type(class_->get_name()))
        class_->type_check(class_tree, type_table, env);
}

void TypeClassVisitor::on_enter(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    class_->sync_local_env(env);
}

void TypeClassVisitor::on_exit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    class_->clean_local_env(env);
}


void SyncMethodEnvironmentVisitor::on_enter(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void SyncMethodEnvironmentVisitor::on_exit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{

}

void SyncMethodEnvironmentVisitor::visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env)
{
    class_->sync_global_env(env);
}

