/******************************************************************************************
 * Method Environment
 * This data structure is used to store cool methods signatures in the
 * scope of a class.  The supported operations are:
 *   1. add: adds a method signature to the environment. if the signature already exists
 *           does nothig.
 *   2. remove: removes the entry for the given method name symbol from the environment
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
 *****************************************************************************************/
#ifndef METHOD_ENVIRONMENT_H_
#define METHOD_ENVIRONMENT_H_


#include <stringtab.h>
#include <cool-tree.h>
#include <vector>
#include <unordered_map>


using namespace std;

class MethodEnvironment
{
    public:
        class Signature 
        {
            friend class MethodEnvironment;
            private:
                vector<Symbol> params;
                Symbol ret_type;
                Signature(Symbol name, vector<Symbol> params, Symbol ret_type);
            public:
                vector<Symbol> get_param_types();
                Symbol get_return_type();
        };
      private:
        unordered_map<Symbol, unordered_map<Symbol, Signature*>> env;
        
      public:
        /*destructor*/
        ~MethodEnvironment();

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
        Signature& lookup(Symbol class_name, Symbol fun_name); 

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


#endif /*METHOD_ENVIRONMENT_H*/