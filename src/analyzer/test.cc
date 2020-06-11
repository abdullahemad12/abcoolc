#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include <iostream>
#include "catch.hpp"

#include "cool-tree.h"
#include "class-tree.h"
#include <cstdlib>

extern Program ast_root;      // root of the abstract syntax tree
FILE *ast_file = stdin;       // we read the AST from standard input
extern int ast_yyparse(void); // entry point to the AST parser

int cool_yydebug;     // not used, but needed to link with handle_flags
char *curr_filename;

void handle_flags(int argc, char *argv[]);

using namespace std;

vector<ClassTree::Node*> generate_random_nodes(long n)
{
    vector<ClassTree::Node*> vec;
    
    for(int i = 0; i < n; i++)
    {
        ClassTree::Node* node = new ClassTree::Node(NULL, random() % 1000000);
        vec.push_back(node);
    }
    
    return vec;
}

ClassTree::Node* get_min_in_range(vector<ClassTree::Node*> vec, int start, int end)
{
    ClassTree::Node* min = vec[start];
    for(int i = start + 1; i <= end; i++)
    {
        if(vec[i]->get_depth() < min->get_depth()) 
        {
            min = vec[i];
        }
    }
    return min;
}


TEST_CASE( "Insert and Query of Segment Tree", "[segment_tree]" ) {
	vector<ClassTree::Node*> nodes = generate_random_nodes(500);
	SegmentTree seg(nodes);
	// query all the possible ranges
	for(unsigned int i = 0; i < nodes.size(); i++)
	{
	    for(unsigned int j = i; j < nodes.size(); j++)
	    {
	        REQUIRE((seg.query(i, j) == get_min_in_range(nodes, i, j)));
	    }
	}
	
	for(unsigned int i = 0; i < nodes.size(); i++)
	{
	    ClassTree::Node* node = nodes.back();
	    nodes.pop_back();
	    delete node;
	}
}
