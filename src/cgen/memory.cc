#include "code-container.h"
#include "memory.h"
#include <assert.h>

void MemSlot::set_valid(bool val) 
{
    this->valid = val;
}

Register::Register(string name) : name(name) { }

string Register::get_name()
{
    return name;
}

Register* Register::load(CodeContainer& ccon)
{
    return this;
}
ostream& Register::operator<<(ostream& os)
{
    return (os << name);
}

void Register::save(CodeContainer& ccon, Register* src)
{
    if(!(this == src)) 
    {
        ccon.move(this, src);
    }
}

RamMemLoc::RamMemLoc(Register* addr_reg, Register* t0, int offset) : 
                        addr_reg(addr_reg), t0(t0), offset(offset)
{
    assert(addr_reg->get_name() != "$sp");
}

Register* RamMemLoc::load(CodeContainer& ccon)
{
    // $sp is not garuanteed to be fixed at any point
    ccon.lw(t0, addr_reg, offset);
    return t0;
}

void RamMemLoc::save(CodeContainer& ccon, Register* src)
{
    ccon.sw(src, addr_reg, offset);
}
