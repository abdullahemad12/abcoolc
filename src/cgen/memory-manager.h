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
// Note: the memory manager does not use tmp registers $t1-$t4; thus
//       they can be used without consulting the manager, but not 
//       any guarantee on their persistance will not be made
//////////////////////////////////////////////////////////////////////////


#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <unordered_map>
#include <stack>
#include <unordered_set>
#include "code-container.h"
#include "activation-record.h"
#include "memory.h"
#include "stringtab.h"
#include "static-memory.h"

using namespace std;

#define GEN_LABEL(ctr) "gen_label" + to_string(ctr)
class MemoryManager 
{
  // use this to store the registers and pass it to the scope
    class MipsRegisters
    {
      friend MemoryManager;
      private:
        MipsRegisters();
        ~MipsRegisters();
        vector<Register*> pregv;
        Register* sp_reg;
        Register* fp_reg;
        Register* t0_reg;
        Register* t1_reg;
        Register* t2_reg;
        Register* ra_reg;
        Register* a0_reg;
        Register* a1_reg;
        Register* zero_reg;
      public:
        /**
          * Gets a list of persistant registers that are not used by 
          * the MIPS run-time system
          * i.e: non-scratch registers
          */  
        vector<Register*> pregs();
        Register* zero();
        Register* sp();
        Register* fp();
        Register* t0();
        Register* t1();
        Register* t2();
        Register* ra();
        Register* acc();
        Register* a1();
    };
    class Scope 
    {
        private:
            friend MemoryManager;
            ActivationRecord& ar;
            stack<MemSlot*> free_mem;
            unordered_map<Register*, RamMemLoc*> regs_to_mem;
            unordered_map<string, stack<MemSlot*>> identifiers; 
            unordered_set<RamMemLoc*> all_ram_mem;
            RamMemLoc* ar_ra;
            RamMemLoc* ar_old_fp;
            RamMemLoc* ar_self;

            Scope(ObjectPrototype& obj_prot, ActivationRecord& ar, MipsRegisters& mregs);
            // ar must be set correctly first before calling them
            void initialize_tmps(MipsRegisters& mregs);
            void initialize_ar_mem(MipsRegisters& mregs);
            void initialize_self_attr(ObjectPrototype& obj_prot, MipsRegisters& mregs);
            // binds a memory slot to an identifier
            void bind_mem_slot(Symbol identifier, MemSlot* slot);
            ~Scope();
    };

    private: 
      StaticMemory& static_memory_attr;
      Scope* scope = NULL;
      MipsRegisters mregs;
      int labels_ctr = 0;
      void push_register(CodeContainer& ccon, Register* reg);
    public:
      MemoryManager(const MemoryManager&) = delete;
      MemoryManager(StaticMemory& static_memory);
      /**
        * @brief creates a new scope. Call this when entring a new method
        * @effects: allocates a new scope
        * @modifies: this
        * @param CodeContainer used to generate the code on method enter
        * @param ActivationRecord the activation record of the current method node
        */
      void enter_scope(CodeContainer& ccon, Class_ class_, ActivationRecord& ar);

      /**
        * @brief used when the code for the method was generated
        * @effects: frees the scope and sets to NULL
        * @modifies: this
        * @param CodeContainer used to generate the code on method enter
        */
      void exit_scope(CodeContainer& ccon);

      /**
        * @brief allocates a new memory slot
        * @modifies: scope
        * @param CodeContainer
        * @returns a newly allocated memory slot
        */ 
      MemSlot* memalloc();

      /**
        * @brief frees a memory that was allocated by this memory manager
        * @modifies: scope
        * @param CodeContainer
        * @param MemSlot*
        */ 
      void memfree(MemSlot* memslot);

      /**
        * @brief binds an identifier to a new memory location. (Case and let)
        * @modifies: scope
        * @param Symbol the name of the identifier
        * @returns a new memory slot
        */ 
      MemSlot* add_identifier(Symbol name);

    /**
      * @brief binds the identifier name to the given memory location
      * @modifies: scope
      * @param Symbol the name of the identifier
      * @param MemSlot* the location to be bound to this id
      * @returns the given MemSlot* on success. On failure hangs
      */ 
      MemSlot* add_identifier(Symbol name, MemSlot* location);

      /**
        * @brief looks up an identifier
        * @requires: the identifier to be already added. Hangs
        *            if the identifier is not found
        * @param Symbol the name of the identifier
        * @returns the memory slot associated with the identifier
        */ 
      MemSlot* lookup_identifier(Symbol name);

      /**
        * @brief removes an identifier and frees the memory associated with it
        * @requires: the identifier to be already added. Hangs
        *            if the identifier is not found
        * @param Symbol the name of the identifier
        */
      void remove_and_free_identifier(Symbol name);

    /**
        * @brief removes an identifier but does not free the memory associated with it
        * @requires: the identifier to be already added. Hangs
        *            if the identifier is not found
        * @param Symbol the name of the identifier
        */
      void remove_identifier(Symbol name);

      
      /**
        * @brief pushes the AC register onto the stack
        * @param CodeContainer& ccon
        */
       void push_acc(CodeContainer& ccon);

      /**
        * @brief pushes the frame pointer onto the stack
        * @param CodeContainer& ccon
        */ 
       void push_fp(CodeContainer& ccon);

      /**
        * @brief return the accumulator register $a0
        * @returns Register* $a0
        * @warning no guarantees are made on these registers
        */ 
       Register* acc();
       Register* a1();
       Register* tmp1();
       Register* tmp2();
       Register* zero();
       MemSlot* self();

      /**
        * @brief returns the static memory
        * @returns the static memory
        */ 
       StaticMemory& static_memory();

      /**
        * @brief generates a new label that has not been used before
        * @returns string the generated label
        */ 
       string gen_label();

};

#endif /*MEMORY_MANAGER_H*/