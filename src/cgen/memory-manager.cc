#include <algorithm> 
#include <assert.h>
#include "memory-manager.h"
#include "activation-record.h"

using namespace std;

///////////////////////////////////
//
// Code for Scope class
//
///////////////////////////////////
MemoryManager::Scope::Scope(ActivationRecord& ar, Register* t0, Register* ra, 
                            Register* fp, vector<Register*> regs) : ar(ar)
{
    
    initialize_tmps(t0, fp, regs);
    initialize_ar_mem(t0, ra, fp, regs);
}

MemoryManager::Scope::~Scope()
{
    for(auto mem_loc : all_ram_mem)
        delete mem_loc;

    delete ar_ra;
    delete ar_old_fp;
}

void MemoryManager::Scope::initialize_tmps(Register* t0, Register* fp, vector<Register*> regs)
{
    int regs_size;
    int tmps;
    int n;
    int i;
    RamMemLoc* rml;

    regs_size = regs.size();
    tmps = ar.ntmps();
    n = min(tmps, regs_size);

    for(i = n - 1; i >= 0; i--)
    {
        free_regs.push(regs[i]);
        rml = new RamMemLoc(fp, t0, 4 * i);;
        regs_to_mem[regs[i]] = rml;
        all_ram_mem.insert(rml);
    }

    for(i = tmps - 1; i >= n; i--)
    {
        rml = new RamMemLoc(fp, t0, 4 * i);
        free_mem_locs.push(rml);
        all_ram_mem.insert(rml);
    }
}

void MemoryManager::Scope::initialize_ar_mem(Register* t0, Register* ra, Register* fp, vector<Register*> regs)
{
    int nargs;
    int ntmps;
    int i;
    auto argv = ar.args();

    nargs = ar.argc();
    ntmps = ar.ntmps();

    for(int i = 0; i < nargs; i++)
    {
        RamMemLoc* rml = new RamMemLoc(fp, t0, (4 * ntmps + 4) + (4 * i));
        identifiers[argv[i]->get_name()] = rml;
        all_ram_mem.insert(rml);
    }

    ar_ra = new RamMemLoc(fp, ra, 4 * ntmps);
    ar_old_fp = new RamMemLoc(fp, fp, (4 * ntmps) + (4 * nargs) + 4);

}

//////////////////////////////////////////////////
//
// Code for MemoryManager
//
/////////////////////////////////////////////////


MemoryManager::MemoryManager() 
{
    fp = new Register(FP);
    sp = new Register(SP);
    t0 = new Register(T0);
    ra = new Register(RA);
    t_regs = {
        new Register(T5),
        new Register(T6),
        new Register(T7),
        new Register(T8),
        new Register(T9)
    };
}

MemoryManager::~MemoryManager()
{
    delete fp;
    delete sp;
    for(auto reg : t_regs)
        delete reg;
}

void MemoryManager::enter_scope(CodeContainer& ccon, ActivationRecord& ar)
{
    assert(scope == NULL);

    int ntmps;
    
    scope = new Scope(ar, t0, ra, fp, t_regs);
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
    ccon.addiu(sp, fp, (4 * nargs) + (4 * ntmps) + 4);

    // restore $ra
    scope->ar_ra->load(ccon);

    // restore $fp
    scope->ar_old_fp->load(ccon);
}