///////////////////////////////////////////////////////////////////
// This class contains visitors for the class nodes
// For the semantic checks, classes are visited in an 
// euler walk fashion. While this works fine and efficiently 
// as each class is only visited once, it introduces a bit of 
// complexity into the code. Hence, to refactor the algorithm 
// that does the euler walk on the classes from the program node 
// I need to some how call the function that corresponds to 
// semantic phase being executed currently. These classes solve 
// this problem 
////////////////////////////////////////////////////////////////////
#ifndef CLASS_VISITOR_H_
#define CLASS_VISITOR_H_

#include <cool-tree.h>

class ClassVisitor
{
    public:
        /**
          * @brief executes before any child is visited
          */ 
        virtual void visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env) = 0;
        /**
          * @brief The first thing to be executed
          */ 
        virtual void on_enter(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env) = 0;
        
        /**
          * @brief before returning from the visit on the given node
          */ 
        virtual void on_exit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env) = 0;


};


class TypeClassVisitor : public ClassVisitor 
{
    public:
        void visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
        void on_enter(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
        void on_exit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
};

class SyncMethodEnvironmentVisitor : public ClassVisitor
{
    public:
        void visit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
        void on_enter(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
        void on_exit(Class_ class_, ClassTree& class_tree, TypeTable& type_table, Environment& env);
};


#endif /*_CLASS_VISITOR_*/