///////////////////////////////////////////////////////////////
// ObjectPrototype
//
// A blueprint for an Object of a certain COOL class
// The attributes in this class includes the inherited ones
//////////////////////////////////////////////////////////////

#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H


#include <list>
#include "ancestors-table.h"
#include "methods-table.h"

using namespace std;


class ObjectPrototype
{
    private:
        string Olabel;
        int Otag;
        std::list<attr_class*> attrs;
        AncestorsTable ancestors_table;
        MethodsTable method_table;
    public:
        /**
          * @brief instantiates an object prototype for the given class 
          * @param Class_ the class which this prototype belongs to
          */ 
        ObjectPrototype(Class_ class_);
        /**
          * @brief copies the the object prototype of the parent including the 
          *        AncestorsTable and the MethodTable
          * @effects: adds all the attributes, methods and ancestors to this object
          * @modifies: this, ancestors, methodtable
          * @param ObjectPrototype the objectprototype of the parent class
          */
        void copy_parent_object(ObjectPrototype& parent_prot);

        string label();
        int tag();
        std::list<attr_class*> attributes();
        
};

#endif /*OBJECT_PROTOTYPE_H*/

