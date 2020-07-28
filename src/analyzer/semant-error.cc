#include <semant-errors.h>
#include <cool-tree.h>

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

ostream& SemantErrorHandler::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& SemantErrorHandler::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& SemantErrorHandler::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 

void SemantErrorHandler::report(SemantError* err)
{
    errors.push_back(err);
}

void SemantErrorHandler::report_fatal(SemantError& err)
{
    Class_ class_ = err.get_class();
    Symbol filename = class_->get_filename();
    tree_node* node = err.get_faulty_node();
    auto& stream = semant_error(filename, node);
    stream << err.what() << endl;
    terminate_on_errors();
}
void SemantErrorHandler::report_fatal(UndefinedMainError& err)
{
    auto& stream = semant_error();
    stream << err.what() << endl;
    terminate_on_errors();
}

void SemantErrorHandler::terminate_on_errors(void)
{
    report_all();
    if(semant_errors)
    {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

void SemantErrorHandler::report_all()
{
    sort();
    for(auto err : errors)
    {
        Class_ class_ = err->get_class();
        Symbol filename = class_->get_filename();
        tree_node* node = err->get_faulty_node();
        auto& stream = semant_error(filename, node);
        stream << err->what() << endl;
    }
}

void SemantErrorHandler::sort()
{
    for(unsigned int i = 0; i < errors.size(); i++)
    {
        for(unsigned int j = 0; j < errors.size() - 1; j++)
        {
            int cur_line_no = errors[j]->get_faulty_node()->get_line_number();
            int next_line_no = errors[j+1]->get_faulty_node()->get_line_number();
            if( cur_line_no > next_line_no)
            {
                swap(errors[j], errors[j+1]);
            }
        }
    }
}


SemantErrorHandler::~SemantErrorHandler()
{
    for(SemantError* err : errors)
        delete err;
}

/************************************
 * 
 *  constructors for Errors
 * 
 ************************************/


ClassRedefinitionError::ClassRedefinitionError(Class_ class_, tree_node* faulty_node) : SemantError(class_, faulty_node)
{ 
    msg << "class " << class_->get_name() << " is defined multiple times";
}

CyclicClassError::CyclicClassError(Class_ class_, tree_node* faulty_node) : SemantError(class_, faulty_node)
{ 
    msg << "class " << class_->get_name() << " causes a dependency cycle";
}  

UndefinedClassError::UndefinedClassError(Class_ class_, tree_node* faulty_node, Symbol undefined_class) 
                                        : SemantError(class_, faulty_node)
{
    this->msg << "class " << class_->get_name() << 
                            " inherits from undefined class " << undefined_class;
}

BasicClassRedefinitionError::BasicClassRedefinitionError(Class_ class_, tree_node* faulty_node) : SemantError(class_, faulty_node)
{
    msg << "Basic Class " << class_->get_name() << " cannot be redefined"; 
}

BasicClassInheritanceError::BasicClassInheritanceError(Class_ class_, tree_node* faulty_node, Symbol basic_class) 
                                                    : SemantError(class_, faulty_node)
{
    msg << "Class " << class_->get_name() 
        << " cannot inherit from built-in class " << basic_class->get_string();
}

ReservedInheritanceError::ReservedInheritanceError(Class_ class_, tree_node* faulty_node, Symbol reserved)
                                     : SemantError(class_, faulty_node)
{
    msg << "Class " << class_->get_name()
            << " is trying to inherit from reserved type " << reserved;
}

ReservedClassDeclarationError::ReservedClassDeclarationError(Class_ class_, tree_node* faulty_node, Symbol reserved)  
                             : SemantError(class_, faulty_node)
{
    msg << reserved << " cannot be declared as a class";
}


string UndefinedMainError::what(void) 
{ 
    return "Main Class is not defined."; 
}


TypeMismathcError::TypeMismathcError(Class_ class_, tree_node* faulty_node, Symbol faulty_symbol, Symbol expected_symbol) :
                   SemantError(class_, faulty_node) 
{
    msg <<  "The inferred type " << faulty_symbol->get_string()
               << " does not conform with the expected type " << expected_symbol->get_string();
}


UndefinedTypeError::UndefinedTypeError(Class_ class_, tree_node* faulty_node, Symbol type) :
                           SemantError(class_, faulty_node)
{
    msg << type->get_string() << " does not name a valid Type";
}

SelfTypeAsArgumentError::SelfTypeAsArgumentError(Class_ class_, tree_node* faulty_node) :
                                    SemantError(class_, faulty_node) 
{
    msg << "SELF_TYPE cannot be declared as a method argument type";
}

UnexpectedNumberOfArgsError::UnexpectedNumberOfArgsError(Class_ class_, tree_node* faulty_node, int n_expected, int n_given) :
                            SemantError(class_, faulty_node)
{
    msg << "Expects " << n_expected << " arguments but was given " << n_given; 
}

UndefinedIdentifierError::UndefinedIdentifierError(Class_ class_, tree_node* faulty_node, Symbol identifier) :    
                                        SemantError(class_, faulty_node)
{
    msg << "identifier " << identifier << " is not defined in this context";
}

UndefinedMethodError::UndefinedMethodError(Class_ class_, tree_node* faulty_node, Symbol method) :
                            SemantError(class_, faulty_node)
{
    msg << "method " << method << " is not defined in this context";
}

FeatureRedefinitionError::FeatureRedefinitionError(Class_ class_, tree_node* faulty_node, Symbol identifier) : 
                                    SemantError(class_, faulty_node)
{
    msg << "redefinition of feature " << identifier << " is not allowed";
}


InconsistentSignatureError::InconsistentSignatureError(Class_ class_, tree_node* faulty_node, Symbol method) :
                                        SemantError(class_, faulty_node)
{   
    msg << "cannot override method " << method << " with a different signature";
} 

InvalidDispatchError::InvalidDispatchError(Class_ class_, tree_node* faulty_node, Symbol undefined_class) :
                                SemantError(class_, faulty_node)
{   
    msg << "you are trying to call method in undefined Class " << undefined_class;
}

ReservedIdentifierMisuseError::ReservedIdentifierMisuseError(Class_ class_, tree_node* faulty_node, Symbol reserved)
                            : SemantError(class_, faulty_node)
{
    msg << "Reserved identifier " << reserved << " cannot be used in this context";
}


FormalRedefinitionError::FormalRedefinitionError(Class_ class_, tree_node* faulty_node, Symbol faulty_formal)
                        : SemantError(class_, faulty_node)
{
    msg << "Redefinition of method argument " << faulty_formal;
}

UndefinedMainMethodError::UndefinedMainMethodError(Class_ class_, tree_node* faulty_node) 
                        : SemantError(class_, faulty_node)
{
    msg << "Missing the main method in class Main";
}

InvalidMainMethodSignatureError::InvalidMainMethodSignatureError(Class_ class_, tree_node* faulty_node)
                        : SemantError(class_, faulty_node)
{
    msg << "main method should have no arguments";
}

DuplicateCaseBranchError::DuplicateCaseBranchError(Class_ class_, tree_node* faulty_node, Symbol type)
                        : SemantError(class_, faulty_node)
{
    msg << "Type " <<  type << " cannot be defined multiple times within a case expression";
}

InheritanceMismatchError::InheritanceMismatchError(Class_ class_, tree_node* faulty_node, Symbol base, Symbol derived)
                        : SemantError(class_, faulty_node)
{
    msg << "Class " << derived << " does not inherit from class " << base;
}

ConditionTypeError::ConditionTypeError(Class_ class_, tree_node* faulty_node, Symbol type)
                    : SemantError(class_, faulty_node)
{
    msg << "Conditional statement expects a Boolean expression as its condition but got " << type;
}

NonBasicTypeError::NonBasicTypeError(Class_ class_, tree_node* faulty_node, Symbol type)
                    : SemantError(class_, faulty_node)
{
    msg << "Expects the type of the expression to be on of COOL's basic types but got " << type;
}

EqualityTypeMismatchError::EqualityTypeMismatchError(Class_ class_, tree_node* faulty_node, Symbol type1, Symbol type2)
                    : SemantError(class_, faulty_node)
{
    msg << "cannot check equality between types " << type1 << " and " << type2;
}