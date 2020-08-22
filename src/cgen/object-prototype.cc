#include "object-prototype.h"
#include "labels.h"
#include "basic-symbols.h"

string ObjectPrototype::label() { return label_attr; }
int ObjectPrototype::tag() { return tag_attr ;}
std::vector<attr_class*> ObjectPrototype::attributes() { return attrs_attr; }

MethodsTable& ObjectPrototype::methods_table() { return methods_table_attr; }
AncestorsTable& ObjectPrototype::ancestors_table() { return ancestors_table_attr; }
int ObjectPrototype::depth() { return depth_attr; }
string ObjectPrototype::default_value() { return default_value_attr; }

ObjectPrototype::ObjectPrototype()
{
    initialize_constants();
    label_attr = "empty";
    tag_attr = -1;
    depth_attr = -1;
}

ObjectPrototype::ObjectPrototype(Class_ class_, Features features, ObjectPrototype& parent_obj_prot)
                        : tag_attr(class_->tag),
                          ancestors_table_attr(parent_obj_prot.ancestors_table(), class_) ,
                          methods_table_attr(parent_obj_prot.methods_table(), class_, features),
                          depth_attr(parent_obj_prot.depth() + 1)
{
    string class_name(class_->get_name()->get_string());
    label_attr = OBJECT_PROTOTYPE_LABEL(class_name);

    int n = features->len();
    for(int i = 0; i < n; i++)
        features->nth(i)->filter_feature(attrs_attr);
}


ObjectObjectPrototype::ObjectObjectPrototype(Class_ class_, ObjectPrototype& parent_obj_prot)
                        : ObjectPrototype(class_, nil_Features(), parent_obj_prot)
{

}
StringObjectPrototype::StringObjectPrototype(Class_ class_, ObjectPrototype& parent_obj_prot)
                        : ObjectPrototype(class_, nil_Features(), parent_obj_prot)
{

}

IntObjectPrototype::IntObjectPrototype(Class_ class_, ObjectPrototype& parent_obj_prot) 
                        : ObjectPrototype(class_, nil_Features(), parent_obj_prot)
{

}

BoolObjectPrototype::BoolObjectPrototype(Class_ class_, ObjectPrototype& parent_obj_prot)
                        : ObjectPrototype(class_, nil_Features(), parent_obj_prot)
{

}

