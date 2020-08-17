#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>
#include "cool-io.h"  //includes iostream
#include "cool-tree.h"
#include "cgen_gc.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "activation-record.h"
#include "object-prototype.h"
#include "static-memory.h"
#include "memory-manager.h"
#include "code-container.h"

using namespace std;

extern int optind;            // for option processing
extern char *out_filename;    // name of output assembly
extern Program ast_root;             // root of the abstract syntax tree
FILE *ast_file = stdin;       // we read the AST from standard input
extern int ast_yyparse(void); // entry point to the AST parser

int cool_yydebug;     // not used, but needed to link with handle_flags
char *curr_filename;

TEST_CASE( "MemoryManager", "[enter_scope]" ) 
{
    vector<string> expected_ordered = {
        "\tsw\t$a0, 0($sp)",
        "\tsw\t$ra, -4($sp)",
        "\taddiu\t$sp, $sp, -36",
        "\taddiu\t$fp, $sp, 4",
        "\tsw\t$t5, 0($fp)",
        "\tsw\t$t7, 4($fp)",
        "\tsw\t$t8, 8($fp)",
        "\tsw\t$t9, 12($fp)",
        "\tsw\t$s1, 16($fp)",
        "\tsw\t$t6, 20($fp)",
        "\tsw\t$s2, 24($fp)"
    };
    
    Formal formal1 = formal(idtable.add_string("arg1"), idtable.add_string("Int"));
    Formal formal2 = formal(idtable.add_string("arg2"), idtable.add_string("String"));
    Formal formal3 = formal(idtable.add_string("arg3"), idtable.add_string("Int"));
    Formal formal4 = formal(idtable.add_string("arg4"), idtable.add_string("Bool"));

    Formals formals = single_Formals(formal1);
    formals = append_Formals(formals, single_Formals(formal2));
    formals = append_Formals(formals, single_Formals(formal3));
    formals = append_Formals(formals, single_Formals(formal4));

    ActivationRecord ar(formals, 7);
    Class_ classs = class_(idtable.add_string("A"), idtable.add_string("Object"), nil_Features(), idtable.add_string("file.cl"));
    ObjectPrototype obj;
    StaticMemory sm;
    sm.add_object_prot(idtable.add_string("A"), obj);

    MemoryManager mm(sm);

    stringstream s;
    stringstream expected;

    expected << "# start of generated code\n";
    for(string tmp : expected_ordered)
    {
        expected << tmp << endl;
    }
    expected << "\n# end of generated code\n";
    CodeContainer ccon(s);

    mm.enter_scope(ccon, classs, ar);
    ccon.write_out();
}