/*
* Disclaimer: the singleton pattern here is based on the design mentioned here:
* https://stackoverflow.com/a/1008289/6548856
*/

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <type_traits>

/*Any class extending this must declare it as a friend*/
template <typename T>
class Singleton 
{
    protected:
        Singleton() {}
        ~Singleton() {}
    public:
    
     /*delete those methods to avoid unwanted errors */
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;
    
    /**
     * References: https://stackoverflow.com/a/30687399/6548856
     * This is equivalent to the self type in COOL
     */
    static T& instance()
    {
        static T t;
        return t;
    }
};


#endif /*SINGLETON_H*/