#include <algorithm> 
#include <assert.h>
#include "memory-manager.h"
#include "activation-record.h"
#include "object-prototype.h"
#include "static-memory.h"

using namespace std;


///////////////////////////////////
//
// Code for MipsRegisters
//
///////////////////////////////////
MemoryManager::MipsRegisters::MipsRegisters()
{
    // All registers that are not used
    // by the run time system
    vector<string> pregs = {T5, T6, T7, T8, T9, S1, S2, S3, S4, S5, S6};
    for(string reg : pregs) 
        pregv.push_back(new Register(reg));
    sp_reg = new Register(SP);
    fp_reg = new Register(FP);
    t0_reg = new Register(T0);
    ra_reg = new Register(RA);
    a0_reg = new Register(ACC);  
}
MemoryManager::MipsRegisters::~MipsRegisters()
{
    for(Register* reg : pregv)
        delete reg;

    delete sp_reg;
    delete fp_reg;
    delete t0_reg;
    delete ra_reg;
    delete a0_reg;
}

vector<Register*> MemoryManager::MipsRegisters::pregs() { return pregv; }
Register* MemoryManager::MipsRegisters::sp() { return sp_reg; }
Register* MemoryManager::MipsRegisters::fp()  { return fp_reg; }
Register* MemoryManager::MipsRegisters::t0() { return t0_reg; }
Register* MemoryManager::MipsRegisters::ra() { return ra_reg; }
Register* MemoryManager::MipsRegisters::acc() { return a0_reg; }

///////////////////////////////////
//
// Code for Scope class
//
///////////////////////////////////
MemoryManager::Scope::Scope(ObjectPrototype& obj_prot, ActivationRecord& ar, MemoryManager::MipsRegisters& mregs)
                            : ar(ar)
{
    initialize_self_attr(obj_prot, mregs);
    initialize_tmps(mregs);
    initialize_ar_mem(mregs);
}

MemoryManager::Scope::~Scope()
{
    for(auto mem_loc : all_ram_mem)
        delete mem_loc;

    delete ar_ra;
    delete ar_old_fp;
}

void MemoryManager::Scope::initialize_tmps(MemoryManager::MipsRegisters& mregs)
{
    int regs_size;
    int tmps;
    int n;
    int i;
    RamMemLoc* rml;
    vector<Register*> regs = mregs.pregs();
    regs_size = regs.size();
    tmps = ar.ntmps();
    n = min(tmps, regs_size);

    for(i = tmps - 1; i >= n; i--)
    {
        rml = new RamMemLoc(mregs.fp(), mregs.t0(), 4 * i);
        free_mem.push(rml);
        all_ram_mem.insert(rml);
    }

    for(i = n - 1; i >= 0; i--)
    {
        free_mem.push(regs[i]);
        rml = new RamMemLoc(mregs.fp(), regs[i], 4 * i);;
        regs_to_mem[regs[i]] = rml;
        all_ram_mem.insert(rml);
    }


}

void MemoryManager::Scope::initialize_ar_mem(MemoryManager::MipsRegisters& mregs)
{
    int nargs, ntmps, offset, i;
    auto argv = ar.args();
    RamMemLoc* rml;

    vector<Register*> regs = mregs.pregs();

    nargs = ar.argc();
    ntmps = ar.ntmps();

    offset = (4 * ntmps + 8);
    for(int i = 0; i < nargs; i++)
    {
        rml = new RamMemLoc(mregs.fp(), mregs.t0(),  offset + (nargs - 1 ) - (4 * i));
        bind_mem_slot(argv[i]->get_name(), rml);
        all_ram_mem.insert(rml);
    }
    ar_ra = new RamMemLoc(mregs.fp(), mregs.ra(), 4 * ntmps);
    ar_old_fp = new RamMemLoc(mregs.fp(), mregs.fp(), (4 * ntmps) + (4 * nargs) + 8);

}

void MemoryManager::Scope::initialize_self_attr(ObjectPrototype& obj_prot, MemoryManager::MipsRegisters& mregs)
{
    vector<attr_class*> attrs = obj_prot.attributes();
    ar_self = new RamMemLoc(mregs.fp(), mregs.acc(), 4 * ar.ntmps() + 4);

    int i = 0;
    for(auto attr : attrs)
    {
        MemSlot* location = new SelfAttribute(ar_self, (i * 4) + 12);
        bind_mem_slot(attr->get_name(), location);
        ++i;
    }
}

void MemoryManager::Scope::bind_mem_slot(Symbol identifier, MemSlot* slot)
{
    if(identifiers.find(identifier) == identifiers.end())
    {
        std::stack<MemSlot*> s;
        identifiers[identifier] = s;
    }
    identifiers[identifier].push(slot);
}

//////////////////////////////////////////////////
//
// Code for MemoryManager
//
/////////////////////////////////////////////////


MemoryManager::MemoryManager(StaticMemory& static_memory) : static_memory_attr(static_memory)
{

}

void MemoryManager::enter_scope(CodeContainer& ccon, Class_ class_, ActivationRecord& ar)
{
    assert(scope == NULL);
    Register *sp, *fp, *ra, *acc;
    int ntmps;
    ObjectPrototype& obj_prot = static_memory_attr.lookup_objectprot(class_->get_name());

    sp = mregs.sp();
    fp = mregs.fp();
    ra = mregs.ra();
    acc = mregs.acc();
    scope = new Scope(obj_prot, ar, mregs);

    ccon.sw(acc, sp, 0);
    ccon.sw(ra, sp, -4);

    ntmps = ar.ntmps();
    // sp is set to the first free loc after temps
    ccon.addiu(sp, sp, -(4 * ntmps + 8));
    // fp is set to the last location (self)
    ccon.addiu(fp, sp, 4);

    // save all the required tmp registers to preserve them
    for(auto entry : scope->regs_to_mem)
        entry.second->save(ccon, entry.first);
    

}

void MemoryManager::exit_scope(CodeContainer& ccon)
{
    assert(scope);
    assert(scope->free_mem.size() == scope->ar.ntmps());
    int ntmps;
    int nargs;

    // restore all tmps
    for(auto entry : scope->regs_to_mem)
        Register* old_value = entry.second->load(ccon);


    ntmps = scope->ar.ntmps();
    nargs = scope->ar.argc();

    //restore $sp
    ccon.addiu(mregs.sp(), mregs.fp(), (4 * nargs) + (4 * ntmps) + 8);

    // restore $ra
    Register* ra = scope->ar_ra->load(ccon);

    // restore $fp
    scope->ar_old_fp->load(ccon);

    ccon.jr(ra);
    delete scope;
    scope = NULL;
}

MemSlot* MemoryManager::memalloc()
{
    assert(scope);
    assert(!scope->free_mem.empty());

    MemSlot* alloc_mem = scope->free_mem.top();
    assert(!alloc_mem->alloc);

    alloc_mem->alloc = true;
    scope->free_mem.pop();
    return alloc_mem;
}

void MemoryManager::memfree(MemSlot* memslot)
{
    assert(scope);
    assert(memslot->alloc);
    memslot->alloc = false;
    scope->free_mem.push(memslot);
}

MemSlot* MemoryManager::add_identifier(Symbol name)
{
    assert(scope);
    MemSlot* slot = memalloc();
    scope->bind_mem_slot(name, slot);
    return slot;
}

MemSlot* MemoryManager::lookup_identifier(Symbol name)
{
    assert(scope);
    assert(scope->identifiers.find(name)
            != scope->identifiers.end());
    assert(!scope->identifiers[name].empty());
    return scope->identifiers[name].top();
}

void MemoryManager::remove_identifier(Symbol name)
{
    assert(scope);
    memfree(lookup_identifier(name));
    scope->identifiers[name].pop();
}


void MemoryManager::push_ac(CodeContainer& ccon)
{
    ccon.sw(mregs.acc(), mregs.sp(), 0);
    ccon.addiu(mregs.sp(), mregs.sp(), -4);
}

Register* MemoryManager::acc() { return mregs.acc(); }

StaticMemory& MemoryManager::static_memory() { return static_memory_attr; }