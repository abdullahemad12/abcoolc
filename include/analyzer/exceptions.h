#include <exception>
#include <cool-tree.h>


class graph_exception : std::exception
{
    private:
        Class_ faulty_class;
    public:
        graph_exception(Class_ faulty_class) : faulty_class(faulty_class) { }
        virtual Class_ get_faulty_class() { return faulty_class; }
};

class class_redefinition_exception : graph_exception {
        const char* msg;
        class_redefinition_exception(Class_ faulty_class) : graph_exception(faulty_class)
        {
            faulty_class->get_name();
        }
};

