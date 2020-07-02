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

#define OBJECT idtable.add_string("Object")

using namespace std;


// prototypes
Class_ classes_find_duplicates(Classes classes);
bool has_main(Classes classes);
void handle_duplicate_feature(Feature feature);
void handle_duplicate_formal(Formal formal);

// these checks return true if the an error was detected
bool undefined_types_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);
bool resreved_id_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);
bool resreved_type_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class);



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
void Expression_class::validate(TypeTable& type_table)
{
    reserved_symbols_misuse_detection(type_table);
    undefined_types_detection(type_table);
}


void branch_class::validate(TypeTable& type_table)
{
    reserved_symbols_misuse_detection(type_table);
    undefined_types_detection(type_table);
}

//////////////////////////////////
//    Validation stages 
//////////////////////////////////

/*************Program Node*******************/
void program_class::redefintions_detection()
{
    unordered_set<Symbol> defined;
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Class_ class_ = classes->nth(i);
        if(SET_CONTAINS(defined, class_->get_name()))
            class_->duplication_detected();
        defined.insert(class_->get_name());
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
            feature->duplication_detected();
        defined.insert(feature->get_name());
    }
}
void class__class::duplication_detected()
{
    this->faulty = true;
    ClassRedefinitionError err(this, this);
    RAISE_FATAL(err);
}

/********Feature Node*******/
void Feature_class::duplication_detected()
{
    faulty = true;
    FeatureRedefinitionError err(containing_class, this, get_name());
    RAISE(err);
}

/*******Method Node********/
void method_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    // Methods are allowed to have SELF_TYPE as return or any other Type
    // but cannot have self as a name
    faulty = resreved_id_misuse_check(this, typetable, name, containing_class);

}
void method_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, return_type, containing_class);
    if(err) 
        return_type = OBJECT;
}
void method_class::formal_redefinition_detection(TypeTable& typetable)
{
    unordered_set<Symbol> defined;
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Formal formal = formals->nth(i);
        if(SET_CONTAINS(defined, formal->get_name()))
            formal->duplication_detected();
        defined.insert(formal->get_name());
    }
}


/***************Attribute Node******************/
void attr_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    faulty = resreved_id_misuse_check(this,  typetable,  name, containing_class);
}
void attr_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type_decl, containing_class);
    if(err)
        type_decl = OBJECT;
}
void attr_class::formal_redefinition_detection(TypeTable& typetable)
{

}


/****************Formals Node************************/
void formal_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    faulty = resreved_id_misuse_check(this,  typetable, name, containing_class);
}

void formal_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type_decl, containing_class);
    if(err)
        type_decl = OBJECT;
}
void formal_class::reserved_type_misuse_detection(TypeTable& typetable)
{
    bool err = resreved_type_misuse_check(this, typetable, type_decl, containing_class);
    if(err)
        type_decl = OBJECT;
}

void formal_class::duplication_detected()
{
    faulty = true;
    FormalRedefinitionError err(containing_class, this, name);
    RAISE(err);
}
/********************Assign Node**********************/
void assign_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    // self cannot be assigned
    faulty = resreved_id_misuse_check(this, typetable,  name,  containing_class);
}
void assign_class::undefined_types_detection(TypeTable& typetable)
{

}

/****************Static Dispatch***********************/
void static_dispatch_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    bool err = resreved_type_misuse_check(this, typetable, type_name,containing_class);
    if(err)
        type_name = OBJECT;
    faulty = resreved_id_misuse_check(this, typetable, name, containing_class);
}

void static_dispatch_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type_name, containing_class);
    if(err)
        type_name = OBJECT;
}

/*************Dynamic Dispatch************************/
void dispatch_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    bool err = resreved_type_misuse_check(this, typetable, type_name,containing_class);
}

void dispatch_class::undefined_types_detection(TypeTable& typetable)
{

}
/*************conditional**************************/

void cond_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void cond_class::undefined_types_detection(TypeTable& typetable)
{

}

/*************Loop*********************************/
void loop_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void loop_class::undefined_types_detection(TypeTable& typetable)
{

}

/*************Block******************************/

void block_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void block_class::undefined_types_detection(TypeTable& typetable)
{

}

/*************Let*******************************/

void let_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    faulty = resreved_id_misuse_check(this, typetable, identifier, containing_class);
}

void let_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type, containing_class);
    if(err)
        type = OBJECT;
}

/**********TypeCase********************************/

void typcase_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void typcase_class::undefined_types_detection(TypeTable& typetable)
{

}


/**********CaseBranch*******************************/
void branch_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    resreved_id_misuse_check(this, typetable, name, containing_class);
}

void branch_class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type_decl, containing_class);
    if(err)
        type_decl = OBJECT;
}

/**********new*************************************/
void new__class::reserved_symbols_misuse_detection(TypeTable& typetable)
{
    
}

void new__class::undefined_types_detection(TypeTable& typetable)
{
    bool err = undefined_types_check(this, typetable, type, containing_class);
    if(err)
        type = OBJECT;
}


/********isvoid***********************************/
void isvoid_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void isvoid_class::undefined_types_detection(TypeTable& typetable)
{

}

/********plus**************************************/
void plus_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void plus_class::undefined_types_detection(TypeTable& typetable)
{

}

/********Minus**************************************/
void sub_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void sub_class::undefined_types_detection(TypeTable& typetable)
{

}


/********Multiply***********************************/
void mul_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void mul_class::undefined_types_detection(TypeTable& typetable)
{

}

/*********division**********************************/
void divide_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void divide_class::undefined_types_detection(TypeTable& typetable)
{

}

/*********compliment***************************************/
void comp_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void comp_class::undefined_types_detection(TypeTable& typetable)
{

}

/*******Less than**********************************/
void lt_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void lt_class::undefined_types_detection(TypeTable& typetable)
{

}


/********less than or Equal***************************/
void leq_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void leq_class::undefined_types_detection(TypeTable& typetable)
{

}

/*******Equals***************************************/
void eq_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void eq_class::undefined_types_detection(TypeTable& typetable)
{

}

/******negation******************************************/
void neg_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void neg_class::undefined_types_detection(TypeTable& typetable)
{

}


/******expr*********************************************/
void object_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}
void object_class::undefined_types_detection(TypeTable& typetable)
{

}

/*******Integer*****************************************/
void int_const_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void int_const_class::undefined_types_detection(TypeTable& typetable)
{

}

/*******String*****************************************/
void string_const_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void string_const_class::undefined_types_detection(TypeTable& typetable)
{

}

/*******bool*******************************************/
void bool_const_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void bool_const_class::undefined_types_detection(TypeTable& typetable)
{

}

/******no expr******************************************/
void no_expr_class::reserved_symbols_misuse_detection(TypeTable& typetable)
{

}

void no_expr_class::undefined_types_detection(TypeTable& typetable)
{

}

//////////////////////////////////
//
// Helpers for the stages
//
//////////////////////////////////


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


bool undefined_types_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(!typetable.contains(name))
    {
        UndefinedTypeError err(containing_class, node, name);
        RAISE(err);
        return true;
    }
    return false;
}

bool resreved_id_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(typetable.is_reserved_identifier(name))
    {
        ReservedIdentifierMisuseError err(containing_class, node, name);
        RAISE(err);
        return true;
    }
    return false;
}

bool resreved_type_misuse_check(tree_node* node, TypeTable& typetable, Symbol name, Class_ containing_class)
{
    if(typetable.is_reserved_type(name))
    {
        ReservedIdentifierMisuseError err(containing_class, node, name);
        RAISE(err);
        return true;
    }
    return false;
}