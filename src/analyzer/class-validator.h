#ifndef _CLASS_VALIDATOR_H
#define _CLASS_VALIDATOR_H

/////////////////////////////////////////////////////////////////
// This is the code responsible for doing 
// all the validation on the classes. 
// This includes: 
// 1. checking Main class definition
// 2. checking for any undefined types
// 3. checking for misusing the basic classes
// 4. checking for class redefinitions
// 5. checking for cycles in the inheritance graph
// The code should return a new list of classes with all 
// the basic classes installed
////////////////////////////////////////////////////////////////

#include <cool-tree.h>

/**
  * @brief makes sure all the classes are well formed 
  * @effects: may terminate the program if a problem with the classes was detected
  * @returns the list of classes after installing all the basic classes
  */ 
Classes validate(Classes classses);


#endif /*_CLASS_VALIDATOR_H*/