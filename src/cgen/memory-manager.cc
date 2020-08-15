#include <algorithm> 
#include <assert.h>
#include "memory-manager.h"
#include "activation-record.h"
#include "object-prototype.h"
#include "static-memory.h"

using namespace std;

///////////////////////////////////
//
// Code for Scope class
//
///////////////////////////////////
MemoryManager::Scope::Scope(Class_ class_, ActivationRecord& ar, MemoryManager::MipsRegisters& mregs)
                            : ar(ar)
{
    
    initialize_tmps(mregs);
    initialize_ar_mem(mregs);
    initialize_self_attr(class_, mregs);
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

    for(i = n - 1; i >= 0; i--)
    {
        free_regs.push(regs[i]);
        rml = new RamMemLoc(mregs.fp(), mregs.t0(), 4 * i);;
        regs_to_mem[regs[i]] = rml;
        all_ram_mem.insert(rml);
    }

    for(i = tmps - 1; i >= n; i--)
    {
        rml = new RamMemLoc(mregs.fp(), mregs.t0(), 4 * i);
        free_mem_locs.push(rml);
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

    offset = (4 * ntmps + 4);
    for(int i = 0; i < nargs; i++)
    {
        rml = new RamMemLoc(mregs.fp(), mregs.t0(),  offset + (4 * i));
        bind_mem_slot(argv[i]->get_name(), rml);
        all_ram_mem.insert(rml);
    }

    ar_ra = new RamMemLoc(mregs.fp(), mregs.ra(), 4 * ntmps);
    ar_old_fp = new RamMemLoc(mregs.fp(), mregs.fp(), (4 * ntmps) + (4 * nargs) + 4);

}

void MemoryManager::Scope::initialize_self_attr(Class_ class_, MemoryManager::MipsRegisters& mregs)
{
    
}

//////////////////////////////////////////////////
//
// Code for MemoryManager
//
/////////////////////////////////////////////////


MemoryManager::MemoryManager(StaticMemory& static_memory) : static_memory(static_memory)
{

}

void MemoryManager::enter_scope(CodeContainer& ccon, Class_ class_, ActivationRecord& ar)
{
    assert(scope == NULL);
    Register *sp, *fp, *ra;
    int ntmps;
    sp = mregs.sp();
    fp = mregs.fp();
    ra = mregs.ra();

    scope = new Scope(class_, ar, mregs);
    ccon.sw(ra, sp, 0);

    ntmps = ar.ntmps();
    // sp is set to the first free loc after temps
    ccon.addiu(sp, sp, -(4 * ntmps + 4));
    // fp is set to the last tmp
    ccon.addiu(fp, sp, 4);

    // save all the required tmp registers to preserve them
    for(auto entry : scope->regs_to_mem)
        entry.second->save(ccon, entry.first);
    
}

void MemoryManager::exit_scope(CodeContainer& ccon)
{
    int ntmps;
    int nargs;

    // restore all tmps
    for(auto entry : scope->regs_to_mem)
    {
        Register* old_value = entry.second->load(ccon);
        entry.first->save(ccon, old_value);
    }

    ntmps = scope->ar.ntmps();
    nargs = scope->ar.argc();

    //restore $sp
    ccon.addiu(mregs.sp(), mregs.fp(), (4 * nargs) + (4 * ntmps) + 4);

    // restore $ra
    scope->ar_ra->load(ccon);

    // restore $fp
    scope->ar_old_fp->load(ccon);
}