////////////////////////////////////////////////////////////////////
// StaticMemory
//
// Everything that lives in the static memory area of the 
// generated code is managed here. This includes ObjectPrototypes
// and all constants
////////////////////////////////////////////////////////////////////

#include <cool-tree.h>

#ifndef STATIC_MEMORY_H
#define STATIC_MEMORY_H

#include <object-prototype.h>

class StaticMemory 
{
    public:
        /**
          * @brief looks up the object prototype of a given class 
          * @requires: StaticMemory to be initialized correctly
          * @param Symbol the name of the class to be looked up
          * @returns the object prototype of the given class 
          */
        ObjectPrototype& lookup_objectprot(Symbol class_name);
};

#endif /* STATIC_MEMORY_H*/