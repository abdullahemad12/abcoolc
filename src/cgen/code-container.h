/////////////////////////////////////////////////////////////////
// This class is used to store and emit the generated assembly 
// code. When cgen needs to generate a certain MIPS instruction, 
// it will call the corresponding emit function in this class. 
// This class is responsible to make sure that the emitted code 
// preserves the memory invariants and other conditions mentioned
// in the README of the cgen component
/////////////////////////////////////////////////////////////////

#ifndef CODE_CONTAINER_H
#define CODE_CONTAINER_H


#include <ostream>
#include <string>
#include <vector>

using namespace std;

class CodeContainer 
{
    private:
        vector<string> code;
        ostream& os;

    public:
        CodeContainer(ostream& os);
        void write_out();
};



#endif /*CODE_CONTAINER_H*/