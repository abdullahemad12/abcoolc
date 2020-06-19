/***************************************************************
 *  Any exception thrown by the semantic anaylzer              *
 *  must inherit this class. It contians two main              *
 *  data fields:                                               *
 *  Class_ faulty_class: the class at which the error occured  *
 *  msg: the error message accessible through what() method    *
 ***************************************************************/
#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <exception>
#include <string>
#include <sstream>
#include <tree.h>
#include <cool-tree.h>
#include <vector>
#include <singleton.h>


class SemantException : std::exception
{
    Symbol faulty_class;
    protected:
        std::stringstream msg;
        SemantException(Symbol faulty_class) : faulty_class (faulty_class) { }
    public:
        Symbol get_faulty_class(void) { return faulty_class; }
        const char* what(void) { return msg.str().c_str(); }
};
/**********************************************
 * Exceptions for malformed inheritance graph. *
 * There are only three possible errors when   *
 * building the inheritance:                   *
 *  1)  A cycle was detected in the graph      *
 *  2)  A class was defined multiple times with*
 *      the same name                          *
 *  3) A class was referenced as a parent but  *
 *     was not actually defined                * 
 ***********************************************/
class GraphException : public SemantException
{
    protected:
        GraphException(Symbol faulty_class) : SemantException(faulty_class) { }   
};

class ClassRedefinitionException : public GraphException 
{
    public:
        ClassRedefinitionException(Symbol faulty_class) : GraphException(faulty_class) { 
            ClassRedefinitionException::msg << "class " << faulty_class->get_string() << " is redefined multiple times";
        }
};

class CyclicClassException : public GraphException
{   
    public:
        CyclicClassException(Symbol faulty_class) : GraphException(faulty_class) { 
            SemantException::msg << "class " << faulty_class->get_string() << " causes a dependency cycle";
        }   
};

class UndefinedClassException : public GraphException
{
    public:
    UndefinedClassException(Symbol faulty_class) : GraphException(faulty_class) {
        SemantException::msg << "class " << faulty_class->get_string() << " is undefined";
    }
};

/********************************************
 * Exceptions for semantic analysis         *
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
class AnalysisException : public SemantException
{   
    private:
        tree_node* faulty_node;
    
    protected:
        AnalysisException(Symbol faulty_exception, tree_node* faulty_node) : SemantException(faulty_exception) 
        { 
            this->faulty_node = faulty_node;
        }
        
    public:
        tree_node* get_faulty_node(void) { return faulty_node; }
};

class ScopeException : public AnalysisException
{
    protected:
        ScopeException(Symbol faulty_class, tree_node* faulty_node) : AnalysisException(faulty_class, faulty_node) {  }
        
};

class TypeException : public AnalysisException
{
    public:
    TypeException(Symbol faulty_class, tree_node* faulty_node, Symbol faulty_symbol, Symbol expected_symbol) :
                   AnalysisException(faulty_class, faulty_node) 
    {
       SemantException::msg <<  "expected type " << expected_symbol << " but got " << faulty_symbol;
    }
};

class UndefinedAttributeException : public ScopeException
{
    public:
        UndefinedAttributeException(Symbol faulty_class, tree_node* faulty_node, Symbol identifier) :    
                                        ScopeException(faulty_class, faulty_node)
        {
            SemantException::msg << "attribute " << identifier << " is not defined in this context";
        }
};


class UndefinedMethodException : public ScopeException
{
    public:
    UndefinedMethodException(Symbol faulty_class, tree_node* faulty_node, Symbol method) :
                              ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "method " << method << " is not defined in this context";
    }
};

class attribute_redefinition_exception : public ScopeException
{
    public:
    attribute_redefinition_exception(Symbol faulty_class, tree_node* faulty_node, Symbol identifier) : 
                                     ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "attribute " << identifier << "is defined multiple times";
    }
};

class MethodRedefinition : public ScopeException
{
    public:
    MethodRedefinition(Symbol faulty_class, tree_node* faulty_node, Symbol method) : 
                                     ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "method " << method << "is defined multiple times";
    }
};

class InconsistentSignatureException : public ScopeException
{
    public:
        InconsistentSignatureException(Symbol faulty_class, tree_node* faulty_node, Symbol method) :
                                        ScopeException(faulty_class, faulty_node)
        {   
            SemantException::msg << "cannot override method " << method << " with a different signature";
        }  
};



/*********************************************************************************************
 * SemantExceptionHandler                                                                *
 * This singleton class serves as a container for the exceptions thrown. Any analysis        *
 * Exception Must be thrown through this Other exceptions are to be thrown normally          *
 * The reason being that traversing the tree should not be halted after hitting an error to  *
 * catch as many errors as possible. Moreover, errors must be store some where so it can     *
 * be reported later on.                                                                     *
 *                                                                                           *
 * For other semantic errors, it is okay to halt the execution after hitting on of them      *
 *********************************************************************************************/
class SemantExceptionHandler : Singleton<SemantExceptionHandler>
{
    friend Singleton<SemantExceptionHandler>;
    private:
        std::vector<AnalysisException*> container;
        SemantExceptionHandler(void) { }
    public:
        void raise(AnalysisException* exception) { container.push_back(exception); }
        auto begin() { return container.begin(); }
        auto end() { return container.end(); }
        /**
          * @brief reports all the excptions that were passed to the raise method
          * @modifies: this (clears all the exceptions that were raised)
          * @effects:terminates the program if any errors were raised 
          *          after writing all the errors
          */
        void report_all_if_any(void);
        /**
          * @brief reports a single exception. Typically used for reporting 
          *        graph errors because they are fatal
          * @effects: terminates the program after reporting the error
          * @param GraphException the graph exception to be reported
          */
        void report_one(GraphException& exception);
};
#endif /*EXCEPTIONS_H_*/