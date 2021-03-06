#include "activation-record.h"


ActivationRecord::ActivationRecord(Formals formals, int tmps)
{
    this->tmps = tmps;
    int n = formals->len();
    for(int i = 0; i < n; i++)
        argv.push_back(formals->nth(i));
}

unsigned int ActivationRecord::ntmps() 
{
    return tmps;
}


unsigned int ActivationRecord::argc() 
{
    return argv.size();
}


vector<Formal> ActivationRecord::args() 
{
    return argv;
}
