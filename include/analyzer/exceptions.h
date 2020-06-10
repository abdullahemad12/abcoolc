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
class semant_exception : std::exception
{
    Class_ faulty_class;
    protected:
        std::stringstream msg;
        semant_exception(Class_ faulty_class) : faulty_class (faulty_class) { }
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
class graph_exception : public semant_exception
{
    protected:
        graph_exception(Class_ faulty_class) : semant_exception(faulty_class) { }   
};

class class_redefinition_exception : public graph_exception 
{
    class_redefinition_exception(Class_ faulty_class) : graph_exception(faulty_class) { 
        semant_exception::msg << "class " << faulty_class->get_name() << " is redefined multiple times";
    }
};

class cyclic_class_exception : public graph_exception
{
    cyclic_class_exception(Class_ faulty_class) : graph_exception(faulty_class) { 
        semant_exception::msg << "class " << faulty_class->get_name() << " causes a dependency cycle";
    }   
};

class undefined_class_exception : public graph_exception
{
    undefined_class_exception(Class_ faulty_class) : graph_exception(faulty_class) {
        semant_exception::msg << "class " << faulty_class->get_name() << " is undefined";
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
class analysis_exception : public semant_exception
{   
    private:
        tree_node* faulty_node;
    
    protected:
        analysis_exception(Class_ faulty_exception, tree_node* faulty_node) : semant_exception(faulty_exception) 
        { 
            this->faulty_node = faulty_node;
        }
        
    public:
        tree_node* get_faulty_node(void) { return faulty_node; }
};

class scope_exception : public analysis_exception
{
    protected:
        scope_exception(Class_ faulty_class, tree_node* faulty_node) : analysis_exception(faulty_class, faulty_node) {  }
        
};

class type_exception : public analysis_exception
{
    type_exception(Class_ faulty_class, tree_node* faulty_node, Symbol faulty_symbol, Symbol expected_symbol) :
                   analysis_exception(faulty_class, faulty_node) 
    {
       semant_exception::msg <<  "expected type " << expected_symbol << " but got " << faulty_symbol;
    }
};

class undefined_attribute_exception : public scope_exception
{
        undefined_attribute_exception(Class_ faulty_class, tree_node* faulty_node, Symbol identifier) :    
                                        scope_exception(faulty_class, faulty_node)
        {
            semant_exception::msg << "attribute " << identifier << " is not defined in this context";
        }
};


class undefined_method_exception : public scope_exception
{
    undefined_method_exception(Class_ faulty_class, tree_node* faulty_node, Symbol method) :
                              scope_exception(faulty_class, faulty_node)
    {
        semant_exception::msg << "method " << method << " is not defined in this context";
    }
};

class attribute_redefinition_exception : public scope_exception
{
    attribute_redefinition_exception(Class_ faulty_class, tree_node* faulty_node, Symbol identifier) : 
                                     scope_exception(faulty_class, faulty_node)
    {
        semant_exception::msg << "attribute " << identifier << "is defined multiple times";
    }
};

class method_redefinition : public scope_exception
{
    method_redefinition(Class_ faulty_class, tree_node* faulty_node, Symbol method) : 
                                     scope_exception(faulty_class, faulty_node)
    {
        semant_exception::msg << "method " << method << "is defined multiple times";
    }
};

