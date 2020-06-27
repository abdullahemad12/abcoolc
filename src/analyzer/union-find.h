#ifndef _UNION_FIND_
#define _UNION_FIND_

#include <cool-tree.h>
#include <unordered_map>

using namespace std;
/**
  * This class contains the implementation of a union find datastructure with the support of two main operations 
  * bool is_disjoint(int i, int j) 
  * This is mainly used to quickly check for cycles in the Abstract syntax tree
  */
   
class UnionFind
{
    private:
        unordered_map<Symbol, unsigned int> mapping;
        unsigned int n;
        unsigned int* parents; 
        unsigned int* rank;
        unsigned int find(unsigned int i);
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
    public:
        /**
          * @brief constructor for the union find 
          * @param int the number of elements in the unionfind +
          */
        UnionFind(Classes classes);
        ~UnionFind();

        /**
          * @brief checks if two components belong to the same component 
          * @requires: Symbols to be a class in the classes
          * @returns true if the two components are disjoint, false if overlapping
          * @param Symbol the first component
          * @param Symbol the second component
          */  
        bool disjoint(Symbol s1, Symbol s2);
        
        /**
          * @brief merge two components together 
          * @requires: 0 <= i, j < n
          * @modifies: this  
          * @param Symbol the first element
          * @param unsigned int the second element
          */
        void union_components(Symbol s1, Symbol s2);

};

#endif /*_UNION_FIND_*/