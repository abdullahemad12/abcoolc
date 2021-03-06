/***************************************************************
 *  Any Error thrown by the semantic anaylzer              *
 *  must inherit this class. It contians two main              *
 *  data fields:                                               *
 *  Class_ faulty_class: the class at which the error occured  *
 *  msg: the error message accessible through what() method    *
 ***************************************************************/
#ifndef _SEMANT_ERRORS_H_
#define _SEMANT_ERRORS_H_

#include <string>
#include <sstream>
#include <tree.h>
#include <cool-tree.h>
#include <vector>
#include <ostream>




using namespace std;

class SemantError
{
    protected:
        Class_ class_; 
        tree_node* faulty_node;
        stringstream msg;
        SemantError(Class_ class_, tree_node* faulty_node) : class_(class_), faulty_node(faulty_node) { }
    public:
        Class_ get_class(void) { return class_; }
        tree_node* get_faulty_node(void) { return faulty_node; }
        string what(void) { return msg.str(); } ; 
};
/**********************************************
 * Errors for malformed inheritance graph. *
 * There are only three possible errors when   *
 * building the inheritance:                   *
 *  1)  A cycle was detected in the graph      *
 *  2)  A class was defined multiple times with*
 *      the same name                          *
 *  3) A class was referenced as a parent but  *
 *     was not actually defined                * 
 ***********************************************/

class ClassRedefinitionError : public SemantError 
{
    public:
        ClassRedefinitionError(Class_ class_, tree_node* faulty_node);
};

class CyclicClassError : public SemantError
{   
    public:
        CyclicClassError(Class_ class_, tree_node* faulty_node);
};

class UndefinedClassError : public SemantError
{
    public:
    UndefinedClassError(Class_ class_, tree_node* faulty_node, Symbol undefined_class);
};

class BasicClassRedefinitionError : public SemantError
{
    public:
        BasicClassRedefinitionError(Class_ class_, tree_node* faulty_node);
};

class BasicClassInheritanceError : public SemantError
{
    public:
        BasicClassInheritanceError(Class_ class_, tree_node* faulty_node, Symbol basic_class);
};

class ReservedInheritanceError : public SemantError
{
    public:
        ReservedInheritanceError(Class_ class_, tree_node* faulty_node, Symbol reserved);
};

class ReservedClassDeclarationError : public SemantError
{
    public: 
        ReservedClassDeclarationError(Class_ class_, tree_node* faulty_node, Symbol reserved);
};

class ReservedIdentifierMisuseError : public SemantError 
{
    public:
        ReservedIdentifierMisuseError(Class_ class_, tree_node* faulty_node, Symbol reserved);
};

class UndefinedMainMethodError : public SemantError
{
    public:
        UndefinedMainMethodError(Class_ class_, tree_node* faulty_node);
};
class UndefinedMainError
{
    public:
        string what(void);

};
/********************************************
 * Errors for semantic analysis         *
 * There are five possible exceptios        *
 * that could occur when performing         *
 * semantic analysis:                       *
 *  1) an attribute was defined multiple    *
 *     times                                *
 *  2) an attribute referenced but not      *
 *     defined                              *
 *  3) a method was defined multiple times  *
 *  4) a method referenced but not defined  *
 *  5) a type mismatch                      *
 ********************************************/


class TypeMismathcError : public SemantError
{
    public:
    TypeMismathcError(Class_ faulty_class, tree_node* faulty_node, Symbol faulty_symbol, Symbol expected_symbol);
};
class UndefinedTypeError : public SemantError
{
    public:
    UndefinedTypeError(Class_ class_, tree_node* faulty_node, Symbol type);
};

class SelfTypeAsArgumentError: public SemantError
{
    public:
        SelfTypeAsArgumentError(Class_ class_, tree_node* faulty_node);
};

class UnexpectedNumberOfArgsError : public SemantError
{
    public:
        UnexpectedNumberOfArgsError(Class_ class_, tree_node* faulty_node, int n_expected, int n_given);
};

class UndefinedIdentifierError : public SemantError
{
    public:
        UndefinedIdentifierError(Class_ class_, tree_node* faulty_node, Symbol identifier);
};


class UndefinedMethodError : public SemantError
{
    public:
    UndefinedMethodError(Class_ class_, tree_node* faulty_node, Symbol method);
};

class FeatureRedefinitionError : public SemantError
{
    public:
    FeatureRedefinitionError(Class_ class_, tree_node* faulty_node, Symbol identifier);
};


class InconsistentSignatureError : public SemantError
{
    public:
        InconsistentSignatureError(Class_ class_, tree_node* faulty_node, Symbol method);
};

class InvalidDispatchError : public SemantError
{
    public:
        InvalidDispatchError(Class_ class_, tree_node* faulty_node, Symbol undefined_class);
};

class InheritanceMismatchError : public SemantError
{
    public:
       InheritanceMismatchError(Class_ class_, tree_node* faulty_node, Symbol base, Symbol derived);
};

class FormalRedefinitionError : public SemantError
{
    public: 
        FormalRedefinitionError(Class_ class_, tree_node* faulty_node, Symbol faulty_formal);
};

class InvalidMainMethodSignatureError : public SemantError
{
    public:
        InvalidMainMethodSignatureError(Class_ class_, tree_node* faulty_node);
};


class DuplicateCaseBranchError : public SemantError 
{
    public:
        DuplicateCaseBranchError(Class_ class_, tree_node* faulty_node, Symbol type);
};

class ConditionTypeError : public SemantError
{
    public:
        ConditionTypeError(Class_ class_, tree_node* faulty_node, Symbol type);
};

class NonBasicTypeError : public SemantError
{
    public:
        NonBasicTypeError(Class_ class_, tree_node* faulty_node, Symbol type);
};

class EqualityTypeMismatchError : public SemantError
{
    public:
        EqualityTypeMismatchError(Class_ class_, tree_node* faulty_node, Symbol type1, Symbol type2);
};


/*********************************************************************************************
 * SemantErrorHandler                                                                *
 * This singleton class serves as a container for the Errors thrown. Any analysis        *
 * Error Must be thrown through this Other Errors are to be thrown normally          *
 * The reason being that traversing the tree should not be halted after hitting an error to  *
 * catch as many errors as possible. Moreover, errors must be store some where so it can     *
 * be reported later on.                                                                     *
 *                                                                                           *
 * For other semantic errors, it is okay to halt the execution after hitting on of them      *
 *********************************************************************************************/
class SemantErrorHandler
{
    private:
        vector<SemantError*> errors;
        int semant_errors;
        ostream& error_stream;
        
        /*Error reporting helper*/
        std::ostream& semant_error();
        std::ostream& semant_error(Class_ c);
        std::ostream& semant_error(Symbol filename, tree_node *t);
        
        SemantErrorHandler(void) : semant_errors(0), error_stream(cerr) { }
        ~SemantErrorHandler(void);
        /*delete those methods to avoid unwanted errors */
        SemantErrorHandler(SemantErrorHandler const&) = delete;
        void operator=(SemantErrorHandler const&) = delete;
        
        void report_all();
        /**
          * @brief sorts the errors according to their line number 
          * @effects: reorders the errors in the container
          * @modifies: this 
          */ 
        void sort();

    public:
        static SemantErrorHandler& instance()
        {
            static SemantErrorHandler t;
            return t;
        }

        /**
          * @brief reports a given error to std::cerr
          * @param SemantError the error to be reported
          * @modifies: this 
          */
        void report(SemantError* err);
        /**
          * @brief reports a single Error and then terminates the program with
          *        an error code
          * @effects: terminates the program after reporting the error
          * @param SemantError the graph Error to be reported
          */
        void report_fatal(SemantError& err);
        void report_fatal(UndefinedMainError& err);

        /**
          * @brief terminates the program with an exit code of 1 if
          *        one or more errors were reported
          * @effects: terminates the program
          */
        void terminate_on_errors();
        
};

#define RAISE_FATAL(err) \
SemantErrorHandler& sem_err = SemantErrorHandler::instance();\
sem_err.report_fatal((err));

#define RAISE(err) \
SemantErrorHandler& sem_err = SemantErrorHandler::instance();\
sem_err.report((err));

#endif /*_SEMANT_ERRORS_H_*/
