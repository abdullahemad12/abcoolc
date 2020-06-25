/******************************************************************************************
 * Method Environment
 * This data structure is used to store cool methods signatures in the
 * scope of a class.  The supported operations are:
 *   1. add: adds a method signature to the environment. if the signature already exists increments 
 *      the counter in the signature. 
 *   2. remove: decrements the counter of the associated method then removes the entry for the given 
 *              method name symbol from the environment if the counter is 0
 *   3. lookup: looks up the signature of a given method
 *   4. contains: returns true if there is entry for the given method in the given class
 *
 *    All the operations takes O(1) time complexity and the datastructure takes O(n)
 *    space complexity where n is the number of (Class, method) pairs added
 *
 * Implementation details:
 *   the datastructure is represented as an unordered_map of unordered_maps. The first
 *   unordered_map is indexed by the class and stores an unordered_map for each class.
 *
 *   The second unordered_map is indexed by the method's name and stores the method's
 *   signature.
 *  
 *   The method environment dont really care about the identifier names of the formals since 
 *   they are considered  part of the object environment. Instead, it cares about the types 
 *   of the identifiers in their given order in addition to the return type of the method. 
 *   Additionally the signature data structure keeps track of a counter that indicates how 
 *   many methods with the same name, class and signature were inserted into the environment. 
 *   This becomes useful especially for the local environment because a method maybe defined 
 *   multiple times. It is up to the caller to decide when a method can override an existing
 *   one, or a redefinition error should be raised.
 *****************************************************************************************/
#ifndef METHOD_ENVIRONMENT_H_
#define METHOD_ENVIRONMENT_H_


#include <stringtab.h>
#include <cool-tree.h>
#include <vector>
#include <unordered_map>

using namespace std;

class Environment;

class MethodEnvironment
{
    friend class Environment;
    public:
        class Signature 
        {
            friend class MethodEnvironment;
            friend class Environment;
            private:
                vector<Symbol> params;
                Symbol ret_type;
                int counter;
                Signature(Symbol name, vector<Symbol> params, Symbol ret_type);
            public:
                vector<Symbol> get_param_types();
                Symbol get_return_type();
        };
      private:
        unordered_map<Symbol, unordered_map<Symbol, Signature*>> env;
      
      protected:
        MethodEnvironment() { }
        ~MethodEnvironment();
        /*delete those methods to avoid unwanted errors */
        MethodEnvironment(MethodEnvironment const&) = delete;
        void operator=(MethodEnvironment const&) = delete;

        /**
          * @brief adds a method signature to the given class
          * @modifies: this 
          * @requires: (class_name, fun_name) pair not to be in the environment
          * @param Symbol the class that contains this method
          * @param name the name
          * @param params a vector of the function parameter types in order
          * @param return_type the return type of the function
          */
        void add(Symbol class_name, Symbol name, vector<Symbol> params, Symbol return_type);
        /**
          * @brief removes a method signature from a given class 
          * @modifies: this
          * @requires: method signature to be added previously to the given class 
          * @param Symbol the class name from the idtable
          * @param Symbol the method's name from the idtable
          */ 
        void remove(Symbol class_name, Symbol method_name);

        /**
          * @brief looks up a method signature in a class 
          * @param Symbol the class name from the idtable
          * @param Symbol the method's name from the idtable
          * @requires: class 'class_name' to be defined, fun_name to be defined (bug otherwise)  
          * @return the method signature, or NULL if no matching method
          * @note   DO NOT delete the method returned signature
          */   
        Signature lookup(Symbol class_name, Symbol fun_name); 

        /**
          * @brief checks if the environment contains a given method in a given class
          * @param Symbol the class name from the idtable
          * @param Symbol the method's name from the idtable
          * @requires: class 'class_name' to be defined 
          * @returns true if the method was found, false otherwise
          */
        bool contains(Symbol class_name, Symbol fun_name);


};

typedef MethodEnvironment::Signature MethodSignature;


// overload method signature equality 
bool operator==(MethodSignature& sign, method_class& meth);
bool operator!=(MethodSignature& sign, method_class& meth);


#endif /*METHOD_ENVIRONMENT_H*/