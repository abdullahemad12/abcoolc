#include <class-validator.h>
#include <type-table.h>
#include <cool-tree.h>
#include <unordered_map>
#include <class-tree.h>
#include <semant-errors.h>

using namespace std;
// prototypes
Classes install_basic_classes(Classes classes);

Classes validate(Classes classes)
{
    initialize_constants();
    exit(1);
    return classes;
}

//////////////////////////////////////
// 
//  Installing basic Classes
//
/////////////////////////////////////
// use this to initialize the inheritence tree
Classes install_basic_classes(Classes classes) 
{

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


unordered_map<Symbol, int> map_class_to_int(Classes classes)
{
    int n = classes->len();
    unordered_map<Symbol, int> map; 
    for(int i = 0; i < n; i++)
        map[classes->nth(i)->get_name()] = i;
    return map;
}

void check_for_cycles(Classes classes)
{

  int n = classes->len();

  auto class_map = map_class_to_int(classes);
  assert((int)class_map.size() == classes->len());

  // Note: n includes the dummy _no_type symbol but it does not really matter as it 
  // does not add a cycle
  UnionFind uf(n);
  SemantErrorHandler& sem_err = SemantErrorHandler::instance();

  for(int i = 0; i < n; i++)
  {
      Class_ class_ = classes->nth(i);
      Symbol cur = class_->get_name();
      Symbol parent = class_->get_parent();
      //cycle detected 
      if(!uf.disjoint(class_map[cur], class_map[parent]))
      {
          CyclicClassError err(class_, class_); 
          sem_err.report_fatal(err);
      }
      uf.union_components(class_map[cur], class_map[parent]);
  }

}