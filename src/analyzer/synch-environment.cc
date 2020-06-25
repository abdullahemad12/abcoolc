#include <cool-tree.h>
#include <environment.h>
#include <symtab.h>
#include <exceptions.h>
#include <unordered_set>

#define CONTAINS(set, elem) ((set.find(elem)) != (set.end()))

using namespace std;

// helpers prototypes
vector<Symbol> extract_formals_type(Formals formals);


////////////////////////////////////////////////////////////////
// globla environment
// Adding to this environment happens as a preprocessing step 
// before the semantic analysis begins. Therefore, correctness of the 
// environment should not be assumed
/////////////////////////////////////////////////////////////////

// this is a preprocessing step, thus there is no need for raising 
// an error
void method_class::add_to_global_env(Symbol class_name)
{
    // insert only if the method is not defined.
    Environment& env = Environment::instance();
    MethodEnvironment& menv =  env.get_global_method_env();
    if(!menv.contains(class_name, name))
    {
        vector<Symbol> formal_symbols = extract_formals_type(formals);
        menv.add(class_name, name, formal_symbols, return_type);
    }
}

/*
 * do nothing as attributes are private
 */ 
void attr_class::add_to_global_env(Symbol class_name)
{
    
}

///////////////////////////////////////////////////////////////////////
// local environment
// Check for multiple definition here for the sake consistency
// Modifying this environment happens while the analysis check 
// is carried out. It makes the assumption that all the operations 
// on it were called in the correct order as decided by the program node
/////////////////////////////////////////////////////////////////////////


void method_class::add_to_local_env()
{
    assert(!malformed);
    Symbol class_name = idtable.add_string(LOCAL_TYPE);
    Environment& env = Environment::instance();
    MethodEnvironment& menv = env.get_local_method_env();
    vector<Symbol> formal_symbols = extract_formals_type(formals);
    
    // there is no way to detect if whether, this is overriding 
    // or redefinition. Hence, This is left to the caller to assert
    // however, if this exists, then the signatures must be identical
    if(!menv.contains(class_name, name))
    {
        menv.add(class_name, name, formal_symbols, return_type);
    }
    else 
    {
        MethodEnvironment::Signature& sign = menv.lookup(class_name, name);
        if(sign != *this) // the != operator is overloaded
        {
            raise_inconsistent_signature_error();
            return;
        }
        menv.add(class_name, name, formal_symbols, return_type); 
    }
}

void method_class::remove_from_local_env()
{
    assert(!malformed);
    Symbol class_name = idtable.add_string(LOCAL_TYPE);
    Environment& env = Environment::instance();
    MethodEnvironment& menv = env.get_local_method_env();
    menv.remove(class_name, name);
}

void attr_class::add_to_local_env()
{
    assert(!malformed);
    // because those are features, no feature shall shadow another one 
    Environment& env = Environment::instance();
    ObjectEnvironment& oenv = env.get_local_object_env();
    if(oenv.contains(name))
    {
        raise_redefinition_error();
        return;
    }
    oenv.add(name, type_decl);
  
}

void attr_class::remove_from_local_env()
{
    assert(!malformed);
    Environment& env = Environment::instance();
    ObjectEnvironment& oenv = env.get_local_object_env();
    oenv.remove(name);
}

void formal_class::add_to_local_env()
{
    assert(!malformed);
    // as long as it is unique within the formals, no other condition applies
    Environment& env = Environment::instance();
    ObjectEnvironment& oenv = env.get_local_object_env();
    oenv.add(name, type_decl);
}

void formal_class::remove_from_local_env()
{
    assert(!malformed);
    Environment& env = Environment::instance();
    ObjectEnvironment& oenv = env.get_local_object_env();
    oenv.remove(name);
}


/////////////////////////////////////////
//
//      Method Environment interaction
//
////////////////////////////////////////
void method_class::sync_local_environment()
{
    ObjectEnvironment& oenv = Environment::instance().get_local_object_env();
    unordered_set<Symbol> defined;
    int n = formals->len();
    for(int i = 0; i < n; i++)
    {
        Formal formal = formals->nth(i);
        if(defined.find(formal->get_name()) != defined.end())
        {
            formal->raise_redefinition_error();
        }
        else
        {
            oenv.add(formal->get_name(), formal->get_type_decl());
            defined.insert(formal->get_name());
        }
    }
}

void method_class::clean_local_environment()
{
    ObjectEnvironment& oenv = Environment::instance().get_local_object_env();
    int n = formals->len();
    for(int i = 0; i < n; i++)
    {
        Formal formal = formals->nth(i);
        if(!formal->is_malformed())
            oenv.remove(formal->get_name());
    }
}
/////////////////////////////////////////
//
// Class-Environment interactions
//
/////////////////////////////////////////


/* 
 * this is preprocessing pass that adds features to the global environment
 * no need for error checking
 */ 
void class__class::sync_global_env()
{
    for(int i = 0; i < features->len(); i++)
    {
        Feature feature = features->nth(i);
        features->nth(i)->add_to_global_env(name);
    }
}

/*
 * this is called on the second pass. Error checking is needed in here
 * for detecting malformed feature definitions. Error are passed to the 
 * error handler accordingly without interrupting execution
 */ 
void class__class::sync_local_env()
{
    // stores all the features seen so far
    unordered_set<Symbol> defined;

    // for every feature, raise an error if its redefined 
    // within this class, or add it to the environment otherwise
    for(int i = 0; i  < features->len(); i++)
    {
        Feature feature = features->nth(i);
        if(CONTAINS(defined, feature->get_name()))
        {
            // raise error and pass 
            feature->raise_redefinition_error();
        }
        else // add to the environment
        {
            feature->add_to_local_env();
            defined.insert(feature->get_name());
        }
    }

}

/*
 * this is typically done after this class and all its children
 * has been visited, At this point we dont need its features anymore
 */ 
void class__class::clean_local_env()
{
    for(int i = 0; i  < features->len(); i++)
    {
        Feature feature = features->nth(i);
        if(!feature->is_malformed())
            feature->remove_from_local_env();
    }
}

//////////////////////
//
// polymorphic errors
//
//////////////////////

/**
  * Any raise_exception definition below must raise it's exception through this 
  */
void Feature_class::raise_error (AnalysisException* excep)
{
    malformed = true;
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    sem_err.raise(excep);
}
void Formal_class::raise_error (AnalysisException* excep)
{
    malformed = true;
    SemantExceptionHandler& sem_err = SemantExceptionHandler::instance();
    sem_err.raise(excep);
}

void method_class::raise_redefinition_error()
{
    Environment& env = Environment::instance();
    raise_error(new MethodRedefinitionException(env.current_class, this, name));
}

void method_class::raise_inconsistent_signature_error()
{
    Environment& env = Environment::instance();
    raise_error(new InconsistentSignatureException(env.current_class, this, name)); 
}


void attr_class::raise_redefinition_error()
{
    Environment& env = Environment::instance();
    raise_error(new AttributeRedefinitionException(env.current_class, this, name)); 
}


void formal_class::raise_redefinition_error()
{
    Environment& env = Environment::instance();
    raise_error(new AttributeRedefinitionException(env.current_class, this, name));
}
//////////////////////
// Helpers
//////////////////////
vector<Symbol> extract_formals_type(Formals formals)
{
    vector<Symbol> formal_symbols;
     // no need to store information of the identifiers' names
    for(int i = 0; i < formals->len(); i++)
        formal_symbols.push_back(formals->nth(i)->get_type_decl());

    return formal_symbols;
}
