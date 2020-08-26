//////////////////////////////////////////////
// cgen.h
//
// Contains some classes and helpers for the 
// code generation routine
/////////////////////////////////////////////

#ifndef _CGEN_H
#define _CGEN_H

#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"
#include <vector>
#include <sstream>


using namespace std;

class Register;
class CodeContainer;

class GenArithOperation
{
   public:
      virtual void cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2) = 0;
};


class PlusCgen : public GenArithOperation
{
   public:
      void cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2);
};

class SubCgen : public GenArithOperation
{
   public:
      void cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2);
};

class MulCgen : public GenArithOperation
{
   public:
      void cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2);
};

class DivCgen : public GenArithOperation
{
   public:
      void cgen(CodeContainer& ccon, Register* dest, Register* op1, Register* op2);
};

#endif /*CGEN_H*/