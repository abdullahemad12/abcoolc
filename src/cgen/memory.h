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
        string operator<<(string& s);
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

ostream& operator<<(ostream& os,  Register* reg);


#endif /*MEMORY_H*/