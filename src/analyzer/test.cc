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

/*************************************************
 *  Helper functions
 * ***********************************************/
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
void gen_random(char* str, const int len) 
{    
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        str[i] = (alphanum[rand() % (sizeof(alphanum) - 1)]);
    }
    str[len] = '\0';
}

char* const_to_var_charptr(const char* in, const int len) 
{
    char* out = new char[len + 1];
    strcpy(out, in);
    return out;
}
int random(int min, int max) 
{
    return min + (rand() % (max - min + 1));
}

/*************************************************************************************/
/*************************************Tests*******************************************/
/*************************************************************************************/
TEST_CASE( "Insert and Query of Segment Tree", "[segment_tree]" ) 
{
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


TEST_CASE("Object Environment") {
    int t = 1000;
    int n_names = 100;
    vector<pair<Symbol, Symbol>> identifiers;
    vector<Symbol> names;
    vector<Symbol> types;
    for(int i = 0; i < n_names; i++) {
        char namestr[i+10+1];
        gen_random(namestr, i + 10);
        Symbol name = idtable.add_string(namestr);
        names.push_back(name);
        
        char typestr[i+10+1];
        gen_random(namestr, i + 10);
        Symbol type = idtable.add_string(typestr);
        types.push_back(type);
    }
    ObjectEnvironment objenv;
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
    }

}


TEST_CASE("Method Environment") 
{

    const int n_classes = 10;
    const int n_names = 100;
    const int n_methods = 10000;
    vector<Symbol> classes;
    vector<Symbol> classes_of_ith_method;
    vector<Symbol> ret_type_of_ith_method;
    vector<pair<Symbol, vector<Symbol>>> methods;
    vector<Symbol> names;
    Formals types;

    for(int i = 0; i < n_classes; i++) 
    {
        char namestr[i+10+1];
        gen_random(namestr, i + 10);
        Symbol name = idtable.add_string(namestr);
        classes.push_back(name);
    }
    MethodEnvironment env;
    for(int i = 0; i < n_names; i++) 
    {
        char namestr[i+10+1];
        gen_random(namestr, i + 10);
        Symbol name = idtable.add_string(namestr);
        names.push_back(name);
        const int n_formals = random(0, 20);
        vector<Symbol> formals;
        for(int j = 0; j < n_formals; j++) 
        {  
            int random1 = random(0, classes.size());
            char namestr1[i+10+1];
            gen_random(namestr1, i + 10);
            Symbol name1 = idtable.add_string(namestr1);
            formals.push_back(name1);
        }

        int random1 = random(0, classes.size());
        int random2 = random(0, classes.size());

        pair<Symbol, vector<Symbol>> p(name, formals);
        methods.push_back(p);
        classes_of_ith_method.push_back(classes[random1]);
        ret_type_of_ith_method.push_back(classes[random2]);
        env.add(classes[random1], name, formals, classes[random2]);
    }
    for(unsigned int i = 0; i < methods.size(); i++)
    {
        MethodEnvironment::Signature& sig = env.lookup(classes_of_ith_method[i], methods[i].first);
        REQUIRE(sig.get_param_types() == methods[i].second);
        REQUIRE(sig.get_return_type() == ret_type_of_ith_method[i]);
    }

    for(unsigned int i = 0; i < methods.size(); i++) 
    {
        env.remove(classes_of_ith_method[i], methods[i].first);
        REQUIRE(!env.contains(classes_of_ith_method[i], methods[i].first));
    }

}
