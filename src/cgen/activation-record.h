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
#include <cool-tree.h>

using namespace std;

class ActivationRecord 
{
    private:
        vector<Formal> argv;
        unsigned int tmps;
    
    public:
        ActivationRecord(Formals formals, int tmps);
        /**
          * @returns the number of temporaries required by this method
          */ 
        unsigned int ntmps();

        /**
          * @returns the number of arguments passed to this method
          */
        unsigned int argc();

        /**
          * @returns the arguments of this method
          */
         vector<Formal> args();
};

#endif /*ACTIVATION_RECORD_H*/