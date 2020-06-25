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
    protected:
        Environment() { }
        ~Environment() { }
        /*delete those methods to avoid unwanted errors */
        Environment(Environment const&) = delete;
        void operator=(Environment const&) = delete;


    private:
        MethodEnvironment local_method_env;
        ObjectEnvironment local_object_env;
        MethodEnvironment global_method_env;
        Symbol resolve_type(Symbol type);
        void resolve_signature_type(MethodSignature& sign);
    public:
        Symbol current_class;
        void add_local(Symbol name, Symbol type);
        void add_local(Symbol class_name, Symbol name, vector<Symbol> formals, Symbol return_type);
        void add_global(Symbol class_name, Symbol name, vector<Symbol> formals, Symbol return_type);
        void remove_local_method(Symbol class_name, Symbol name);
        void remove_global_method(Symbol class_name, Symbol name);
        void remove_local_object(Symbol name);
        bool contains_local_object(Symbol name);
        bool contains_local_method(Symbol class_name, Symbol name);
        bool contains_global_method(Symbol class_name, Symbol name);
        Symbol lookup_local_object(Symbol name);
        MethodEnvironment::Signature lookup_local_method(Symbol class_name, Symbol name);
        MethodEnvironment::Signature lookup_global_method(Symbol class_name, Symbol name);

        /**
         * References: https://stackoverflow.com/a/30687399/6548856
         */
        static Environment& instance()
        {
            static Environment t;
            return t;
        }
        
};
#endif /*_ENVIRONMENT_H*/