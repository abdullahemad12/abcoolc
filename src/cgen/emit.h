///////////////////////////////////////////////////////////////////////
//
//  Assembly Code Naming Conventions:
//
//     Dispatch table            <classname>_dispTab
//     Method entry point        <classname>.<method>
//     Class init code           <classname>_init
//     Abort method entry        <classname>.<method>.Abort
//     Prototype object          <classname>_protObj
//     Integer constant          int_const<Symbol>
//     String constant           str_const<Symbol>
//
///////////////////////////////////////////////////////////////////////
#include <string>
#include "stringtab.h"

using namespace std;

#define MAXINT  100000000    
#define WORD_SIZE    4
#define LOG_WORD_SIZE 2     // for logical shifts



/////////////////
// Statics
/////////////////
#define GLOBAL        "\t.globl\t"
#define ALIGN         "\t.align\t"
#define WORD          "\t.word\t"
#define ASCII         "\t.ascii\t"
#define BYTE          "\t.byte\t"
#define DATA          "\t.data\t"
#define TEXT          "\t.text"

// cool system procedures
#define EQUALITY_TEST   "equality_test"
#define DISPATCH_ABORT  "_dispatch_abort"
#define CASE_ABORT      "_case_abort"
#define CASE_ABORT_VOID "_case_abort2"

// Global names
#define CLASSNAMETAB         "class_nameTab"
#define CLASSOBJTAB          "class_objTab"
#define INTTAG               "_int_tag"
#define BOOLTAG              "_bool_tag"
#define STRINGTAG            "_string_tag"
#define HEAP_START           "heap_start"
#define ANCESTORS_TAB_PTR    "ancestors_TabPtr"

// Naming conventions
#define DISPTAB_SUFFIX       "_dispTab"
#define METHOD_SEP           "."
#define CLASSINIT_SUFFIX     "_init"
#define PROTOBJ_SUFFIX       "_protObj"
#define OBJECTPROTOBJ        "Object" PROTOBJ_SUFFIX
#define INTCONST_PREFIX      "int_const"
#define STRCONST_PREFIX      "str_const"
#define BOOLCONST_PREFIX     "bool_const"
#define ANCESTORS_SUFFIX     "_ancestors"
#define DISPATCH_LABEL_SUFFIX "_dispTab"

// Labels Generators
#define OBJECT_PROTOTYPE_LABEL(class_name)    (class_name + PROTOBJ_SUFFIX)
#define ANCESTORS_TABLE_LABEL(class_name)     (class_name + ANCESTORS_SUFFIX)
#define INT_CONST_LABEL(i) (INTCONST_PREFIX + std::to_string(i))
#define STR_CONST_LABEL(i) (STRCONST_PREFIX + std::to_string(i))

// Default values
#define EMPTY_STRING        "_empty_string"
#define NULL_VALUE          "0"
#define FALSE               BOOLCONST_PREFIX "0"
#define TRUE                BOOLCONST_PREFIX "1"
#define ZERO_INT            "zero_int"


#define EMPTYSLOT            0
#define LABEL                ":\n"

#define STRINGNAME          "String"
#define INTNAME             "Int"
#define BOOLNAME            "Bool"
#define MAINNAME            "Main"
#define MAINMETHOD          "main"
//
// information about object headers
//
#define DEFAULT_OBJFIELDS 3
#define TAG_OFFSET 0
#define SIZE_OFFSET 1
#define DISPTABLE_OFFSET 2

#define STRING_SLOTS      1
#define INT_SLOTS         1
#define BOOL_SLOTS        1

#define GLOBAL        "\t.globl\t"
#define WORD          "\t.word\t"

//
// register names
//
#define ZERO "$0"		// Zero register 
#define ACC  "$a0"		// Accumulator 
#define A1   "$a1"		// For arguments to prim funcs 
#define A2   "$a2"      // $a2 Register
#define A3   "$a3"      // $a3 Register
#define SELF "$s0"		// Ptr to self (callee saves) 
#define T0   "$t0"      // Temporary 0
#define T1   "$t1"		// Temporary 1 
#define T2   "$t2"		// Temporary 2 
#define T3   "$t3"		// Temporary 3 
#define T4   "$t4"      // Temporary 4
#define T5   "$t5"      // Temporary 5
#define T6   "$t6"      // Temporary 6
#define T7   "$t7"      // Temporary 7
#define T8   "$t8"      // Temporary 8
#define T9   "$t9"      // Temporary 9
#define S0   "$s0"      // Saved 0
#define S1   "$s1"      // Saved 1
#define S2   "$s2"      // Saved 2
#define S3   "$s3"      // Saved 3
#define S4   "$s4"      // Saved 4
#define S5   "$s5"      // Saved 5
#define S6   "$s6"      // Saved 6
#define S7   "$s7"      // Saved 7
#define SP   "$sp"		// Stack pointer 
#define FP   "$fp"		// Frame pointer 
#define RA   "$ra"		// Return address 


//
// Opcodes
//
#define JALR  "\tjalr\t"  
#define JAL   "\tjal\t"                 
#define RET   "\tjr\t"
#define JUMP  "\tj\t"

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
#define BLTZ     "\tbltz\t"
#define BLEQ     "\tble\t"
#define BLT      "\tblt\t"
#define BGT      "\tbgt\t"


