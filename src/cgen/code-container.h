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

/////////////////
// Statics
/////////////////
#define GLOBAL        "\t.globl\t"
#define ALIGN         "\t.align\t"
#define WORD          "\t.word\t"
#define ASCII         "\t.ascii\t"
#define BYTE          "\t.byte\t"
/////////////////
// Opcodes
/////////////////
#define JALR  "\tjalr\t"  
#define JAL   "\tjal\t"                 
#define RET   "\tjr\t" RA "\t"

#define SW    "\tsw\t"
#define LW    "\tlw\t"
#define LI    "\tli\t"
#define LA    "\tla\t"

#define MOVE  "\tmove\t"
#define NEG   "\tneg\t"
#define ADD   "\tadd\t"
#define ADDI  "\taddi\t"
#define ADDU  "\taddu\t"
#define ADDIU "\taddiu\t"
#define DIV   "\tdiv\t"
#define MUL   "\tmul\t"
#define SUB   "\tsub\t"
#define SLL   "\tsll\t"
#define BEQZ  "\tbeqz\t"
#define BRANCH   "\tb\t"
#define BEQ      "\tbeq\t"
#define BNE      "\tbne\t"
#define BLEQ     "\tble\t"
#define BLT      "\tblt\t"
#define BGT      "\tbgt\t"


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
        void sw(Register* src, Register* addr_reg, int offset);
        void move(Register* dest, Register* src);
        void addiu(Register* dst, Register* src, int imm);
        void sub(Register* dest, Register* op1, Register* op2);
        void global_word(string label, string str);
        void global_word(string label, int i);
        void label(string lab);
        void label(string lab, int index);
        void ascii(string str);
        void byte(int i);
        void align(int i);
        void word(int i);
        void word(string s);
        void write_out();
};



#endif /*CODE_CONTAINER_H*/