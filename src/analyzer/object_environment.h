/*****************************************************************************************************
 *  Object Environment
 *
 *  This data structure is used to store all the  identifiers in the current scope.
 *  The data structure works in FIFO order.
 *  The supported operations are:
 *
 *    1. add: adds an identifier and it's type to the environment. An identifier can
 *            be added mutliple times and all the of the add operations type are recorded
 *            in FIFO order.
 *    2. remove: removes the last added entry from the environment.
 *    3. lookup: looks up the type of a given identifier and returns the most recently added
 *               type
 *    4. contains: returns true if there is at least one entry that matching the given identifier
 *
 *    All the operations takes O(1) time complexity and the datastructure takes O(n) space complexity
 *    where n is the number of (identifier, type) pairs added
 *
 * Implementation details:
 *  the data structure is basically an undordered_map of stacks. The unordered_map is indexed by the
 *  identifier and each identifier has its own stack of types. because we want to give precendence
 *  to the type that was inserted recently, I used a stack due to its FIFO nature.
 *
 *  On add operations if the  identifier does not exist, a new entry is added to the map and the type
 *  is pushed onto the stack.
 *
 *  on the remove operation, the item is popped from the stack and if the stack becomes empty
 *  after the the pop, the entry is removed from the map. Note for every pop there must be a
 *  previous push, since the pop operation is generated by the compiler. If a pop operation
 *  happened on an empty stack or nonexisting entry than I am certainly doing something wrong.
 *  I am using the stack and hashtable from the std c++ library
 ****************************************************************************************************/
# include <stringtab.h>
# include <unordered_map>
# include <stack>


class object_environement {
    private:
        std::unordered_map<Symbol, std::stack<Symbol>> env;
    
    public:

    /**
      * EFFECTS: adds a (identifier, type) pair to the environment 
      * MODIFIES: this 
      * PARAMETERS:
      * - Symbol id: the identifier symbol from idtable
      * - Symbol type: type of the identifier from idtable
     */ 
    void add(Symbol id, Symbol type);

    /**
      * EFFECTS: removes one (identifier, type) entry from the environment
      *          in FIFO order
      * MODIFIES: this
      * PARAMETERS:
      *  - Symbol id: the identifier symbol from the idtable 
      */
    void remove(Symbol id);

    /**
      * EFFECTS: looks up the type from the symbol table by id. if the 
      *          same id has more than one type, the most recently
      *          added one is returned.
      * PARAMETERS: 
      *  - Symbol id: the identifier symbol from the idtable 
      * RETURNS: the most recently added type symbol, or NULL if no 
      *          entry for identifier was found
      */ 
    Symbol lookup(Symbol id);

    /**
      * EFFECTS: checks if the there exists at least one entry
      *          for the given identifier
      * PARAMETERS: 
      *  - Symbol id: the identifier symbol from the idtable 
      * RETURNS: true if at least one entry was found
      */
     bool contains(Symbol id);

};