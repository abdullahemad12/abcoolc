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

vector<string> split(string str)
{
    vector<string> vec;
    string cur;
    for(unsigned int i = 0; i < str.length(); i++)
    {
        if(str[i] == '\n') 
        {
            if(cur != "")
                vec.push_back(cur);
            cur = "";
        }
        else
        {
            cur.push_back(str[i]);
        }
    }
    return vec;
}
TEST_CASE( "MemoryManager Test1", "[enter_scope]" ) 
{
    vector<string> expected_ordered = {
        "\tsw\t$a0, 0($sp)",
        "\tsw\t$fp, -4($sp)",
        "\tsw\t$ra, -8($sp)",
        "\taddiu\t$sp, $sp, -40",
        "\taddiu\t$fp, $sp, 4"
    };

    unordered_set<string> expected_unordered = {
        "\tsw\t$t5, 0($fp)",
        "\tsw\t$t6, 4($fp)",
        "\tsw\t$t7, 8($fp)",
        "\tsw\t$t8, 12($fp)",
        "\tsw\t$t9, 16($fp)",
        "\tsw\t$s1, 20($fp)",
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
    Class_ classs = class_(idtable.add_string("A"), NULL, nil_Features(), idtable.add_string("file.cl"));
    StaticMemory sm;
    sm.install_class(classs);

    MemoryManager mm(sm);

    stringstream s;
    CodeContainer ccon(s);
    mm.enter_scope(ccon, classs, ar);
    ccon.write_out();
    vector<string> lines = split(s.str());
    REQUIRE(lines.size() == 14);
    for(int i = 1; i < 6; i++)
    {
        REQUIRE(lines[i] == expected_ordered[i - 1]);
    }
    for(int i = 6; i < 13; i++)
    {
        REQUIRE(expected_unordered.find(lines[i]) != expected_unordered.end());
        expected_unordered.erase(lines[i]);
    }
}


TEST_CASE( "MemoryManager Test2", "[exit_scope]" )
{
    unordered_set<string> expected_unordered = {
        "\tlw\t$t5, 0($fp)",
        "\tlw\t$t6, 4($fp)",
        "\tlw\t$t7, 8($fp)",
        "\tlw\t$t8, 12($fp)",
        "\tlw\t$t9, 16($fp)",
        "\tlw\t$s1, 20($fp)",
        "\tlw\t$s2, 24($fp)"
    };
    vector<string> expected_ordered = {
        "\taddiu\t$sp, $fp, 52",
        "\tlw\t$ra, 28($fp)",
        "\tlw\t$fp, 32($fp)"
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
    Class_ classs = class_(idtable.add_string("A"), NULL, nil_Features(), idtable.add_string("file.cl"));
    ObjectPrototype obj;
    StaticMemory sm;
    sm.install_class(classs);

    MemoryManager mm(sm);


    stringstream s;
    CodeContainer ccon(s);
    mm.enter_scope(ccon, classs, ar);
    mm.exit_scope(ccon);
    ccon.write_out();
    vector<string> lines = split(s.str());
    for(int i = 13; i < 20; i++)
    {
        REQUIRE(expected_unordered.find(lines[i]) != expected_unordered.end());
        expected_unordered.erase(lines[i]);
    }
    for(int i = 20; i < 23; i++)
    {
        REQUIRE(lines[i] == expected_ordered[i - 20]);
    }
    
    
}

TEST_CASE("Memory Manager Test 3", "[memalloc and free]")
{
    int tmps = 20;
    Formal formal1 = formal(idtable.add_string("arg1"), idtable.add_string("Int"));
    Formal formal2 = formal(idtable.add_string("arg2"), idtable.add_string("String"));
    Formal formal3 = formal(idtable.add_string("arg3"), idtable.add_string("Int"));
    Formal formal4 = formal(idtable.add_string("arg4"), idtable.add_string("Bool"));

    Formals formals = single_Formals(formal1);
    formals = append_Formals(formals, single_Formals(formal2));
    formals = append_Formals(formals, single_Formals(formal3));
    formals = append_Formals(formals, single_Formals(formal4));

    ActivationRecord ar(formals, tmps);
    Class_ classs = class_(idtable.add_string("A"), NULL, nil_Features(), idtable.add_string("file.cl"));
    StaticMemory sm;
    sm.install_class(classs);

    MemoryManager mm(sm);
    stringstream sss;
    CodeContainer ccon(sss);
    mm.enter_scope(ccon, classs, ar);
    unordered_set<string> reserved = {T5, T6, T7, T8, T9, S1, S2, S3, S4, S5, S6};
    for(int j = 0; j < 3; j++)
    {
        unordered_set<string> seen;
        vector<MemSlot*> slots;
        for(int i = 0; i < 11; i++)
        {
            stringstream stream;

            CodeContainer c(stream);
            MemSlot* mem = mm.memalloc();
            Register* reg = mem->load(c);
            c.write_out();
            REQUIRE(reserved.find(reg->get_name()) != reserved.end());
            REQUIRE(split(stream.str()).size() == 2);
            REQUIRE(seen.find(reg->get_name()) == seen.end());
            seen.insert(reg->get_name());
            slots.push_back(mem);
        }
        for(int i = 0; i < 9; i++)
        {
            stringstream stream;

            CodeContainer c(stream);
            MemSlot* mem = mm.memalloc();
            Register* reg = mem->load(c);
            c.write_out();
            REQUIRE(reg->get_name() == T0);
            REQUIRE(split(stream.str()).size() == 3);

            stringstream expected_stream;
            expected_stream << "\tlw\t$t0, " << ((i + 11) * 4) << "($fp)";
            REQUIRE(split(stream.str())[1] == expected_stream.str());
            slots.push_back(mem);
        }
        for(int i = slots.size() - 1; i >= 0; i--)
        {
            mm.memfree(slots[i]);
        }
    }
    

    mm.exit_scope(ccon);
}

TEST_CASE( "MemoryManager", "[identifiers]" )
{
    int tmps = 20;
    Feature feature1 = attr(idtable.add_string("x"), idtable.add_string("Int"), no_expr());
    Feature feature2 = attr(idtable.add_string("y"), idtable.add_string("Bool"), no_expr());
    Feature feature3 = attr(idtable.add_string("z"), idtable.add_string("String"), no_expr());
    Features features = single_Features(feature1);
    features = append_Features(features, single_Features(feature2));
    features = append_Features(features, single_Features(feature3));

    Formal formal1 = formal(idtable.add_string("arg1"), idtable.add_string("Int"));
    Formal formal2 = formal(idtable.add_string("arg2"), idtable.add_string("String"));
    Formal formal3 = formal(idtable.add_string("arg3"), idtable.add_string("Int"));
    Formal formal4 = formal(idtable.add_string("arg4"), idtable.add_string("Bool"));

    Formals formals = single_Formals(formal1);
    formals = append_Formals(formals, single_Formals(formal2));
    formals = append_Formals(formals, single_Formals(formal3));
    formals = append_Formals(formals, single_Formals(formal4));

    ActivationRecord ar(formals, tmps);
    Class_ classs = class_(idtable.add_string("A"), NULL, features, idtable.add_string("file.cl"));
    StaticMemory sm;
    sm.install_class(classs);

    stringstream s;
    CodeContainer ccon(s);
    MemoryManager mm(sm);
    mm.enter_scope(ccon, classs, ar);
    stringstream s1; 
    CodeContainer ccon1(s1);

    MemSlot* mem = mm.lookup_identifier(idtable.add_string("x"));
    Register* reg = mem->load(ccon1);
    REQUIRE(reg->get_name() == T0);
    ccon1.write_out();
    vector<string> lines = split(s1.str());
    REQUIRE(lines.size() == 4);

    REQUIRE(lines[1] == "\tlw\t$t0, 88($fp)");
    REQUIRE(lines[2] == "\tlw\t$t0, 12($t0)");

    stringstream s2; 
    CodeContainer ccon2(s2);
    mem = mm.lookup_identifier(idtable.add_string("y"));
    reg = mem->load(ccon2);
    REQUIRE(reg->get_name() == T0);
    ccon2.write_out();
    lines = split(s2.str());
    REQUIRE(lines.size() == 4);

    REQUIRE(lines[1] == "\tlw\t$t0, 88($fp)");
    REQUIRE(lines[2] == "\tlw\t$t0, 16($t0)");

    stringstream s3; 
    CodeContainer ccon3(s3);
    mem = mm.lookup_identifier(idtable.add_string("z"));
    reg = mem->load(ccon3);
    REQUIRE(reg->get_name() == T0);
    ccon3.write_out();
    lines = split(s3.str());
    REQUIRE(lines.size() == 4);

    REQUIRE(lines[1] == "\tlw\t$t0, 88($fp)");
    REQUIRE(lines[2] == "\tlw\t$t0, 20($t0)");


    mm.add_identifier(idtable.add_string("x"));
    stringstream s4;
    CodeContainer ccon4(s4);
    mem = mm.lookup_identifier(idtable.add_string("x"));
    reg = mem->load(ccon4);
    ccon4.write_out();
    REQUIRE(reg->get_name() == T5);
    REQUIRE(split(s4.str()).size() == 2);

    mm.remove_identifier(idtable.add_string("x"));

    stringstream s5; 
    CodeContainer ccon5(s5);
    mem = mm.lookup_identifier(idtable.add_string("x"));
    reg = mem->load(ccon5);
    REQUIRE(reg->get_name() == T0);
    ccon5.write_out();
    lines = split(s5.str());
    REQUIRE(lines.size() == 4);

    REQUIRE(lines[1] == "\tlw\t$t0, 88($fp)");
    REQUIRE(lines[2] == "\tlw\t$t0, 12($t0)");

    
    mm.add_identifier(idtable.add_string("h"));
    stringstream s6;
    CodeContainer ccon6(s6);
    mem = mm.lookup_identifier(idtable.add_string("h"));
    reg = mem->load(ccon6);
    ccon6.write_out();
    REQUIRE(reg->get_name() == T6);
    REQUIRE(split(s6.str()).size() == 2);

    mm.remove_identifier(idtable.add_string("h"));

}
