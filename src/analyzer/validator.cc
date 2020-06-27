#include "type-table.h"
#include <cool-tree.h>
#include <unordered_map>
#include <class-tree.h>
#include <semant-errors.h>

#define RAISE_FATAL(err) \
SemantErrorHandler& sem_err = SemantErrorHandler::instance();\
sem_err.report_fatal((err));

using namespace std;


// prototypes
void raise_main_error();



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
    
}




////////////////////////////////////////////
// Program_class
// Validations on classes
////////////////////////////////////////////



//////////////////////////////////
// Helpers for raising errors
/////////////////////////////////
