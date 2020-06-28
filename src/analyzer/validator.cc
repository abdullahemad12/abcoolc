#include <tree.h>
#include <type-table.h>
#include <cool-tree.h>
#include <unordered_map>
#include <class-tree.h>
#include <semant-errors.h>
#include <union-find.h>

#define SET_CONTAINS(set, elem) (set.find((elem)) != set.end())
#define RAISE_FATAL(err) \
SemantErrorHandler& sem_err = SemantErrorHandler::instance();\
sem_err.report_fatal((err));

#define RAISE(err) \
SemantErrorHandler& sem_err = SemantErrorHandler::instance();\
sem_err.report((err));

using namespace std;


// prototypes
Class_ classes_find_duplicates(Classes classes);
bool has_main(Classes classes);
Feature features_find_duplicates(Features features);
void handle_duplicate_feature(Feature feature);
void handle_duplicate_formal(Formal formal);
void undefined_types_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);
void resreved_id_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);
void resreved_type_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);



//////////////////////////////////////////////////////
// checks:
// 1) Main Existance
// 2) Undefined Types 
// 3) basic classes misuse
// 4) redefinitions
// 5) cycles
// if any of the following checks fails, the program is 
// terminated after reporting the error
////////////////////////////////////////////////////////
void program_class::validate(TypeTable& type_table)
{
    redefintions_detection();
    missing_main_detection();
    cycle_detection();
}
void class__class::validate(TypeTable& type_table)
{
    undefined_type_detection(type_table);
    name_reserved_detection(type_table);
    inheritance_reserved_detection(type_table);
    basic_class_inheritance_detection(type_table);
    builtin_class_redefinition(type_table);
    feature_redefinition_detection();
}
void method_class::validate(TypeTable& type_table)
{
    reserved_symbols_misuse_detection(type_table);
    undefined_types_detection(type_table);
    formal_redefinition_detection(type_table);
}
void attr_class::validate(TypeTable& type_table)
{
    reserved_symbols_misuse_detection(type_table);
    undefined_types_detection(type_table);
    formal_redefinition_detection(type_table);
}
void formal_class::validate(TypeTable& type_table)
{
    reserved_symbols_misuse_detection(type_table);
    undefined_types_detection(type_table);
    reserved_type_misuse_detection(type_table);
}
void assign_class::validate(TypeTable& type_table)
{
    
}
void static_dispatch_class::validate(TypeTable& type_table)
{
    
}
void dispatch_class::validate(TypeTable& type_table)
{
    
}
void cond_class::validate(TypeTable& type_table)
{
    
}
void loop_class::validate(TypeTable& type_table)
{
    
}
void typcase_class::validate(TypeTable& type_table)
{
    
}
void branch_class::validate(TypeTable& type_table)
{
    
}
void block_class::validate(TypeTable& type_table)
{
    
}
void let_class::validate(TypeTable& type_table)
{
    
}
void plus_class::validate(TypeTable& type_table)
{
    
}
void sub_class::validate(TypeTable& type_table)
{
    
}
void mul_class::validate(TypeTable& type_table)
{
    
}
void divide_class::validate(TypeTable& type_table)
{
    
}
void neg_class::validate(TypeTable& type_table)
{
    
}
void lt_class::validate(TypeTable& type_table)
{
    
}
void eq_class::validate(TypeTable& type_table)
{
    
}
void leq_class::validate(TypeTable& type_table)
{
    
}
void comp_class::validate(TypeTable& type_table)
{
    
}
void int_const_class::validate(TypeTable& type_table)
{
    
}
void bool_const_class::validate(TypeTable& type_table)
{
    
}
void string_const_class::validate(TypeTable& type_table)
{
    
}
void new__class::validate(TypeTable& type_table)
{
    
}
void isvoid_class::validate(TypeTable& type_table)
{
    
}
void no_expr_class::validate(TypeTable& type_table)
{
    
}
void object_class::validate(TypeTable& type_table)
{
    
}



//////////////////////////////////
//    Validation stages 
//////////////////////////////////

/*************Program Node*******************/
void program_class::redefintions_detection()
{
    Class_ dup = classes_find_duplicates(classes);
    if(dup)
    {
        ClassRedefinitionError err(dup, dup);
        RAISE_FATAL(err);
    }
}
void program_class::missing_main_detection()
{
    if(!has_main(classes))
    {
        UndefinedMainError err;
        RAISE_FATAL(err);
    }
}
void program_class::cycle_detection()
{
    UnionFind uf(classes);
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Class_ class_ = classes->nth(i);
        Symbol name = class_->get_name();
        Symbol parent = class_->get_name();
        if(parent)
        {
            if(!uf.disjoint(name, parent))
            {
                CyclicClassError err(class_, class_);
                RAISE_FATAL(err);
            }    
            uf.union_components(name, parent);
        }
    }
}


/************ Class Node ***************/
bool class__class::is_main()
{
    return idtable.add_string("Main") == name;
}			
void class__class::undefined_type_detection(TypeTable& tb)
{
    if(!tb.contains(parent))
    {
        UndefinedTypeError err(this, this, parent);
        RAISE_FATAL(err);
    }
}		
void class__class::name_reserved_detection(TypeTable& tb)
{
    if(tb.is_reserved_type(name))
    {
        ReservedClassDeclarationError err(this, this, name);
        RAISE_FATAL(err);
    }
}
void class__class::inheritance_reserved_detection(TypeTable& tb)
{
    if(tb.is_reserved_type(parent))
    {
        ReservedInheritanceError err(this, this, parent);
        RAISE_FATAL(err);
    }
}
void class__class::basic_class_inheritance_detection(TypeTable& tb)
{
    if(tb.is_basic_type(parent))
    {
        BasicClassInheritanceError err(this, this, parent);
        RAISE_FATAL(err);
    }
}	
void class__class::builtin_class_redefinition(TypeTable& tb)
{
    if(tb.is_built_in_type(name))
    {
        BasicClassRedefinitionError err(this, this);
        RAISE_FATAL(err);
    }
}		
void class__class::feature_redefinition_detection()
{
    unordered_set<Symbol> defined;
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Feature feature = features->nth(i);
        if(SET_CONTAINS(defined, feature->get_name()))
        {
            handle_duplicate_feature(feature);
        }
        defined.insert(feature->get_name());
    }
}

/*******Method Node********/
void method_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    // Methods are allowed to have SELF_TYPE as return or any other Type
    // but cannot have self as a name
    resreved_id_misuse_check(this, typetable, name, containing_class);

}
void method_class::undefined_types_detection(TypeTable& typetable)
{
    undefined_types_check(this, typetable, return_type, containing_class);
}
void method_class::formal_redefinition_detection(TypeTable& typetable)
{
    unordered_set<Symbol> defined;
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Formal formal = formals->nth(i);
        if(SET_CONTAINS(defined, formal->get_name()))
        {
            handle_duplicate_formal(formal);
        }
        defined.insert(formal->get_name());
    }
}


/***************Attribute Node******************/
void attr_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    resreved_id_misuse_check(this,  typetable,  name, containing_class);
}
void attr_class::undefined_types_detection(TypeTable& typetable)
{
    undefined_types_check(this, typetable, type_decl, containing_class);
}
void attr_class::formal_redefinition_detection(TypeTable& typetable)
{

}


/****************Formals Node************************/
void formal_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    resreved_id_misuse_check(this,  typetable, name, containing_class);
}

void formal_class::undefined_types_detection(TypeTable& typetable)
{
    undefined_types_check(this, typetable, type_decl, containing_class);
}
void formal_class::reserved_type_misuse_detection(TypeTable& typetable)
{
    resreved_type_misuse_check(this, typetable, type_decl, containing_class);
}
//////////////////////////////////
//
// Helpers for the stages
//
//////////////////////////////////
Class_ classes_find_duplicates(Classes classes)
{
    unordered_set<Symbol> defined;
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Class_ class_ = classes->nth(i);
        if(SET_CONTAINS(defined, class_->get_name()))
            return class_;
        defined.insert(class_->get_name());
    }
    return NULL;
}


bool has_main(Classes classes)
{
    bool ans = false;
    int n = classes->len();
    for(int i = 0; i < n; i++)
        ans = ans || classes->nth(i)->is_main();
    return ans;
}

vector<Symbol> unroll_class_names(Classes classes)
{
    vector<Symbol> symbols;
    int n = classes->len();
    for(int i = 0; i < n; i++)
        symbols.push_back(classes->nth(i)->get_name());
    return symbols;
}


void handle_duplicate_feature(Feature feature)
{
    feature->is_duplicate = true;
    FeatureRedefinitionError err(feature->get_containing_class(), feature, feature->get_name());
    RAISE(err);
}

void handle_duplicate_formal(Formal formal)
{
    formal->is_duplicate = true;
    FeatureRedefinitionError err(formal->get_containing_class(), formal, formal->get_name());
    RAISE(err);
} 

void undefined_types_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(!typetable.contains(name))
    {
        UndefinedTypeError err(containing_class, node, name);
        RAISE(err);
    }
}

void resreved_id_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(typetable.is_reserved_identifier(name))
    {
        ReservedIdentifierMisuseError err(containing_class, node, name);
        RAISE(err);
    }
}

void resreved_type_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(typetable.is_reserved_type(name))
    {
        ReservedIdentifierMisuseError err(containing_class, node, name);
        RAISE(err);
    }
}