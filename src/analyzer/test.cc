#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()

#include <iostream>
#include "catch.hpp"

#include "cool-tree.h"
#include "class-tree.h"
#include <cstdlib>
#include <string>
#include <utility>
#include <exceptions.h>

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
/*vector<ClassTree::Node*> generate_random_nodes(long n)
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
}*/
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

Classes create_cyclic_classes(void)
{
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol _no_class = idtable.add_string("_no_class");
    Symbol filename = idtable.add_string("filetable");
    Class_ class1 = class_(myclass1, myclass4, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);

    Classes classes1 = single_Classes(class1);
    Classes classes2 = single_Classes(class2);
    Classes classes3 = single_Classes(class3);
    Classes classes4 = single_Classes(class4);
    Classes classes5 = single_Classes(class5);
    Classes classes6 = single_Classes(class6);
    Classes classes7 = single_Classes(class7);
    
    Classes all = append_Classes(classes1, classes2);
    all = append_Classes(all, classes3);
    all = append_Classes(all, classes4);
    all = append_Classes(all, classes5);
    all = append_Classes(all, classes6);
    all = append_Classes(all, classes7);

    return all;
}

Classes create_valid_graph(void)
{
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol myclass8 = idtable.add_string("myclass8");
    Symbol myclass9 = idtable.add_string("myclass9");
    Symbol myclass10 = idtable.add_string("myclass10");
    Symbol _no_class = idtable.add_string("_no_class");
    Symbol filename = idtable.add_string("filetable");

    Class_ class1 = class_(myclass1, _no_class, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);
    Class_ class8 = class_(myclass8, myclass4, nil_Features(), filename);
    Class_ class9 = class_(myclass9, myclass4, nil_Features(), filename);
    Class_ class10 = class_(myclass10, myclass4, nil_Features(), filename);


    Classes classes1 = single_Classes(class1);
    Classes classes2 = single_Classes(class2);
    Classes classes3 = single_Classes(class3);
    Classes classes4 = single_Classes(class4);
    Classes classes5 = single_Classes(class5);
    Classes classes6 = single_Classes(class6);
    Classes classes7 = single_Classes(class7);
    Classes classes8 = single_Classes(class8);
    Classes classes9 = single_Classes(class9);
    Classes classes10 = single_Classes(class10);
    
    Classes all = append_Classes(classes1, classes2);
    all = append_Classes(all, classes3);
    all = append_Classes(all, classes4);
    all = append_Classes(all, classes5);
    all = append_Classes(all, classes6);
    all = append_Classes(all, classes7);
    all = append_Classes(all, classes8);
    all = append_Classes(all, classes9);
    all = append_Classes(all, classes10);

    return all;
}



/*************************************************************************************/
/*************************************Tests*******************************************/
/*************************************************************************************/

// this test is no longer valid due to a slight change in the interface
// the implementation did not change though
/*TEST_CASE( "Insert and Query of Segment Tree", "[segment_tree]" ) 
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
}*/


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

TEST_CASE("Cyclic graph Test")
{
    Classes classes = create_cyclic_classes();
    ClassTree& ct = ClassTree::instance();

    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(const CyclicClassException& e)
    {
        REQUIRE(true);
    }
    catch(const std::exception& e)
    {
        REQUIRE(false);
    }
    
}

TEST_CASE("LUB Operation")
{
    Classes classes = create_valid_graph();
    ClassTree& ct = ClassTree::instance();
    ct.init(classes);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol myclass8 = idtable.add_string("myclass8");
    Symbol myclass9 = idtable.add_string("myclass9");
    Symbol myclass10 = idtable.add_string("myclass10");

    Symbol sym = ct.lub(myclass1, myclass2);
    REQUIRE(sym == myclass1);

    sym = ct.lub(myclass9, myclass6);
    REQUIRE(sym == myclass1);

    sym = ct.lub(myclass9, myclass8);
    REQUIRE(sym == myclass4);

    sym = ct.lub(myclass10, myclass8);
    REQUIRE(sym == myclass4);

    sym = ct.lub(myclass5, myclass10);
    REQUIRE(sym == myclass1);
    
    sym = ct.lub(myclass6, myclass7);
    REQUIRE(sym == myclass5);

        
    sym = ct.lub(myclass7, myclass3);
    REQUIRE(sym == myclass1);

    sym = ct.lub(myclass7, myclass1);
    REQUIRE(sym == myclass1);
}

TEST_CASE("get_euler_walk")
{
    Classes classes = create_valid_graph();
    ClassTree& ct = ClassTree::instance();
    ct.init(classes);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol myclass8 = idtable.add_string("myclass8");
    Symbol myclass9 = idtable.add_string("myclass9");
    Symbol myclass10 = idtable.add_string("myclass10");

    vector<Symbol> vec;

    vec.push_back(myclass1);
    vec.push_back(myclass2);
    vec.push_back(myclass5);
    vec.push_back(myclass6);
    vec.push_back(myclass5);
    vec.push_back(myclass7);
    vec.push_back(myclass5);
    vec.push_back(myclass2);
    vec.push_back(myclass1);
    vec.push_back(myclass3);
    vec.push_back(myclass4);
    vec.push_back(myclass8);
    vec.push_back(myclass4);
    vec.push_back(myclass9);
    vec.push_back(myclass4);
    vec.push_back(myclass10);
    vec.push_back(myclass4);
    vec.push_back(myclass3);
    vec.push_back(myclass1);

    vector<Symbol> actual = ct.get_euler_trip();

    REQUIRE(vec == actual);
}