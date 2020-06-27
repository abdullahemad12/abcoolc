#include "type-table.h"
#include <cool-tree.h>
#include <unordered_map>
#include <class-tree.h>
#include <semant-errors.h>

using namespace std;

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
void program_class::validate_classes(TypeTable& tb)
{
    initialize_constants();
    main_validation(tb);
    class_reserved_keywords_inheritance_validation(tb);
    class_reserved_keywords_definition_validation(tb);
    class_inheritance_validation(tb);
    class_definition_validation(tb);
    unique_class_validation(tb);
    acyclic_inheritance_graph_validation(tb);
}




////////////////////////////////////////////
// Program_class
// Validations on classes
////////////////////////////////////////////
void program_class::main_validation(TypeTable& tb)
{
    SemantErrorHandler& sem_err = SemantErrorHandler::instance();
    bool has_main = false;
    int n = classes->len();

    // note this does not check multiple definitions of main
    for(int i = 0; i < n; i++)
        has_main = has_main || classes->nth(i)->is_main();
    
    if(!has_main)
    {
        UndefinedMainError err;
        sem_err.report_fatal(err);

    }
} 				
void program_class::class_reserved_keywords_inheritance_validation(TypeTable& tb)
{

}	
void program_class::class_reserved_keywords_definition_validation(TypeTable& tb)
{

}	
void program_class::class_inheritance_validation(TypeTable& tb)
{

}	
void program_class::class_definition_validation(TypeTable& tb)
{

}		
void program_class::unique_class_validation(TypeTable& tb)
{

}			
void program_class::acyclic_inheritance_graph_validation(TypeTable& tb)
{

}


