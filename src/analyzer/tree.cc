//
// See copyright.h for copyright notice and limitation of liability
// and disclaimer of warranty provisions.
//
#include "copyright.h"


///////////////////////////////////////////////////////////////////////////
//
// file: tree.cc
//
// This file defines the basic class of tree node
//
///////////////////////////////////////////////////////////////////////////

#include "tree.h"

/* line number to assign to the current node being constructed */
int node_lineno = 1;

///////////////////////////////////////////////////////////////////////////
//
// tree_node::tree_node
//
// constructor of tree node
//
///////////////////////////////////////////////////////////////////////////
tree_node::tree_node()
{
    line_number = node_lineno;
    faulty = false;
}

///////////////////////////////////////////////////////////////////////////
//
// tree_node::get_line_number
//
///////////////////////////////////////////////////////////////////////////
int tree_node::get_line_number()
{	
	return line_number;
}

//
// Set up common area from existing node
//
tree_node *tree_node::set(tree_node *t) {
   line_number = t->line_number;
   return this;
}

// this gets the class that contains this node
Class_ tree_node::get_containing_class()
{
    return containing_class;
}

// if this is true, then this node could not be 
// corrected for later stages and shall be ignored 
bool tree_node::is_faulty()
{
    return faulty;
}
