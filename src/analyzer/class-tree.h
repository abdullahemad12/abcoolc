#ifndef CLASS_TREE_H_
#define CLASS_TREE_H_

#include <cool-tree.h>
#include <unordered_map>
#include <vector>


// MACRO to calculate the node with minimum depth
#define MIN_DEPTH_NODE(ln, rn) ((ln->get_depth())<(rn->get_depth()))?(ln):(rn)


/**
  * This class contains the implementation of a union find datastructure with the support of two main operations 
  * bool is_disjoint(int i, int j) 
  * This is mainly used to quickly check for cycles in the Abstract syntax tree
  */
   
class union_find
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
        union_find(unsigned int n);
        ~union_find();
        
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
class class_tree
{
    /**
      * Represents a Node in the CLASS tree
      * Holds extra information other than class_ class
      */
     public: 
        class node
        {
            private:
                Class_ class_obj;
                unsigned int depth;
                std::vector<Class_> children;
            public:
                node(Class_ class_obj, unsigned int depth) : 
                class_obj(class_obj), depth(depth) {};
                Class_ get_class() { return class_obj; }
                unsigned int get_depth() { return depth; }
                void add_child(Class_ child) { children.push_back(child); }
        };
     private:
        Classes classes;
        std::unordered_map<Class_, int> classes_ids;
        std::vector<std::vector<int>> tree; // I use this representation because the inheritence tree 
                                   // is of fixed size
                               
        std::vector<node*> euler_vector; // constructed using euler walk and used for LCA calculation 
        std::vector<int> first_euler_vector; // used to keep track of the index of the first occurance of nodes
};

/**
  * segment_tree class 
  * used to query the minimum by the class tree
  * for calculating the LCA (LUB operation). As I am not expecting to use
  * it for something else in this project, it only stores Vector<Node*>
  * Also there is no need for insertion as the size of the tree is fixed,
  * so this will only support range queries
  */
  
class lub_tree
{
    private:
        unsigned int n; // the number of nodes in the tree 
        class_tree::node** tree;
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
        class_tree::node* query(unsigned int curnode, unsigned int l, 
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
        void construct_tree(std::vector<class_tree::node*> nodes, unsigned int curnode, 
        		    unsigned int l, unsigned int r);
    public:
        lub_tree(std::vector<class_tree::node*> nodes);
        ~lub_tree(); // node pointers wont be deleted
        
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
        class_tree::node* query(unsigned int l, unsigned int r);
        
};

#endif /*CLASS_TREE_H*/
