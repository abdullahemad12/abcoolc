#include "object-prototype.h"
#include "basic-symbols.h"
#include "memory-manager.h"
#include "static-memory.h"
#include "default-value.h"
#include "emit.h"

string ObjectPrototype::label() { return label_attr; }

int ObjectPrototype::tag() { return tag_attr ;}

std::vector<attr_class*> ObjectPrototype::attributes() { return attrs_attr; }

std::vector<attr_class*> ObjectPrototype::self_attributes() { return self_attrs_attr; }

MethodsTable& ObjectPrototype::methods_table() { return methods_table_attr; }

AncestorsTable& ObjectPrototype::ancestors_table() { return ancestors_table_attr; }

int ObjectPrototype::depth() { return depth_attr; }

DefaultValue* ObjectPrototype::default_value() { return default_value_attr; }

string ObjectPrototype::name() { return name_attr; }

string ObjectPrototype::init_method_label() { return name() + CLASSINIT_SUFFIX; }

ObjectPrototype::~ObjectPrototype() 
{

}

ObjectPrototype::ObjectPrototype()
{
    initialize_constants();
    label_attr = "empty";
    tag_attr = 0;
    depth_attr = -1;
    default_value_attr = new DefaultNull();
}

ObjectPrototype::ObjectPrototype(Class_ class_, int tag, ObjectPrototype& parent_obj_prot)
                        : name_attr(class_->get_name()->get_string()),
                          tag_attr(tag),
                          attrs_attr(parent_obj_prot.attrs_attr),
                          ancestors_table_attr(parent_obj_prot.ancestors_table(), class_) ,
                          methods_table_attr(parent_obj_prot.methods_table(), class_, class_->get_features()),
                          depth_attr(parent_obj_prot.depth() + 1),
                          default_value_attr(class_->default_value)
{

    Features features;
    Feature feature;
    string class_name(class_->get_name()->get_string());
    label_attr = OBJECT_PROTOTYPE_LABEL(class_name);
    
    features = class_->get_features();

    int n = features->len();
    for(int i = 0; i < n; i++)
    {
        feature = features->nth(i);
        feature->filter_feature(attrs_attr);
        feature->filter_feature(self_attrs_attr);

    }
}

void ObjectPrototype::cgen(CodeContainer& ccon, StaticMemory& stat_mem)
{
    int size;
    
    ancestors_table_attr.cgen(ccon, stat_mem);
    methods_table_attr.cgen(ccon);

    ccon.word(-1);
    ccon.label(label());
    ccon.word(tag());
    size = OBJ_HEADER_SIZE + attrs_attr.size();
    ccon.word(size);
    ccon.word(methods_table().label());
    for(auto attr : attrs_attr)
    {
        ObjectPrototype& obj_prot = stat_mem.lookup_objectprot(attr->get_type());
        ccon.word(obj_prot.default_value()->value());
    }
}

void SystemObjectPrototype::cgen(CodeContainer& ccon, StaticMemory& stat_mem)
{

}


////////////////////////////////////////
// DefaultValue classes
//
//
////////////////////////////////////////

DefaultValue::~DefaultValue() { }

DefaultValueLabel::DefaultValueLabel(string label) : label(label) { }

string DefaultValueLabel::value() { return label; }

Register* DefaultValueLabel::load_value(CodeContainer& ccon, MemoryManager& mem)
{
    Register* acc = mem.acc();
    ccon.la(acc, label);
    return acc;
}

string DefaultNull::value() { return "0"; }

Register* DefaultNull::load_value(CodeContainer& ccon, MemoryManager& mem)
{
    Register* acc = mem.acc();
    ccon.li(acc, 0);
    return acc;
}

DefaultValueLabel::~DefaultValueLabel()
{

}

DefaultNull::~DefaultNull()
{

}
