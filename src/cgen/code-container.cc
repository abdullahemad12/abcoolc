#include <sstream>
#include <string>
#include <assert.h>
#include "code-container.h"
#include "emit.h"

using namespace std;

#define CGEN(stream)        \
        buffer << stream;     \
        code.push_back(buffer.str()); \
        buffer.str("")


CodeContainer::CodeContainer(ostream& os) : os(os)
{ 

}

void CodeContainer::write_out()
{
    os << "# start of generated code\n";
    for(auto code_line : code)
        os << code_line << endl;
    os << "\n# end of generated code\n";
}

void CodeContainer::lw(Register* dest, Register* addr_reg, int offset)
{
    CGEN(LW << dest << ", " << offset << "(" << addr_reg << ")");
}

void CodeContainer::li(Register* dest, int imm)
{
    CGEN(LI << dest << ", " << imm);
}

void CodeContainer::sw(Register* src, Register* addr_reg, int offset)
{
    CGEN(SW << src << ", " << offset << "(" << addr_reg << ")");
}

void CodeContainer::la(Register* dest, string label)
{
    CGEN(LA << dest << ", " << label); 
}

void CodeContainer::move(Register* dest, Register* src)
{
    CGEN(MOVE << dest << ", " << src);
}

void CodeContainer::sub(Register* dest, Register* op1, Register* op2)
{
    CGEN(SUB << dest << ", " << op1 << ", " << op2);
}

void CodeContainer::addiu(Register* dest, Register* src, int immediate)
{
    CGEN(ADDIU << dest << ", " << src <<  ", " << immediate);
}


void CodeContainer::global(string label)
{
    CGEN(GLOBAL << label);
}

void CodeContainer::label(string lab)
{
    CGEN(lab << ":");
}

void CodeContainer::label(string lab, int index)
{
    CGEN(lab << index << ":");
}

void CodeContainer::word(int i)
{
    CGEN(WORD << i);
}

void CodeContainer::word(string s)
{
    CGEN(WORD << s);
}

void CodeContainer::align(int i)
{
    CGEN(ALIGN << i);
}

void CodeContainer::byte(int i)
{
    CGEN(BYTE << i);
}

void  CodeContainer::text()
{
    CGEN(TEXT);
}

void CodeContainer::ascii(string s)
{
    if(s.length() > 0)
    {
        CGEN(ASCII << "\"" << s << "\"");
    }
}

void CodeContainer::jal(string label)
{
    CGEN(JAL << label);
}

void CodeContainer::data()
{
    CGEN(DATA);
}

void CodeContainer::jr(Register* reg)
{
    assert(reg->get_name() == RA);
    CGEN(RET << reg);
}
