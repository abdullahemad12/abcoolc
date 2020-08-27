/////////////////////////////////////////////////////////////////
// This class is used to store and emit the generated assembly 
// code. When cgen needs to generate a certain MIPS instruction, 
// it will call the corresponding emit function in this class. 
// This class is responsible to make sure that the emitted code 
// preserves the memory invariants and other conditions mentioned
// in the README of the cgen component
/////////////////////////////////////////////////////////////////

#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H


#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include "memory.h"


using namespace std;


class CodeContainer 
{
    private:
        stringstream buffer;
        vector<string> code;
        ostream& os;
        CodeContainer(const CodeContainer&) = delete;

    public:
        CodeContainer(ostream& os);
        void lw(Register* dest, Register* addr_reg, int offset);
        void la(Register* dest, string label);
        void li(Register* dest, int imm);
        void sw(Register* src, Register* addr_reg, int offset);
        void move(Register* dest, Register* src);
        void addi(Register* dest, Register* src, int imm);
        void addiu(Register* dest, Register* src, int imm);
        void add(Register* dest, Register* op1, Register* op2);
        void sub(Register* dest, Register* op1, Register* op2);
        void mul(Register* dest, Register* op1, Register* op2);
        void div(Register* dest, Register* op1, Register* op2);
        void sli(Register* dest, Register* src, int val);
        void global(string label);
        void label(string lab);
        void label(string lab, int index);
        void ascii(string str);
        void byte(int i);
        void text();
        void align(int i);
        void word(int i);
        void word(string s);
        void jal(string label);
        void jalr(Register* addr);
        void bne(Register* src1, Register* src2, string label);
        void beq(Register* src1, Register* src2, string label);
        void jr(Register* reg);
        void jump(string label);
        void bltz(Register* src, string label);
        void blez(Register* src, string label);
        void data();
        void write_out();
};



#endif /*CODE_CONTAINER_H*/