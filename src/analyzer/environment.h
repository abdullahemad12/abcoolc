#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H
/******************************************************************************************
 * This singleton class acts as the environment for the current program                   *
 * being analyzed it stores the three environments mentioned in the                       *
 * manual with a small caveat. There is a local and global environments                   *
 * the local environments are to be modified according to the scope we are                *
 * currently in. This includes the features in the current class and its parents.         *
 * All the features in this environment are reference by the dummy class 'localtype'.     *
 * On the otherhand, the global environment stores all the methods defined throughout     *
 * the program and binds them to the class at which they are defined. The order at which  *
 * Features are inserted and deleted is left for the program node and the class nodes     *
 ******************************************************************************************/
#include <method-environment.h>
#include <object-environment.h>
#include <symtab.h>
#include <vector>

using namespace std;

class Environment
{
        /*delete those methods to avoid unwanted errors */
        Environment(Environment const&) = delete;
        void operator=(Environment const&) = delete;
    private:
        ObjectEnvironment object_env;
        MethodEnvironment method_env;

    public:
        Environment();
        ~Environment() { }
        Symbol current_class;
        void add_object(Symbol name, Symbol type);
        void add_method(Symbol class_,  method_class* method);
        void remove_object(Symbol name);
        void remove_method(Symbol class_name, Symbol method_name);
        bool contains_object(Symbol name);
        bool contains_method(Symbol class_name, Symbol name);
        Symbol lookup_object(Symbol name);
        MethodSignature lookup_method(Symbol class_name, Symbol name);
        /** 
          * @brief adds all the methods from the base to the derived class
          * MODIFIES: this 
          * @param Symbol the derived class
          * @param Symbol the base class
          */ 
        void sync_inherited_methods(Symbol derived, Symbol base);
};
#endif /*_ENVIRONMENT_H*/