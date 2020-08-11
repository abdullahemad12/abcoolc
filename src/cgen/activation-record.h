//////////////////////////////////////////////
// ActivationRecord 
//
// This is used to specify the format of the
// activation record for a certain method
//////////////////////////////////////////////

#ifndef ACTIVATION_RECORD_H
#define ACTIVATION_RECORD_H

#include <stringtab.h>
#include <vector>

using namespace std;

class ActivationRecord 
{
    private:
        vector<Symbol> args;
        unsigned int tmps;
    
    public:
        /**
          * @returns the number of temporaries required by this method
          */ 
        unsigned int ntmps();

        /**
          * @returns the number of arguments passed to this method
          */
        unsigned int nargs();

        /**
          * @returns the arguments of this method
          */
         vector<Symbol> args();
};

#endif /*ACTIVATION_RECORD_H*/