#include <vector>
#include "cool-tree.h"

using namespace std;

////////////////////////////////////
// Filter Feature 
// 
// Extract Attributes and Methods
////////////////////////////////////
void method_class::filter_feature(vector<attr_class*>& vec)
{

}
void attr_class::filter_feature(vector<attr_class*>& vec)
{
    vec.push_back(this);
}

void method_class::filter_feature(vector<method_class*>& vec)
{
    vec.push_back(this);
}

void attr_class::filter_feature(vector<method_class*>& vec)
{

}