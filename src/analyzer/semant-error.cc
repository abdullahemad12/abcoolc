#include <exceptions.h>
#include <class-table.h>

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

int SemantExceptionHandler::report_all(void)
{
    ClassTable& classtable = ClassTable::instance();
    int n = container.size();
    for(AnalysisException* exp : container)
    {
        Symbol classname = exp->get_faulty_class();
        Symbol filename = classtable[classname]->get_filename();
        tree_node* node = exp->get_faulty_node();
        auto& stream = semant_error(filename, node);
        stream << exp->what();
        delete exp;
    }
    container.clear();
    return n;
}

void SemantExceptionHandler::report_one(Classes classes, GraphException& exp)
{
    Symbol class_name = exp.get_faulty_class();
    int n = 0;
    for(int i = 0; i < n; i++)
    {
        Class_ class_ = classes->nth(i);
        if(class_->get_name() == class_name) {
            auto& err = semant_error(class_);
            err << exp.what();
            break;
        }
    }
}


