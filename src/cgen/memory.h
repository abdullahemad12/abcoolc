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

#include <ostream>

using namespace std;

//
// register names
//
#define ZERO "$zero"		// Zero register 
#define ACC  "$a0"		// Accumulator 
#define A1   "$a1"		// For arguments to prim funcs 
#define SELF "$s0"		// Ptr to self (callee saves) 
#define T1   "$t1"		// Temporary 1 
#define T2   "$t2"		// Temporary 2 
#define T3   "$t3"		// Temporary 3 
#define SP   "$sp"		// Stack pointer 
#define FP   "$fp"		// Frame pointer 
#define RA   "$ra"		// Return address 



class Register;
class RamMemLoc;
class CodeContainer;

class MemSlot 
{
    private:
        /*used to catch errors*/
        bool valid = true; 


    public:
    
    void set_valid(bool val);
    /**
      * @brief generates the code that loads this memory slot into a register
      * @modifies: CodeContainer
      * @param CodeContainer
      * @returns the register that stores the data
      */
    virtual Register* load(CodeContainer& ccon) = 0;

    /**
      * @brief generates the code that saves the data from a given register in this 
      *        memory slot. If the given memory slot is the same as this, does nothing
      * @modifies: CodeContainer
      * @param CodeContainer
      * @param Register 
      */
    void save(CodeContainer& ccon, Register* src);
};

class Register : public MemSlot 
{
    private:
        string name; 
    public:
        Register(string name);
        string get_name();
        ostream& operator<<(ostream& os);
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon, Register* src);
};

class RamMemLoc : public MemSlot 
{
    private:
        Register* addr_reg;
        Register* t0;
        int offset;
    public:
        RamMemLoc(Register* addr_reg, Register* t0, int offset);
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon, Register* src);
};




#endif /*MEMORY_H*/