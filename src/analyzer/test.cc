#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include <iostream>
#include "catch.hpp"

#include "cool-tree.h"
#include "class-tree.h"
#include <cstdlib>
#include <string>
#include <utility>
#include <exceptions.h>
#include <class-table.h>
#include <environment.h>

extern Program ast_root;      // root of the abstract syntax tree
FILE *ast_file = stdin;       // we read the AST from standard input
extern int ast_yyparse(void); // entry point to the AST parser

int cool_yydebug;     // not used, but needed to link with handle_flags
char *curr_filename;

void handle_flags(int argc, char *argv[]);

using namespace std;



/***************************************************
 *       singleton class wrappers                  *
 * these classes allows instantiating instances    *
 * of the singleton class just for testing puposes *
 ***************************************************/
class ClassTreeWrapper : public ClassTree
{
    public:
        ClassTreeWrapper() { }
        ~ClassTreeWrapper() { }
};

class ClassTableWrapper : public ClassTable
{
    public:
        ClassTableWrapper() { }
        ~ClassTableWrapper() { }
};

class ObjectEnvironmentWrapper : public ObjectEnvironment
{
    public:
        ObjectEnvironmentWrapper() { }
        ~ObjectEnvironmentWrapper() { }
        void add(Symbol name, Symbol type)        
        {
            ObjectEnvironment::add(name, type);
        }
        void remove(Symbol name)
        {
            ObjectEnvironment::remove(name);
        }
        bool contains(Symbol name)
        {
            return ObjectEnvironment::contains(name);
        }
        Symbol lookup(Symbol name)
        {
            return ObjectEnvironment::lookup(name);
        }
};

class MethodEnvironmentWrapper : public MethodEnvironment
{
    public:
        MethodEnvironmentWrapper() { }
        ~MethodEnvironmentWrapper() { }
        void add(Symbol class_name, Symbol name, vector<Symbol> params, Symbol return_type)        
        {
            MethodEnvironment::add(class_name, name, params, return_type);
        }
        void remove(Symbol class_name, Symbol name)
        {
            MethodEnvironment::remove(class_name, name);
        }
        bool contains(Symbol class_name, Symbol name)
        {
            return MethodEnvironment::contains(class_name, name);
        }
        MethodSignature lookup(Symbol class_name, Symbol name)
        {
            return MethodEnvironment::lookup(class_name, name);
        }
};

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
    Symbol Object = idtable.add_string("Object");
    Symbol No_class = idtable.add_string(no_type);
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
    Class_ Object_class = class_(Object, No_class, nil_Features(), filename);


    Classes classes1 = single_Classes(class1);
    Classes classes2 = single_Classes(class2);
    Classes classes3 = single_Classes(class3);
    Classes classes4 = single_Classes(class4);
    Classes classes5 = single_Classes(class5);
    Classes classes6 = single_Classes(class6);
    Classes classes7 = single_Classes(class7);
    Classes object_classes = single_Classes(Object_class);

    
    Classes all = append_Classes(classes1, classes2);
    all = append_Classes(all, classes3);
    all = append_Classes(all, classes4);
    all = append_Classes(all, classes5);
    all = append_Classes(all, classes6);
    all = append_Classes(all, classes7);
    all = append_Classes(all, object_classes);


    return all;
}

Classes create_valid_graph(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol no_class  = idtable.add_string(no_type);
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

    Class_ class1 = class_(myclass1, Object, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);
    Class_ class8 = class_(myclass8, myclass4, nil_Features(), filename);
    Class_ class9 = class_(myclass9, myclass4, nil_Features(), filename);
    Class_ class10 = class_(myclass10, myclass4, nil_Features(), filename);
    Class_ Object_class = class_(Object, no_class, nil_Features(), filename);
	


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
    Classes object_classes = single_Classes(Object_class);
    
    Classes all = append_Classes(classes1, classes2);
    all = append_Classes(all, classes3);
    all = append_Classes(all, classes4);
    all = append_Classes(all, classes5);
    all = append_Classes(all, classes6);
    all = append_Classes(all, classes7);
    all = append_Classes(all, classes8);
    all = append_Classes(all, classes9);
    all = append_Classes(all, classes10);
    all = append_Classes(all, object_classes);

    return all;
}

Classes create_valid_graph_without_object(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol no_class  = idtable.add_string(no_type);
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

    Class_ class1 = class_(myclass1, Object, nil_Features(), filename);
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



Classes create_redefinition_graph1(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol no_class  = idtable.add_string(no_type);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass6");
    Symbol myclass8 = idtable.add_string("myclass8");
    Symbol myclass9 = idtable.add_string("myclass9");
    Symbol myclass10 = idtable.add_string("myclass10");
    Symbol _no_class = idtable.add_string("_no_class");
    Symbol filename = idtable.add_string("filetable");

    Class_ class1 = class_(myclass1, Object, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);
    Class_ class8 = class_(myclass8, myclass4, nil_Features(), filename);
    Class_ class9 = class_(myclass9, myclass4, nil_Features(), filename);
    Class_ class10 = class_(myclass10, myclass4, nil_Features(), filename);
    Class_ Object_class = class_(Object, no_class, nil_Features(), filename);
	


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


Classes create_redefinition_graph2(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol No_class = idtable.add_string(no_type);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass4");
    Symbol myclass7 = idtable.add_string("myclass2");
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
};

Classes create_invalid_inheritance_classes1(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol No_class = idtable.add_string(no_type);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol _no_class = idtable.add_string("_no_class");
    Symbol filename = idtable.add_string("filetable");

    Symbol myclass20 = idtable.add_string("myclass20");

    Class_ class1 = class_(myclass1, myclass4, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass20, nil_Features(), filename);
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

Classes create_invalid_inheritance_classes2(void)
{
    Symbol Object = idtable.add_string("Object");
    Symbol no_class  = idtable.add_string(no_type);
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

    Symbol myclass19 = idtable.add_string("myclass19");
    Symbol myclass20 = idtable.add_string("myclass20");

    Class_ class1 = class_(myclass1, myclass19, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);
    Class_ class8 = class_(myclass8, myclass4, nil_Features(), filename);
    Class_ class9 = class_(myclass9, myclass4, nil_Features(), filename);
    Class_ class10 = class_(myclass10, myclass20, nil_Features(), filename);
	


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


Classes create_basic_class_redefinition(char* basic_class)
{
    Symbol no_class  = idtable.add_string(no_type);
    Symbol myclass1 = idtable.add_string("myclass1");
    Symbol myclass2 = idtable.add_string("myclass2");
    Symbol myclass3 = idtable.add_string("myclass3");
    Symbol myclass4 = idtable.add_string("myclass4");
    Symbol myclass5 = idtable.add_string("myclass5");
    Symbol myclass6 = idtable.add_string("myclass6");
    Symbol myclass7 = idtable.add_string("myclass7");
    Symbol myclass8 = idtable.add_string("myclass8");
    Symbol myclass9 = idtable.add_string(basic_class);
    Symbol myclass10 = idtable.add_string("myclass10");
    Symbol _no_class = idtable.add_string("_no_class");
    Symbol filename = idtable.add_string("filetable");
    Symbol object_sym = idtable.add_string("Object");

    Class_ class1 = class_(myclass1, object_sym, nil_Features(), filename);
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

Classes create_basic_class_inheritance(char* basic_class)
{
    Symbol no_class  = idtable.add_string(no_type);
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
    Symbol object_sym = idtable.add_string("Object");
    Symbol int_sym = idtable.add_string(basic_class);

    Class_ class1 = class_(myclass1, object_sym, nil_Features(), filename);
    Class_ class2 = class_(myclass2, myclass1, nil_Features(), filename);
    Class_ class3 = class_(myclass3, myclass1, nil_Features(), filename);
    Class_ class4 = class_(myclass4, myclass3, nil_Features(), filename);
    Class_ class5 = class_(myclass5, myclass2, nil_Features(), filename);
    Class_ class6 = class_(myclass6, myclass5, nil_Features(), filename);
    Class_ class7 = class_(myclass7, myclass5, nil_Features(), filename);
    Class_ class8 = class_(myclass8, int_sym, nil_Features(), filename);
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


Feature create_method1()
{
    Symbol method_name = idtable.add_string("method_name");
    Symbol type1 = idtable.add_string("My_type1");
    Symbol type2 = idtable.add_string("My_type2");
    Symbol name1 = idtable.add_string("Name1");
    Symbol name2 = idtable.add_string("Name2");
    Symbol return_type = idtable.add_string("return_type");
    Formal formal1 = formal(name1, type1);
    Formal formal2 = formal(name2, type2);
    Formals formals1 = single_Formals(formal1);
    Formals formals2 = single_Formals(formal2);
    Formals formals = append_Formals(formals1, formals2);
    
    Feature meth = method(method_name, formals, return_type, no_expr());

    return meth;
}
Feature create_method2()
{
    Symbol method_name = idtable.add_string("method_name");
    Symbol type1 = idtable.add_string("My_type1");
    Symbol type2 = idtable.add_string("My_type2");
    Symbol name1 = idtable.add_string("Name1");
    Symbol name2 = idtable.add_string("Name2");
    Symbol name3 = idtable.add_string("Name3");

    Symbol return_type = idtable.add_string("return_type");
    
    Formal formal1 = formal(name1, type1);
    Formal formal2 = formal(name2, type2);
    Formal formal3 = formal(name3, type2);

    Formals formals1 = single_Formals(formal1);
    Formals formals2 = single_Formals(formal2);
    Formals formals3 = single_Formals(formal3);
    Formals formals = append_Formals(formals1, formals2);
    formals = append_Formals(formals, formals3);
    Feature meth = method(method_name, formals, return_type, no_expr());

    return meth;
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
    ObjectEnvironmentWrapper objenv;
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
    MethodEnvironmentWrapper env;
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
        MethodEnvironment::Signature sig = env.lookup(classes_of_ith_method[i], methods[i].first);
        REQUIRE(sig.get_param_types() == methods[i].second);
        REQUIRE(sig.get_return_type() == ret_type_of_ith_method[i]);
    }

    for(unsigned int i = 0; i < methods.size(); i++) 
    {
        env.remove(classes_of_ith_method[i], methods[i].first);
        REQUIRE(!env.contains(classes_of_ith_method[i], methods[i].first));
    }

}

TEST_CASE("Multiple insertions in Method environment")
{
    MethodEnvironmentWrapper env;
    int t = 100;
    for(int i = 0; i < t; i++)
    {
        Symbol myclass = idtable.add_string("My_class");
        Symbol method = idtable.add_string("my_method");
        Symbol type1 = idtable.add_string("My_type1");
        Symbol type2 = idtable.add_string("My_type2");
        Symbol type3 = idtable.add_string("My_type3");
        vector<Symbol> formals = {type1, type2, type3};
        Symbol return_type = idtable.add_string("Return_type");
        env.add(myclass, method, formals, return_type);
        REQUIRE(env.contains(myclass, method));
        MethodEnvironment::Signature sign = env.lookup(myclass, method);
        REQUIRE(sign.get_param_types() == formals);
        REQUIRE(sign.get_return_type() == return_type);
    }

    for(int i = 0; i < t - 1; i++)
    {
        Symbol myclass = idtable.add_string("My_class");
        Symbol method = idtable.add_string("my_method");
        Symbol type1 = idtable.add_string("My_type1");
        Symbol type2 = idtable.add_string("My_type2");
        Symbol type3 = idtable.add_string("My_type3");
        vector<Symbol> formals = {type1, type2, type3};
        Symbol return_type = idtable.add_string("Return_type");
        env.remove(myclass, method);
        REQUIRE(env.contains(myclass, method));
        MethodEnvironment::Signature sign = env.lookup(myclass, method);
        REQUIRE(sign.get_param_types() == formals);
        REQUIRE(sign.get_return_type() == return_type);
    }
    Symbol myclass = idtable.add_string("My_class");
    Symbol method = idtable.add_string("my_method");
    env.remove(myclass, method);
    REQUIRE(!env.contains(myclass, method));
}
TEST_CASE("Cyclic graph Test")
{
    Classes classes = create_cyclic_classes();
    ClassTreeWrapper ct;
    Symbol object = idtable.add_string("Object");
    
    try
    {
        ct.init(classes, object);
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
    ClassTreeWrapper ct;
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
    Symbol object = idtable.add_string("Object");
    Symbol recovery = idtable.add_string("_recovery");
    ct.init(classes, object);

    Symbol sym = ct.lub(recovery, object);
    REQUIRE(sym == object);
    
    sym = ct.lub(myclass1, myclass2);
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
TEST_CASE("is_derived check")
{
    Classes classes = create_valid_graph();
    ClassTreeWrapper ct;
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
    Symbol object = idtable.add_string("Object");
    Symbol recovery = idtable.add_string("_recovery");

    ct.init(classes, object);

    REQUIRE(ct.is_derived(myclass2, myclass1));
    REQUIRE(ct.is_derived(myclass4, myclass3));
    REQUIRE(!ct.is_derived(myclass9, myclass8));
    REQUIRE(!ct.is_derived(myclass4, myclass5));
    REQUIRE(ct.is_derived(myclass4, object));
    REQUIRE(ct.is_derived(myclass5, myclass2));
    REQUIRE(!ct.is_derived(myclass8, myclass6));
    REQUIRE(ct.is_derived(myclass6, myclass6));

}

TEST_CASE("get_euler_walk")
{
    Classes classes = create_valid_graph();
    ClassTreeWrapper ct;

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
    Symbol object = idtable.add_string("Object");
    Symbol recovery = idtable.add_string("_recovery");
    ct.init(classes, object);

    vector<Symbol> expected;

    expected.push_back(object);
    expected.push_back(myclass1);
    expected.push_back(myclass2);
    expected.push_back(myclass5);
    expected.push_back(myclass6);
    expected.push_back(myclass5);
    expected.push_back(myclass7);
    expected.push_back(myclass5);
    expected.push_back(myclass2);
    expected.push_back(myclass1);
    expected.push_back(myclass3);
    expected.push_back(myclass4);
    expected.push_back(myclass8);
    expected.push_back(myclass4);
    expected.push_back(myclass9);
    expected.push_back(myclass4);
    expected.push_back(myclass10);
    expected.push_back(myclass4);
    expected.push_back(myclass3);
    expected.push_back(myclass1);
    expected.push_back(object);


    vector<Symbol> actual;
    for(Symbol sym : ct)
        actual.push_back(sym);

    REQUIRE(expected == actual);
}


TEST_CASE("Class Redefinition detection Test 1")
{
   Classes classes = create_redefinition_graph1();
   ClassTableWrapper ct;
   char* expected_name = "myclass6";
   try
   {
      ct.init(classes);
      REQUIRE(false);
   }
   catch(ClassRedefinitionException& excep)
   {
      Symbol expected = idtable.add_string(expected_name);
      REQUIRE(excep.get_faulty_class() == expected);
   }
   catch(exception& excep)
   {
      REQUIRE(false);
   }
}

TEST_CASE("Class Redefinition detection Test 2")
{
    Classes classes = create_redefinition_graph2();
    ClassTableWrapper ct;
    char* expected_name = "myclass4";
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(ClassRedefinitionException& excep)
    {   
        Symbol expected = idtable.add_string("myclass4");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Invalid Inheritance detection Test1")
{
    Classes classes = create_invalid_inheritance_classes1();
    ClassTableWrapper ct;

    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(UndefinedClassException& excep)
    {
        Symbol expected = idtable.add_string("myclass6");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Invalid Inheritance detection Test2")
{
    Classes classes = create_invalid_inheritance_classes2();
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(UndefinedClassException& excep)
    {
        Symbol expected = idtable.add_string("myclass1");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}


TEST_CASE("Basic Class Redefinition detection test 1")
{
    char* basic_class = "Int";
    Classes classes = create_basic_class_redefinition(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassRedefinitionException& excep)
    {
        Symbol expected = idtable.add_string(basic_class);
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Redefinition detection test 2")
{
    char* basic_class = "String";
    Classes classes = create_basic_class_redefinition(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassRedefinitionException& excep)
    {
        Symbol expected = idtable.add_string(basic_class);
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Redefinition detection test 3")
{
    char* basic_class = "Bool";
    Classes classes = create_basic_class_redefinition(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassRedefinitionException& excep)
    {
        Symbol expected = idtable.add_string(basic_class);
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Redefinition detection test 4")
{
    char* basic_class = "IO";
    Classes classes = create_basic_class_redefinition(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassRedefinitionException& excep)
    {
        Symbol expected = idtable.add_string(basic_class);
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Inheritance detection test 1")
{
    char* basic_class = "Bool";
    Classes classes = create_basic_class_inheritance(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassInheritanceException& excep)
    {
        Symbol expected = idtable.add_string("myclass8");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Inheritance detection test 2")
{
    char* basic_class = "String";
    Classes classes = create_basic_class_inheritance(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassInheritanceException& excep)
    {
        Symbol expected = idtable.add_string("myclass8");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}
TEST_CASE("Basic Class Inheritance detection test 3")
{
    char* basic_class = "Int";
    Classes classes = create_basic_class_inheritance(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
        REQUIRE(false);
    }
    catch(BasicClassInheritanceException& excep)
    {
        Symbol expected = idtable.add_string("myclass8");
        REQUIRE(excep.get_faulty_class() == expected);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("Basic Class Inheritance detection test 4")
{
    char* basic_class = "IO";
    Classes classes = create_basic_class_inheritance(basic_class);
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
}

TEST_CASE("ClassTable Install Basic Class Test")
{
    Classes classes = create_valid_graph_without_object();
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }
    Symbol int_class = idtable.add_string("Int");
    Symbol string_class = idtable.add_string("String");
    Symbol bool_class = idtable.add_string("Bool");
    Symbol IO_class = idtable.add_string("IO");
    Symbol object_class = idtable.add_string("Object");
    
    REQUIRE(ct.contains(int_class));
    REQUIRE(ct.contains(string_class));
    REQUIRE(ct.contains(bool_class));
    REQUIRE(ct.contains(IO_class));
    REQUIRE(ct.contains(object_class));
    
    REQUIRE(ct[int_class]->get_name() == int_class);
    REQUIRE(ct[string_class]->get_name() == string_class);
    REQUIRE(ct[bool_class]->get_name() == bool_class);
    REQUIRE(ct[IO_class]->get_name() == IO_class);
    REQUIRE(ct[object_class]->get_name() == object_class);
}

TEST_CASE("ClassTable Contains Test")
{
    Classes classes = create_valid_graph_without_object();
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }

    for(int i = 0; i < classes->len(); i++)
    {
        REQUIRE(ct.contains(classes->nth(i)->get_name()));
    }
}

TEST_CASE("ClassTable operator[] Test")
{
    Classes classes = create_valid_graph_without_object();
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }

    for(int i = 0; i < classes->len(); i++)
    {
        REQUIRE(ct[classes->nth(i)->get_name()] == classes->nth(i));
    }
}

TEST_CASE("ClassTable Iterator Test")
{
    Classes classes = create_valid_graph_without_object();
    ClassTableWrapper ct;
    try
    {
        ct.init(classes);
    }
    catch(exception& excep)
    {
        REQUIRE(false);
    }

    unordered_set<Class_> classes_vec;
    for(auto& entry : ct)
    {
        REQUIRE(entry.first == entry.second->get_name());
        classes_vec.insert(entry.second);
    }

    for(int i = 0; i < classes->len(); i++)
    {
        REQUIRE(classes_vec.find(classes->nth(i)) != classes_vec.end());
    }

}

TEST_CASE("method_class::add_to_global_env test1")
{
    Symbol class_name = idtable.add_string("Class_name");
    Feature method = create_method1();
    method->add_to_global_env(class_name);

    Environment& env = Environment::instance();

    REQUIRE(env.contains_global_method(class_name, method->get_name()));
    MethodEnvironment::Signature sign = env.lookup_global_method(class_name, method->get_name());

    // not good style but I need to assert this 
    REQUIRE((sign ==  *((method_class*) method)));

    env.remove_global_method(class_name, method->get_name());

    REQUIRE(!env.contains_global_method(class_name, method->get_name()));

}

TEST_CASE("method_class::add_to_global_env test2")
{
    // tons of memory leaks :(
    int t = 100;
    Environment& env = Environment::instance();
    for(int i = 0; i < t; i++)
    {
        Symbol class_name = idtable.add_string("Class_name");
        Feature method = create_method1();
        method->add_to_global_env(class_name);
        REQUIRE(env.contains_global_method(class_name, method->get_name()));
    }
    Symbol class_name = idtable.add_string("Class_name");
    Feature method = create_method1();
    env.remove_global_method(class_name, method->get_name());
    if(env.contains_global_method(class_name, method->get_name()))
    {
        while(env.contains_global_method(class_name, method->get_name()))
            env.remove_global_method(class_name, method->get_name());
        // do this to for the other tests to work correctly
        REQUIRE(false);
    }
}

TEST_CASE("method_class::add_to_local_env1")
{
    Symbol class_name = idtable.add_string("local_type");
    Feature method = create_method1();
    method->add_to_local_env();

    Environment& env = Environment::instance();

    REQUIRE(env.contains_local_method(method->get_name()));
    MethodEnvironment::Signature sign = env.lookup_local_method(method->get_name());

    // not good style but I need to assert this 
    REQUIRE((sign ==  *((method_class*) method)));

    env.remove_local_method(method->get_name());

    REQUIRE(!env.contains_local_method(method->get_name()));
}

TEST_CASE("method_class::add_to_local_env2")
{
    Symbol class_name = idtable.add_string("local_type");
    Feature method = create_method1();
    method->add_to_local_env();
    
    int t = 10;
    for(int i = 0; i < t; i++)
    {
        Feature method_copy = create_method1();
        method_copy->add_to_local_env();
    }
    Environment& env = Environment::instance();
    for(int i = 0; i < t; i++)
    {
        env.remove_local_method(method->get_name());
        REQUIRE(env.contains_local_method(method->get_name()));
    }
    env.remove_local_method(method->get_name());
    REQUIRE(!env.contains_local_method(method->get_name()));

}

TEST_CASE("method_class::add_to_local_env3")
{
    Symbol class_name = idtable.add_string("local_type");
    Feature method = create_method2();
    method->add_to_local_env();

    Environment& env = Environment::instance();

    REQUIRE(env.contains_local_method(method->get_name()));
    MethodEnvironment::Signature sign = env.lookup_local_method(method->get_name());

    // not good style but I need to assert this 
    REQUIRE((sign ==  *((method_class*) method)));

    env.remove_local_method(method->get_name());

    REQUIRE(!env.contains_local_method(method->get_name()));
}


TEST_CASE("Invalid method_class::add_to_local_env4")
{
    // attempt two insert two methods with the same name but different parameters
    Symbol class_name = idtable.add_string("local_type");
    Feature method1 = create_method1();
    Feature method2 = create_method2();

    method1->add_to_local_env();

    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();
    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }

    method2->add_to_local_env();
    
    Environment& env = Environment::instance();
    
    env.remove_local_method(method1->get_name());
    REQUIRE(!env.contains_local_method(method1->get_name()));

    vector<SemantException*> exceptions_after;
    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }
    REQUIRE(method2->is_malformed());
    REQUIRE(exceptions_after.size() == exceptions_before.size() + 1);
}

TEST_CASE("method_class::remove_from_local_env")
{
    // attempt two insert two methods with the same name but different parameters
    Symbol class_name = idtable.add_string("local_type");
    Feature method1 = create_method1();

    method1->add_to_local_env();

    Environment& env = Environment::instance();
    REQUIRE(env.contains_local_method(method1->get_name()));
    method1->remove_from_local_env();
    REQUIRE(!env.contains_local_method(method1->get_name()));

}

TEST_CASE("attribute::add_to_local_env")
{
    Symbol attr1 = idtable.add_string("attr1");
    Symbol attr2 = idtable.add_string("attr2");
    Symbol type1 = idtable.add_string("type1");

    Feature fattr1 = attr(attr1, type1, no_expr());
    Feature fattr2 = attr(attr2, type1, no_expr());
    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();
    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }
    fattr1->add_to_local_env();
    fattr2->add_to_local_env();

    Environment& env = Environment::instance();

    REQUIRE(env.contains_local_object(attr1));

    env.remove_local_object(attr1);

    REQUIRE(env.contains_local_object(attr2));

    env.remove_local_object(attr2);

    REQUIRE(!env.contains_local_object(attr2));


    vector<SemantException*> exceptions_after;
    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }
    REQUIRE(exceptions_before.size() == exceptions_after.size());

}

TEST_CASE("Invalid attribute::add_to_local_env")
{
    Symbol attr1 = idtable.add_string("attr1");
    Symbol attr2 = idtable.add_string("attr1");
    Symbol type1 = idtable.add_string("type1");

    Feature fattr1 = attr(attr1, type1, no_expr());
    Feature fattr2 = attr(attr2, type1, no_expr());
    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();
    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }
    fattr1->add_to_local_env();
    fattr2->add_to_local_env();

    Environment& env = Environment::instance();

    REQUIRE(env.contains_local_object(attr1));

    env.remove_local_object(attr1);

    REQUIRE(!env.contains_local_object(attr2));

    REQUIRE(!fattr1->is_malformed());
    REQUIRE(fattr2->is_malformed());

    vector<SemantException*> exceptions_after;
    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }
    REQUIRE(exceptions_before.size() == exceptions_after.size() - 1);
}

TEST_CASE("Sync_local_environment1")
{
     
    Symbol attr1 = idtable.add_string("attr1");
    Symbol attr2 = idtable.add_string("attr2");
    Symbol type1 = idtable.add_string("type1");

    Feature fattr1 = attr(attr1, type1, no_expr());
    Feature fattr2 = attr(attr2, type1, no_expr());

    Feature method = create_method1();

    Features f1 = single_Features(fattr1);
    Features f2 = single_Features(fattr2);
    Features f3 = single_Features(method);
    Features features = append_Features(f1, f2);
    features = append_Features(features, f3);

    Symbol class_name = idtable.add_string("Class1");
    Symbol parent = idtable.add_string("Object");
    Symbol filename = idtable.add_string("cool.cl");
    Class_ class__ = class_(class_name, parent, features, filename);

    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();

    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }

    class__->sync_local_env();

    vector<SemantException*> exceptions_after;
    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }
    
    REQUIRE(exceptions_after == exceptions_before);

    Environment& env = Environment::instance();


    Symbol local_class = idtable.add_string(LOCAL_TYPE);
    REQUIRE(env.contains_local_method(method->get_name()));
    REQUIRE(env.contains_local_object(attr1));
    REQUIRE(env.contains_local_object(attr2));
    REQUIRE(!method->is_malformed());
    REQUIRE(!fattr1->is_malformed());
    REQUIRE(!fattr2->is_malformed());

    class__->clean_local_env();
    REQUIRE(!env.contains_local_method(method->get_name()));
    REQUIRE(!env.contains_local_object(attr1));
    REQUIRE(!env.contains_local_object(attr2));
}

TEST_CASE("Sync_local_environment2")
{
    Symbol attr1 = idtable.add_string("attr1");
    Symbol type1 = idtable.add_string("type1");

    Feature fattr1 = attr(attr1, type1, no_expr());

    Feature method = create_method1();
    Feature fattr2 = attr(method->get_name(), type1, no_expr());

    Features f1 = single_Features(fattr1);
    Features f2 = single_Features(fattr2);
    Features f3 = single_Features(method);
    Features features = append_Features(f1, f3);
    features = append_Features(features, f2);

    Symbol class_name = idtable.add_string("Class1");
    Symbol parent = idtable.add_string("Object");
    Symbol filename = idtable.add_string("cool.cl");
    Class_ class__ = class_(class_name, parent, features, filename);

    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();

    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }
    class__->sync_local_env();

    vector<SemantException*> exceptions_after;
    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }
    
    REQUIRE(exceptions_after != exceptions_before);
    Environment& env = Environment::instance();


    Symbol local_class = idtable.add_string(LOCAL_TYPE);
    REQUIRE(env.contains_local_method(method->get_name()));
    REQUIRE(env.contains_local_object(attr1));
    REQUIRE(!method->is_malformed());
    REQUIRE(!fattr1->is_malformed());
    REQUIRE(fattr2->is_malformed());
    
    class__->clean_local_env();
    REQUIRE(!env.contains_local_method(method->get_name()));
    REQUIRE(!env.contains_local_object(attr1));
}


TEST_CASE("Method::synch_local_environment1")
{
    Symbol name = idtable.add_string("method_name");
    Symbol ret_type = idtable.add_string("Type");
    Symbol id1 = idtable.add_string("id1");
    Symbol id2 = idtable.add_string("id2");
    Symbol id3 = idtable.add_string("id3");
    Symbol id4 = idtable.add_string("id4");
    Symbol id5 = idtable.add_string("id5");
    Symbol self = idtable.add_string("self");
    Symbol type1 = idtable.add_string("Type1");
    Symbol type2 = idtable.add_string("Type2");
    Symbol type3 = idtable.add_string("Type1");
    Symbol type4 = idtable.add_string("Type3");
    Symbol type5 = idtable.add_string("Type3");
    
    Formal formal1 = formal(id1, type1);
    Formal formal2 = formal(id2, type2);
    Formal formal3 = formal(id3, type3);
    Formal formal4 = formal(id4, type4);
    Formal formal5 = formal(id5, type5);

    Formals sing1 = single_Formals(formal1);
    Formals sing2 = single_Formals(formal2);
    Formals sing3 = single_Formals(formal3);
    Formals sing4 = single_Formals(formal4);
    Formals sing5 = single_Formals(formal5);

    Formals formals = append_Formals(sing1, sing2);
    formals = append_Formals(formals, sing3);
    formals = append_Formals(formals, sing4);
    formals = append_Formals(formals, sing5);

    method_class* meth = (method_class*) method(name, formals, ret_type, no_expr());

    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();

    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }

    meth->sync_local_environment();
    vector<SemantException*> exceptions_after;

    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }

    REQUIRE(exceptions_before == exceptions_after);

    Environment& env = Environment::instance();
    REQUIRE(env.contains_local_object(id1));
    REQUIRE(env.contains_local_object(id2));
    REQUIRE(env.contains_local_object(id3));
    REQUIRE(env.contains_local_object(id4));
    REQUIRE(env.contains_local_object(id5));
    REQUIRE(env.contains_local_object(self));

    REQUIRE(env.lookup_local_object(id1) == type1);
    REQUIRE(env.lookup_local_object(id2) == type2);
    REQUIRE(env.lookup_local_object(id3) == type3);
    REQUIRE(env.lookup_local_object(id4) == type4);
    REQUIRE(env.lookup_local_object(id5) == type5);
    REQUIRE(env.lookup_local_object(self) == env.current_class);

    env.remove_local_object(id1);
    env.remove_local_object(id2);
    env.remove_local_object(id3);
    env.remove_local_object(id4);
    env.remove_local_object(id5);
    env.remove_local_object(self);

    REQUIRE(!env.contains_local_object(id1));
    REQUIRE(!env.contains_local_object(id2));
    REQUIRE(!env.contains_local_object(id3));
    REQUIRE(!env.contains_local_object(id4));
    REQUIRE(!env.contains_local_object(id5));
    REQUIRE(!env.contains_local_object(self));

    REQUIRE(!formal2->is_malformed());
    REQUIRE(!formal4->is_malformed());
    REQUIRE(!formal1->is_malformed());
    REQUIRE(!formal3->is_malformed());
    REQUIRE(!formal5->is_malformed());
}


TEST_CASE("Method::synch_local_environment2")
{
    Symbol name = idtable.add_string("method_name");
    Symbol ret_type = idtable.add_string("Type");
    Symbol id1 = idtable.add_string("id1");
    Symbol id2 = idtable.add_string("id1");
    Symbol id3 = idtable.add_string("id3");
    Symbol id4 = idtable.add_string("id3");
    Symbol id5 = idtable.add_string("id5");
    Symbol type1 = idtable.add_string("Type1");
    Symbol type2 = idtable.add_string("Type2");
    Symbol type3 = idtable.add_string("Type1");
    Symbol type4 = idtable.add_string("Type3");
    Symbol type5 = idtable.add_string("Type3");
    Symbol self = idtable.add_string("self");

    Formal formal1 = formal(id1, type1);
    Formal formal2 = formal(id2, type2);
    Formal formal3 = formal(id3, type3);
    Formal formal4 = formal(id4, type4);
    Formal formal5 = formal(id5, type5);

    Formals sing1 = single_Formals(formal1);
    Formals sing2 = single_Formals(formal2);
    Formals sing3 = single_Formals(formal3);
    Formals sing4 = single_Formals(formal4);
    Formals sing5 = single_Formals(formal5);

    Formals formals = append_Formals(sing1, sing2);
    formals = append_Formals(formals, sing3);
    formals = append_Formals(formals, sing4);
    formals = append_Formals(formals, sing5);

    method_class* meth = (method_class*) method(name, formals, ret_type, no_expr());

    SemantExceptionHandler& sem_error = SemantExceptionHandler::instance();

    vector<SemantException*> exceptions_before;
    for(SemantException* excep : sem_error)
    {
        exceptions_before.push_back(excep);
    }
    meth->sync_local_environment();
    vector<SemantException*> exceptions_after;

    for(SemantException* excep : sem_error)
    {
        exceptions_after.push_back(excep);
    }

    REQUIRE(exceptions_before.size() == exceptions_after.size() - 2);

    Environment& env = Environment::instance();
    REQUIRE(env.contains_local_object(id1));
    REQUIRE(env.contains_local_object(id3));
    REQUIRE(env.contains_local_object(id5));
    REQUIRE(env.contains_local_object(self));

    REQUIRE(env.lookup_local_object(id1) == type1);
    REQUIRE(env.lookup_local_object(id3) == type3);
    REQUIRE(env.lookup_local_object(id5) == type5);
    REQUIRE(env.lookup_local_object(self) == env.current_class);

    env.remove_local_object(id1);
    env.remove_local_object(id3);
    env.remove_local_object(id5);
    env.remove_local_object(self);

    REQUIRE(!env.contains_local_object(id1));
    REQUIRE(!env.contains_local_object(id2));
    REQUIRE(!env.contains_local_object(id3));
    REQUIRE(!env.contains_local_object(id4));
    REQUIRE(!env.contains_local_object(id5));
    REQUIRE(formal2->is_malformed());
    REQUIRE(formal4->is_malformed());
    REQUIRE(!formal1->is_malformed());
    REQUIRE(!formal3->is_malformed());
    REQUIRE(!formal5->is_malformed());

}

TEST_CASE("Method::clean_local_environment3")
{
    Symbol name = idtable.add_string("method_name");
    Symbol ret_type = idtable.add_string("Type");
    Symbol id1 = idtable.add_string("id1");
    Symbol id2 = idtable.add_string("id1");
    Symbol id3 = idtable.add_string("id3");
    Symbol id4 = idtable.add_string("id3");
    Symbol id5 = idtable.add_string("id5");
    Symbol type1 = idtable.add_string("Type1");
    Symbol type2 = idtable.add_string("Type2");
    Symbol type3 = idtable.add_string("Type1");
    Symbol type4 = idtable.add_string("Type3");
    Symbol type5 = idtable.add_string("Type3");
    Symbol self = idtable.add_string("self");

    Formal formal1 = formal(id1, type1);
    Formal formal2 = formal(id2, type2);
    Formal formal3 = formal(id3, type3);
    Formal formal4 = formal(id4, type4);
    Formal formal5 = formal(id5, type5);

    Formals sing1 = single_Formals(formal1);
    Formals sing2 = single_Formals(formal2);
    Formals sing3 = single_Formals(formal3);
    Formals sing4 = single_Formals(formal4);
    Formals sing5 = single_Formals(formal5);

    Formals formals = append_Formals(sing1, sing2);
    formals = append_Formals(formals, sing3);
    formals = append_Formals(formals, sing4);
    formals = append_Formals(formals, sing5);

    method_class* meth = (method_class*) method(name, formals, ret_type, no_expr());



    meth->sync_local_environment();


    Environment& env = Environment::instance();

    meth->clean_local_environment();

    REQUIRE(!env.contains_local_object(id1));
    REQUIRE(!env.contains_local_object(id2));
    REQUIRE(!env.contains_local_object(id3));
    REQUIRE(!env.contains_local_object(id4));
    REQUIRE(!env.contains_local_object(id5));
    REQUIRE(!env.contains_local_object(self));
}