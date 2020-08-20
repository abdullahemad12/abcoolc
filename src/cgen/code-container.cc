#include "code-container.h"
#include <sstream>
#include <string>

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

void CodeContainer::sw(Register* src, Register* addr_reg, int offset)
{
    CGEN(SW << src << ", " << offset << "(" << addr_reg << ")");
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

void CodeContainer::global_string_const(string label, string str)
{
    CGEN(GLOBAL << label << endl);
    CGEN(label << ":" << endl);
    CGEN(WORD << str << endl);
}

void CodeContainer::global_int_const(string label, int i)
{
    CGEN(GLOBAL << label << endl);
    CGEN(label << ":" << endl);
    CGEN(WORD << i << endl);
}