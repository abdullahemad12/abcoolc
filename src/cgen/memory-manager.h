//////////////////////////////////////////////////////////////////////////
// MemoryManager
// 
// The memory manager is used to manage the registers 
// and memory locations inorder to impose the invariants 
// and constraints required by cgen. The memory manager does that 
// by making two promises:
//  1. when a code is being generated for an expression node n, 
//     any subsequent and previous node m in the same method
//     will be/was given a  different memory slot than the ones 
//     given to node n
//  2. After any dispatch made in the current method m being process, 
//     all the temporaries and memory given to m will not be altered 
//     by this dispatch
//////////////////////////////////////////////////////////////////////////


#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "activation-record.h"
#include "memory.h"
#include "stringtab.h"
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <code-container.h>

using namespace std;

class MemoryManager 
{
    class Scope 
    {
        private:
            friend MemoryManager;
            ActivationRecord& ar;
            stack<Register*> free_regs;
            stack<RamMemLoc*> free_mem_locs;
            unordered_map<Register*, RamMemLoc*> allocated_regs;
            unordered_set<RamMemLoc*> allocated_mem_locs;
            unordered_map<Symbol, MemSlot*> identifiers; 
            Scope(ActivationRecord& ar);
            ~Scope();
    };
    Scope* scope = NULL;

    /**
      * @brief creates a new scope. Call this when entring a new method
      * @effects: allocates a new scope
      * @modifies: this
      * @param ActivationRecord the activation record of the current method node
      */
    void enter_scope(ActivationRecord& ar);

    /**
      * @brief used when the code for the method was generated
      * @effects: frees the scope and sets to NULL
      * @modifies: this
      */
    void exit_scope();

    /**
      * @brief allocates a new memory slot
      * @modifies: scope
      * @param CodeContainer
      * @returns a newly allocated memory slot
      */ 
    MemSlot* memalloc(CodeContainer& ccon);

    /**
      * @brief frees a memory that was allocated by this memory manager
      * @modifies: scope
      * @param CodeContainer
      * @param MemSlot*
      */ 
    void memfree(CodeContainer& ccon, MemSlot* memslot);

    /**
      * @brief binds an identifier to a memory location. (Case and let)
      * @modifies: scope
      * @param CodeContainer
      * @param Symbol the name of the identifier
      * @returns a new memory slot
      */ 
    MemSlot* add_identifier(CodeContainer& ccon, Symbol name);

    /**
      * @brief looks up an identifier
      * @requires: the identifier to be already added. Hangs
      *            if the identifier is not found
      * @param Symbol the name of the identifier
      * @returns the memory slot associated with the identifier
      */ 
    MemSlot* lookup_identifier(Symbol name);

    /**
      * @brief removes an identifier
      * @requires: the identifier to be already added. Hangs
      *            if the identifier is not found
      * @param CodeContainer 
      * @param Symbol the name of the identifier
      */
    void remove_identifier(CodeContainer& ccon, Symbol name);
};

#endif /*MEMORY_MANAGER_H*/