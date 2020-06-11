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

#include <stringtab.h>
#include <cool-tree.h>
#include <vector>
#include <unordered_map>

/*class prototypes*/
class method_environment;
class method_environment::signature;

/*overloading comparison operators*/
extern  bool operator==(method_environment::signature& arg1, method_environment::signature& arg2);
extern  bool operator!=(method_environment::signature& arg1, method_environment::signature& arg2);


class method_environment
{
    private:
        std::unordered_map<Symbol, std::unordered_map<Symbol, Symbol>> env;
    public:
        class signature 
        {
            private:
                std::vector<Symbol> params;
                Symbol ret_type;
                signature(Formals formals, Symbol ret_type);
            public:
                std::vector<Symbol> get_params();
                Symbol get_return_type();
        };

        /**
          * EFFECTS: adds a method signature to the given class
          * MODIFIES: this 
          * REQUIRES: (class_name, fun_name) pair not to be in the environment
          * PARAMETERS: 
          *  - Symbol class_name: the class name from the idtable
          *  - Symbol fun_name: the method's name from the idtable
          *  - Formals formal: the methods parameters 
          *  - Symbol ret_type: the return type of the method
          */
        void add(Symbol class_name, Symbol fun_name, Formals formal, Symbol ret_type);
        /**
          * EFFECTS: removes a method signature from a given class 
          * MODIFIES: this
          * REQUIRES: method signature to be added previously to the given class 
          * PARAMETERS: 
          *  - Symbol class_name: the class name from the idtable
          *  - Symbol fun_name: the method's name from the idtable
          */ 
        void remove(Symbol class_name, Symbol fun_name);

        /**
          * EFFECTS: looks up a method signature in a class 
          * PARAMETERS: 
          *  - Symbol class_name: the class name from the idtable
          *  - Symbol fun_name: the method's name from the idtable
          * RETURNS: the method signature, or NULL if no matching method
          */   
        signature& lookup(Symbol class_name, Symbol fun_name);

        /**
          * EFFECTS: checks if the environment contains a given method 
          *          in a given class
          * PARAMETERS:
          *  - Symbol class_name: the class name from the idtable
          *  - Symbol fun_name: the method's name from the idtable
          * RETURNS: true if the method was found, false otherwise
          */
        bool contains(Symbol class_name, Symbol fun_name);
};