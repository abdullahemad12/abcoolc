#include <exception>
#include <string>
#include <sstream>
#include <tree.h>
#include <cool-tree.h>

/***************************************************************
 *  Any exception thrown by the semantic anaylzer              *
 *  must inherit this class. It contians two main              *
 *  data fields:                                               *
 *  Class_ faulty_class: the class at which the error occured  *
 *  msg: the error message accessible through what() method    *
 ***************************************************************/
class SemantException : std::exception
{
    Class_ faulty_class;
    protected:
        std::stringstream msg;
        SemantException(Class_ faulty_class) : faulty_class (faulty_class) { }
    public:
        Class_ get_faulty_class(void) { return faulty_class; }
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
        GraphException(Class_ faulty_class) : SemantException(faulty_class) { }   
};

class ClassRedefinitionException : public GraphException 
{
    ClassRedefinitionException(Class_ faulty_class) : GraphException(faulty_class) { 
        ClassRedefinitionException::msg << "class " << faulty_class->get_name() << " is redefined multiple times";
    }
};

class CyclicClassException : public GraphException
{
    CyclicClassException(Class_ faulty_class) : GraphException(faulty_class) { 
        SemantException::msg << "class " << faulty_class->get_name() << " causes a dependency cycle";
    }   
};

class UndefinedClassException : public GraphException
{
    UndefinedClassException(Class_ faulty_class) : GraphException(faulty_class) {
        SemantException::msg << "class " << faulty_class->get_name() << " is undefined";
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
        AnalysisException(Class_ faulty_exception, tree_node* faulty_node) : SemantException(faulty_exception) 
        { 
            this->faulty_node = faulty_node;
        }
        
    public:
        tree_node* get_faulty_node(void) { return faulty_node; }
};

class ScopeException : public AnalysisException
{
    protected:
        ScopeException(Class_ faulty_class, tree_node* faulty_node) : AnalysisException(faulty_class, faulty_node) {  }
        
};

class TypeException : public AnalysisException
{
    TypeException(Class_ faulty_class, tree_node* faulty_node, Symbol faulty_symbol, Symbol expected_symbol) :
                   AnalysisException(faulty_class, faulty_node) 
    {
       SemantException::msg <<  "expected type " << expected_symbol << " but got " << faulty_symbol;
    }
};

class UndefinedAttributeException : public ScopeException
{
        UndefinedAttributeException(Class_ faulty_class, tree_node* faulty_node, Symbol identifier) :    
                                        ScopeException(faulty_class, faulty_node)
        {
            SemantException::msg << "attribute " << identifier << " is not defined in this context";
        }
};


class UndefinedMethodException : public ScopeException
{
    UndefinedMethodException(Class_ faulty_class, tree_node* faulty_node, Symbol method) :
                              ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "method " << method << " is not defined in this context";
    }
};

class attribute_redefinition_exception : public ScopeException
{
    attribute_redefinition_exception(Class_ faulty_class, tree_node* faulty_node, Symbol identifier) : 
                                     ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "attribute " << identifier << "is defined multiple times";
    }
};

class MethodRedefinition : public ScopeException
{
    MethodRedefinition(Class_ faulty_class, tree_node* faulty_node, Symbol method) : 
                                     ScopeException(faulty_class, faulty_node)
    {
        SemantException::msg << "method " << method << "is defined multiple times";
    }
};

class InconsistentSignatureException : public ScopeException
{
    InconsistentSignatureException(Class_ faulty_class, tree_node* faulty_node, Symbol method) :
                                     ScopeException(faulty_class, faulty_node)
    {   
        SemantException::msg << "cannot override method " << method << " with a different signature";
    }  
};

