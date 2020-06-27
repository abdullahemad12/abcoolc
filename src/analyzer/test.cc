#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include <iostream>
#include "catch.hpp"

#include "cool-tree.h"
#include "class-tree.h"
#include <cstdlib>
#include <string>
#include <utility>
#include <semant-errors.h>
#include <type-table.h>
#include <environment.h>
#include <class-validator.h>
#include <sys/wait.h>

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

TEST_CASE("LUB Operation")
{
    Classes classes = create_valid_graph();
    ClassTree ct(classes, idtable.add_string("Object"));
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
    ClassTree ct(classes, idtable.add_string("Object"));
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
    ClassTree ct(classes, idtable.add_string("Object"));

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

   char* expected_name = "myclass6";
   int pid = fork();
   if(pid = 0)
   {
       validate(classes);
   }
   else 
   {
        int status = 0;
        waitpid(pid, &status, 0);
        cout << status;
        REQUIRE(WIFSIGNALED(status));
   }
}

