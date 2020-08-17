///////////////////////////////////////////////////////////////
// ObjectPrototype
//
// A blueprint for an Object of a certain COOL class
// The attributes in this class includes the inherited ones
//////////////////////////////////////////////////////////////

#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H


#include <vector>
#include "ancestors-table.h"
#include "methods-table.h"

using namespace std;


class ObjectPrototype
{
    private:
        string label_attr;
        int tag_attr;
        vector<attr_class*> attrs_attr;
        AncestorsTable ancestors_table_attr;
        MethodsTable methods_table_attr;
    public:
        /**
          * @brief creates an empty object with tag -1 and label empty
          */ 
        ObjectPrototype();
        /**
          * @brief instantiates an object prototype for the given class 
          * @param Class_ the class which this prototype belongs to
          * @param Features the features of the class
          * @param parent_obj_prot the object prototype of the parent
          */ 
        ObjectPrototype(Class_ class_, Features features, ObjectPrototype& parent_obj_prot);

        string label();
        int tag();
        vector<attr_class*> attributes();
        
        MethodsTable& methods_table();
        AncestorsTable& ancestors_table();
        
};

#endif /*OBJECT_PROTOTYPE_H*/

