#include <class-table.h>
#include <cool-tree.h>
#include <unordered_set>
#include <exceptions.h>


#define MAP_CONTAINS(map, element) (map.find(element) != map.end())

// prototypes
void inheritance_from_basic_classes_detection(Classes classes);
void inheritance_from_undefined_class(Classes classes);
void redefinition_of_classes_detection(Classes classes);
void redefinition_of_basic_classes_detection(Classes classes);


void ClassTable::init(Classes classes)
{
    assert(!is_init);
    initialize_constants();
    // before installing basic classes there better 
    // be no definitions for them
    check_for_invalid_definitions(classes);
    classes = install_basic_classes(classes);
    check_for_invalid_inheritance(classes);

    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Class_ cur_class = classes->nth(i);
        this->classes[cur_class->get_name()] = cur_class;
    }
    is_init = true;
}





void ClassTable::check_for_invalid_inheritance(Classes classes)
{
    inheritance_from_basic_classes_detection(classes);
    inheritance_from_undefined_class(classes);
}

void ClassTable::check_for_invalid_definitions(Classes classes)
{
    redefinition_of_basic_classes_detection(classes);
    redefinition_of_classes_detection(classes);
}








//////////////////////////////////////
// 
//  Installing basic Classes
//
/////////////////////////////////////
// use this to initialize the inheritence tree
Classes ClassTable::install_basic_classes(Classes classes) {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copyy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
    Class_ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);

            classes = append_Classes(classes, single_Classes(Object_class));
            classes = append_Classes(classes, single_Classes(IO_class));
            classes = append_Classes(classes, single_Classes(Int_class));
            classes = append_Classes(classes, single_Classes(Bool_class));
            classes = append_Classes(classes, single_Classes(Str_class));
            return classes;

}

/*****************************************
 *          Helper functions             *
 *****************************************/
void inheritance_from_basic_classes_detection(Classes classes)
{
    unordered_set<Symbol> basic_classes = {Int, Str, Bool};
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Class_ cur_class = classes->nth(i);
        if(MAP_CONTAINS(basic_classes, cur_class->get_parent()))
        {
            throw BasicClassInheritanceException(cur_class->get_name(), cur_class->get_parent());
        }
    }
}

void inheritance_from_undefined_class(Classes classes)
{
    int n = classes->len();
    unordered_set<Symbol> classes_symbols;
    classes_symbols.insert(No_class); // for the object class
    for(int i = 0; i < n; i++)
    {
        Class_ cur_class = classes->nth(i);
        Symbol name = cur_class->get_name();
        classes_symbols.insert(name);
    }

    for(int i = 0; i < n; i++)
    {
        Class_ cur_class = classes->nth(i);
        Symbol parent = cur_class->get_parent();
        if(!MAP_CONTAINS(classes_symbols, parent))
        {
            throw UndefinedClassException(cur_class->get_name(), parent);
        }
    }
}

void redefinition_of_basic_classes_detection(Classes classes)
{
    unordered_set<Symbol> basic_classes = {Object, IO, Int, Str, Bool};
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Symbol cur_class = classes->nth(i)->get_name();
        if(MAP_CONTAINS(basic_classes, cur_class))
        {
            throw BasicClassRedefinitionException(cur_class);
        }
    }

}

void redefinition_of_classes_detection(Classes classes)
{
    unordered_set<Symbol> set;
    int n = classes->len();
    for(int i = 0; i < n; i++)
    {
        Symbol name = classes->nth(i)->get_name();
        if(MAP_CONTAINS(set, name))
        {
            throw ClassRedefinitionException(name);
        }
        set.insert(name);
    }
}

