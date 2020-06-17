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
#include <singleton.h>

using namespace std;

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
          * @brief constructor for the union find 
          * @param int the number of elements in the unionfind +
          */
        UnionFind(unsigned int n);
        ~UnionFind();
        
        /**
          * @brief checks if two components belong to the same component 
          * @requires: 0 <= i, j < n
          * @returns true if the two components are disjoint, false if overlapping
          * @param int the first component
          * @param int the second component
          */  
        bool disjoint(unsigned int i, unsigned int j);
        
        /**
          * @brief merge two components together 
          * @requires: 0 <= i, j < n
          * @modifies: this  
          * @param unsigned int the first element
          * @param unsigned int the second element
          */
        void union_components(unsigned int i, unsigned int j); 

};


/**
  * Main class that represents the CLASS tree of the program
  */ 
class ClassTree : public Singleton<ClassTree>
{
    friend Singleton<ClassTree>;
    /**
      * Represents a Node in the CLASS tree
      * Holds extra information other than class_ class
      */
     public: 
        class Node
        {
            private:
                Symbol class_symbol;
                unsigned int depth;
                vector<Node*> children;
            public:
                Node(Symbol class_symbol) : 
                class_symbol(class_symbol){};
                Symbol get_class() { return class_symbol; }
                unsigned int get_depth() { return depth; }
                void add_child(Node* child) { children.push_back(child); }
                void euler_walk(vector<Symbol>& vector, unsigned int depth);
        };
     private:
        Node* root; 
        // the first occurance in an euler walk
        unordered_map<Symbol, unsigned int> eurler_first;
        SegmentTree* lubtree;
        vector<Symbol> euler_trip;

        // just used to catch errors 
        bool is_init = false;

        // private functions
        /*does not return any thing but might throw a fatal exception*/
        void construct_graph(Classes classes);
        void check_for_cycles(void);
        void compute_first_occurance(ClassTree::Node** euler_array);
        ClassTree() { }

      public:
        /**
          * @brief least upper bound (lub) operation as defined in the manual
          *          basically, it calculates the Least common ancestor of the 
          *          given two classes
          * @requires: the given two classes to be defined in the ClassTree
          * @param Symbol the first class symbol from idtable
          * @param Symbol the second class symbol from idtable
          * @returns: the least upper bound of these two classes
          */
        Symbol lub(Symbol type1, Symbol type2);

        /**
          * @brief gets the euler trip of the nodes
          * @requires: class tree to be initialized
          * @returns the euler trip as a vector
          */ 
        vector<Symbol> get_euler_trip();

        /**
          * @brief creates the graph using the given classes
          * @requires: classtable to be initialized 
          * @modifies: this
          * @param Classes the classes in the program + basic classes
          */ 
        void init(Classes classes);
        
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
          * @brief recursively calculates the minimum in the given range l-r (inclusive)
          * @requires: range to be within the size of the of the array. No exceptions thrown 
          * @param int the current node being processed in the tree 
          * @param int the left index of the range being queried 
          * @param int the right index of the range being queried
          * @param int the left index of the range curnode represents
          * @param int the right index of the range curnode represents 
          * @returns the node with the minimum depth in the range
          */ 
        ClassTree::Node* query(unsigned int curnode, unsigned int l, 
        			      unsigned int r, unsigned int tl, unsigned int tr);
        
        /**
          * called from the constructor to construct the tree
          * @brief constructs the segment tree from the nodes vector
          * @modifies: this
          * @requires: nodes to be set correctly and tree array to be intialized 
          * @param curnode: the current node in segment tree being processed 
          * @param l the left range of the current node
          * @param r the right range of the current node
          */
        void construct_tree(vector<ClassTree::Node*> nodes, unsigned int curnode, 
        		    unsigned int l, unsigned int r);
    public:
        SegmentTree(vector<ClassTree::Node*> nodes);
        ~SegmentTree(); // node pointers wont be deleted
        
        /**
          * @brief calculates the node with minimum depth in the given range
          * @requires: range to be within the size of the array. No exceptions thrown
          * @param int the current node being processed in the tree
          * @param int the left index of the range being queried
          * @param r the right index of the range being queried
          * @returns the node with the minimum depth in the range
          */ 
        ClassTree::Node* query(unsigned int l, unsigned int r);
        
};

#endif /*CLASS_TREE_H*/
