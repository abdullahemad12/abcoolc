#ifndef DEFAULT_VALUE_H
#define DEFAULT_VALUE_H

#include <string>

using namespace std;

class CodeContainer;
class MemoryManager;
class Register;

/////////////////////////////////////////////////
// DefaultValue classes
//
// Represents the default values of all classes
// 1. Int: a label to the zero constant
// 2. String: a label to the empty string constant
// 3. Bool: a label to the false constant
// 4  Null: the value zero
/////////////////////////////////////////////////


class DefaultValue {
    public:
  /**
    * @brief loads the default value into the $a0 register
    * @effects: adds code to code container that loads a default value into $a0
    * @modifies: ccon
    * @param CodeContainer& the code container
    * @param MemoryManager& an instance of the memory manager
    * @returns Register* the $a0 (accumelator) register
    */  
  virtual Register* load_value(CodeContainer& ccon, MemoryManager& mem) = 0;
  /**
    * @brief return the default value stored in this object
    * @returns string the default value
    */ 
  virtual string value() = 0;

  virtual ~DefaultValue();
};

class DefaultValueLabel : public DefaultValue
{
  private:
    string label;
  public:
    DefaultValueLabel(string label);
    Register* load_value(CodeContainer& ccon, MemoryManager& mem) override;
    string value() override;
    ~DefaultValueLabel();
};

class DefaultNull : public DefaultValue
{
  public:
    Register* load_value(CodeContainer& ccon, MemoryManager& mem) override;
    string value() override;
    ~DefaultNull();
};



#endif /*DEFAULT_VALUE_H*/