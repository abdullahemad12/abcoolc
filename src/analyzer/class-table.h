#ifndef CLASS_TABLE_H_
#define CLASS_TABLE_H_

#include <unordered_map>
#include <symtab.h>
#include <cool-tree.h>
#include <singleton.h>

using namespace std;

static char* no_type = "_no_type"; 

class ClassTable
{
    friend Singleton<ClassTable>;
    private:
        unordered_map<Symbol, Class_> classes;
        bool is_init = false;
    protected:
        ClassTable() { }
        ~ClassTable() { }

    private:
        void check_for_invalid_inheritance(void);
        void check_for_invalid_definitions(void);
        Classes install_basic_classes(Classes classes);

    public:
        void init(Classes classes);
        auto begin(void) { return classes.begin(); }
        auto end(void) { return  classes.end(); }
        bool contains(Symbol class_);
        Class_ operator[](Symbol sym) { return classes[sym]; }
};



#endif /*CLASS_TABLE_H_*/