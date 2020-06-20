#include <exceptions.h>

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////
ostream& SemantExceptionHandler::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& SemantExceptionHandler::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& SemantExceptionHandler::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 

