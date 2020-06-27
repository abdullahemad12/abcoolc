#include <type-table.h>
#include <cool-tree.h>
#include <unordered_set>

#define SET_CONTAINS(map, element) (map.find(element) != map.end())

// prototypes
void inheritance_from_basic_classes_detection(Classes classes);
void inheritance_from_undefined_class(Classes classes);
void misuse_of_self_type(Classes classes);
void redefinition_of_classes_detection(Classes classes);
void redefinition_of_basic_classes_detection(Classes classes);


TypeTable::TypeTable(Classes classes)
{
    initialize_constants();
    // insert all the types in the set
    for(int i = 0, n = classes->len(); i < n; i++)
        all_defined_types.insert(classes->nth(i)->get_name());
    basic_types = {Int, Str, Bool};
    built_in_types = {Int, Str, Bool, Object, IO};
    reserved_types = { SELF_TYPE };
    reserved_identifiers = { self };

    all_defined_types.insert(SELF_TYPE);

    assert(SET_CONTAINS(all_defined_types, Int));
    assert(SET_CONTAINS(all_defined_types, Str));
    assert(SET_CONTAINS(all_defined_types, Bool));
    assert(SET_CONTAINS(all_defined_types, IO));
    assert(SET_CONTAINS(all_defined_types, Int));

}

bool TypeTable::contains(Symbol type)
{
    return SET_CONTAINS(all_defined_types, type);
}

bool TypeTable::is_basic_type(Symbol type)
{
    return SET_CONTAINS(basic_types, type);
}

bool TypeTable::is_reserved_type(Symbol type)
{
    return SET_CONTAINS(reserved_types, type);
}

bool TypeTable::is_reserved_identifier(Symbol id)
{
    return SET_CONTAINS(reserved_identifiers, id);
}

bool TypeTable::is_built_in_type(Symbol id)
{
    return SET_CONTAINS(built_in_types, id);
}
