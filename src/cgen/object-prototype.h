///////////////////////////////////////////////////////////////
// ObjectPrototype
//
// A blueprint for an Object of a certain COOL class
// The attributes in this class includes the inherited ones
//////////////////////////////////////////////////////////////

#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H


#include <vector>
#include "code-container.h"
#include "ancestors-table.h"
#include "methods-table.h"

#include "emit.h"

#define OBJ_HEADER_SIZE 3
#define INT_OBJ_SIZE 4

using namespace std;

class StaticMemory;
class MemoryManager;
class Register;
class DefaultValue;

class ObjectPrototype
{
    private:
      string name_attr;
      string label_attr;
      int tag_attr = 0;
      vector<attr_class*> attrs_attr;
      vector<attr_class*> self_attrs_attr;
      AncestorsTable ancestors_table_attr;
      MethodsTable methods_table_attr;
      int depth_attr;

    protected:
      DefaultValue* default_value_attr;
    
    public:
      /**
        * @brief creates an empty object with tag -1 and label empty
        */ 
      ObjectPrototype();
      virtual ~ObjectPrototype();
      /**
        * @brief instantiates an object prototype for the given class 
        * @param Class_ the class which this prototype belongs to
        * @param Features the features of the class
        * @param parent_obj_prot the object prototype of the parent
        */ 
      ObjectPrototype(Class_ class_, int tag, ObjectPrototype& parent_obj_prot);

      string name();
      string label();
      int tag();
      int depth();
      vector<attr_class*> attributes();
      vector<attr_class*> self_attributes();
      MethodsTable& methods_table();
      AncestorsTable& ancestors_table();
      DefaultValue* default_value();
      
      virtual void cgen(CodeContainer& ccon, StaticMemory& stat_mem);
};

class SystemObjectPrototype : public ObjectPrototype
{
  public:
    void cgen(CodeContainer& ccon, StaticMemory& stat_mem);
};

#endif /*OBJECT_PROTOTYPE_H*/

