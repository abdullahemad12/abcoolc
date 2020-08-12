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
#define T0   "$t0"      // Temporary 0
#define T1   "$t1"		// Temporary 1 
#define T2   "$t2"		// Temporary 2 
#define T3   "$t3"		// Temporary 3 
#define T4   "$t4"      // Temporary 4
#define T5   "$t5"      // Temporary 5
#define T6   "$t6"      // Temporary 6
#define T7   "$t7"      // Temporary 7
#define T8   "$t8"      // Temporary 8
#define T9   "$t9"      // Temporary 9
#define SP   "$sp"		// Stack pointer 
#define FP   "$fp"		// Frame pointer 
#define RA   "$ra"		// Return address 



class Register;
class RamMemLoc;
class CodeContainer;
class MemoryManager;


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
    virtual void save(CodeContainer& ccon, Register* src) = 0;
};

class Register final : public MemSlot 
{
    private:
        friend MemoryManager;
        string name;
        Register(string name);
    public:
        string get_name();
        ostream& operator<<(ostream& os);
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon, Register* src);
};

class RamMemLoc final : public MemSlot 
{
    private:
        friend MemoryManager;
        Register* addr_reg;
        Register* t0;
        int offset;
        RamMemLoc(Register* addr_reg, Register* t0, int offset);
    public:
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon, Register* src);
};




#endif /*MEMORY_H*/