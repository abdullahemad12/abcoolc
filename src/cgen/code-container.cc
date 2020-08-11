#include "code-container.h"

CodeContainer::CodeContainer(ostream& os) : os(os) { }

void CodeContainer::write_out()
{
    os << "# start of generated code\n";
    for(auto code_line : code)
        os << code_line << endl;
    os << "\n# end of generated code\n";
}