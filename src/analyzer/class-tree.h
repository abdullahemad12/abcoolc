#ifndef CLASS_TREE_H_
#define CLASS_TREE_H_

#include <cool-tree.h>
#include <exceptions.h>
#include <method-environment.h>
#include <object-environment.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>


// MACRO to calculate the node with minimum depth
#define MIN_DEPTH_NODE(ln, rn) ((ln->get_depth())<(rn->get_depth()))?(ln):(rn)

// prototypes
class SegmentTree;

/**
  * This class contains the implementation of a union find datastructure with the support of two main operations 
  * bool is_disjoint(int i, int j) 
  * This is mainly used to quickly check for cycles in the Abstract syntax tree
  */
   
class UnionFind
{
    private:
        unsigned int n;
        unsigned int* parents; 
        unsigned int* rank;
        unsigned int find(unsigned int i);
    public:
        /**
          * EFFECTS: constructor for the union find 
          * PARAMETERS: 
          * - int n: the number of elements in the unionfind +
          */
        UnionFind(unsigned int n);
        ~UnionFind();
        
        /**
          * EFFECTS: checks if two components belong to the same component 
          * REQUIRES: 0 <= i, j < n
          * RETURNS: true if the two components are disjoint, false if overlapping
          * PARAMETERS: 
          *  - int i: the first component
          *  - int j: the second component
          */  
        bool disjoint(unsigned int i, unsigned int j);
        
        /**
          * EFFECTS: merge two components together 
          * REQUIRES: 0 <= i, j < n
          * MODIFIES: this 
          * PARAMETERS: 
          * - int i: the first element
          * - int j: the second element
          */
        void union_components(unsigned int i, unsigned int j); 

};


/**
  * Main class that represents the CLASS tree of the program
  */ 
class ClassTree
{
    /**
      * Represents a Node in the CLASS tree
      * Holds extra information other than class_ class
      */
     public: 
        class Node
        {
            private:
                Class_ class_obj;
                unsigned int depth;
                std::vector<Class_> children;
            public:
                Node(Class_ class_obj, unsigned int depth) : 
                class_obj(class_obj), depth(depth) {};
                Class_ get_class() { return class_obj; }
                unsigned int get_depth() { return depth; }
                void add_child(Class_ child) { children.push_back(child); }
        };
     private:
        std::unordered_set<Symbol> classes;
        Node* root; 
        // the first occurance in an euler walk
        std::unordered_map<Symbol, unsigned int> eurler_first;
        SegmentTree* lubtree;

        // private functions
        /*does not return any thing but might throw a fatal exception*/
        void check_for_invalid_inheritance(void);
        void check_for_redefinitions(void);
        void construct_graph(Classes classes);
        void check_for_cycles(void);
        void install_basic_classes(void);
        ClassTree::Node** euler_walk(void);
        void compute_first_occurance(ClassTree::Node** euler_array);
        void analyze_dfs_helper(Node* node, std::vector<SemantException*>& err_container, 
                                MethodEnvironment& global_env, 
                                std::pair<ObjectEnvironement, MethodEnvironment>& local_env);

        public:
          /**
            * EFFECTS: least upper bound (lub) operation as defined in the manual
            *          basically, it calculates the Least common ancestor of the 
            *          given two classes
            * REQUIRES: the given two classes to be defined in the ClassTree
            * PARAMETERS:
            *  1. Symbol type1: the first class symbol from idtable
            *  2. Symbol type2: the second class symbol from idtable
            * RETURNS:
            *  the LUB of these two classes
            */
          Symbol lub(Symbol type1, Symbol type2);

          /**
           * EFFECTS: performs semantic analysis on all the classes in the program
           * REQUIRES: correct initialization of the trees
           * RETURNS: a vector of exceptions thrown due to semantic errors.
           * POSTCONDITIONS: the SemantExcpetions must be deleted to avoid leaks
           */ 
          std::vector<SemantException*> analyze();

          ClassTree(Classes classes);
          ~ClassTree();



        
                  
};

/**
  * segment_tree class 
  * used to query the minimum by the class tree
  * for calculating the LCA (LUB operation). As I am not expecting to use
  * it for something else in this project, it only stores Vector<Node*>
  * Also there is no need for insertion as the size of the tree is fixed,
  * so this will only support range queries
  */
  
class SegmentTree
{
    private:
        unsigned int n; // the number of nodes in the tree 
        ClassTree::Node** tree;
        /**
          * Helper for the query function
          * EFFECTS: recursively calculates the minimum in the given range l-r (inclusive)
          * REQUIRES: range to be within the size of the of the array. No exceptions thrown
          * PARAMETERS: 
          *  - int curnode: the current node being processed in the tree 
          *  - int l: the left index of the range being queried 
          *  - int r: the right index of the range being queried
          *  - int tl: the left index of the range curnode represents
          *  - int tr: the right index of the range curnode represents 
          *  RETURNS:
          *  - the node with the minimum depth in the range
          */ 
        ClassTree::Node* query(unsigned int curnode, unsigned int l, 
        			      unsigned int r, unsigned int tl, unsigned int tr);
        
        /**
          * called from the constructor to construct the tree
          * EFFECTS: constructs the segment tree from the nodes vector
          * MODIFIES: this->tree
          * REQUIRES: nodes to be set correctly and tree array to be intialized
          * PARAMETERS: 
          * - int curnode: the current node in segment tree being processed 
          * - int l: the left range of the current node
          * - int r: the right range of the current node
          */
        void construct_tree(std::vector<ClassTree::Node*> nodes, unsigned int curnode, 
        		    unsigned int l, unsigned int r);
    public:
        SegmentTree(std::vector<ClassTree::Node*> nodes);
        ~SegmentTree(); // node pointers wont be deleted
        
        /**
          * EFFECTS: calculates the node with minimum depth in the given range
          * REQUIRES: range to be within the size of the array. No exceptions thrown
          * PARAMETERS: 
          * - int curnode: the current node being processed in the tree
          * - int l: the left index of the range being queried
          * - int r: the right index of the range being queried
          * RETURNS:
          * - the node with the minimum depth in the range
          */ 
        ClassTree::Node* query(unsigned int l, unsigned int r);
        
};

#endif /*CLASS_TREE_H*/
