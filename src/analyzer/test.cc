#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include <iostream>
#include "catch.hpp"

#include "cool-tree.h"
#include "class-tree.h"
#include <cstdlib>
#include <string>
#include <utility>

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
string gen_random(const int len) {
    string str = "";
    str.reserve(len+1);
    
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        str += (alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    return str;
}

char* const_to_var_charptr(const char* in, const int len) {
    char* out = new char[len + 1];
    strcpy(out, in);
    return out;
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
int random(int min, int max) {
    return min + (rand() % (max - min + 1));
}

TEST_CASE("Object Environment") {
    int t = 1000;
    int n_names = 100;
    vector<pair<Symbol, Symbol>> identifiers;
    vector<Symbol> names;
    vector<Symbol> types;
    for(int i = 0; i < n_names; i++) {
        string tmp = gen_random(i + 10).c_str();
        char* namestr = const_to_var_charptr(tmp.c_str(), tmp.length());
        Symbol name = idtable.add_string(namestr);
        delete[] namestr;
        names.push_back(name);
        
        tmp = gen_random(i + 10).c_str();
        char* typestr = const_to_var_charptr(tmp.c_str(), tmp.length());
        Symbol type = idtable.add_string(typestr);
        delete[] typestr;
        types.push_back(type);
    }
    ObjectEnvironement objenv;
    for(int i = 0; i < t; i++) {
        int rand1 = random(0, names.size());
        int rand2 = random(0, types.size());
        pair<Symbol, Symbol> p(names[rand1], types[rand2]);
        identifiers.push_back(p);
        objenv.add(p.first, p.second);
    }
    for(pair<Symbol, Symbol> id : identifiers) {
        REQUIRE(objenv.contains(id.first));
    }

    for(int i = identifiers.size() - 1; i >= 0; i--) {
        REQUIRE(objenv.lookup(identifiers[i].first) == identifiers[i].second);
        objenv.remove(identifiers[i].first);
    }

    for(pair<Symbol, Symbol> id : identifiers) {
        REQUIRE(!objenv.contains(id.first));
        REQUIRE(objenv.lookup(id.first) == NULL);
    }

}
