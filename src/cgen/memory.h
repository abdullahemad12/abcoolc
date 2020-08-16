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
#define A2   "$a2"      // $a2 Register
#define A3   "$a3"      // $a3 Register
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
#define S0   "$s0"      // Saved 0
#define S1   "$s1"      // Saved 1
#define S2   "$s2"      // Saved 2
#define S3   "$s3"      // Saved 3
#define S4   "$s4"      // Saved 4
#define S5   "$s5"      // Saved 5
#define S6   "$s6"      // Saved 6
#define S7   "$s7"      // Saved 7
#define SP   "$sp"		// Stack pointer 
#define FP   "$fp"		// Frame pointer 
#define RA   "$ra"		// Return address 



class Register;
class RamMemLoc;
class CodeContainer;
class MemoryManager;


class MemSlot 
{
    friend MemoryManager;
    protected:
        /*used to catch errors*/
        bool alloc = false; 

    public:
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


class SelfAttribute final : public MemSlot
{
    private:
        friend MemoryManager;
        RamMemLoc* self;
        int offset;
        SelfAttribute(RamMemLoc* self, int offset);
    public:
        Register* load(CodeContainer& ccon);
        void save(CodeContainer& ccon, Register* src);
};




#endif /*MEMORY_H*/