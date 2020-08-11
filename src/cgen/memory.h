/////////////////////////////////////////////////////
// This class represents an abstract memory slot
// The memory slot can be a register and it could be 
// a main memory location. Each MemorySlot Object has 
// a corresponding register. For the Register class 
// the corresponding Register is itself. For the 
// RamMemorySlot, the corresponding register is $t0
/////////////////////////////////////////////////////

#ifndef MEMORY_H
#define MEMORY_H

#include "code-container.h"

class Register;
class RamMemLoc;


class MemSlot 
{
    public:
    /**
      * @brief generates the code that loads this memory location into a register
      * @modifies: CodeContainer
      * @param CodeContainer
      * @returns the register that stores the code container
      */
    virtual Register* load(CodeContainer& ccon) = 0;

    /**
      * @brief generates the code that saves the data in the 
      *        corresponding register
      * @modifies: CodeContainer
      * @param CodeContainer
      */
    virtual void save(CodeContainer& ccon) = 0;
};

class Register : public MemSlot 
{
    private:
        string name; 
    public:
        Register(string name);
        string get_name();
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon);
};

class RamMemLoc : public MemSlot 
{
    private:
        Register* address;
        Register* t0;
        int offset;
    public:
        RamMemLoc(Register* address, Register* t0, int offset);
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon);
};




#endif /*MEMORY_H*/