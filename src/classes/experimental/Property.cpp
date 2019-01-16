#ifdef EXPERIMENTAL
  #include "Property.hpp"

  PropertyValue::PropertyValue(int newValue) {
    pType = Integer;
    int tempVal = new int;
    *tempVal = newValue;
    this->value = (void *)tempVal;

  }
  PropertyValue::PropertyValue(FLOAT value){
    pType = Float;
    int tempVal = new FLOAT;
    *tempVal = newValue;
    this->value = (void *)tempVal;

  }
  PropertyValue::PropertyValue(bool value){
    pType = Bool;
    int tempVal = new bool;
    *tempVal = newValue;
    this->value = (void *)tempVal;
  }


  FLOAT PropertyValue::getFloat() {
    if(pType!=Float) {
      throw (std::logic_error("Cannot set integer properties for this object"));
    }
  }



  PropertyValue::~PropertyValue() {
    if (value) {
      delete value;
    }
  }


void PropertyHolder::set (string name, int value) {
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" +  name +"' for this object"));
  }
  throw (std::logic_error("Cannot set integer properties for this object"));

}

void PropertyHolder::set (string name, FLOAT value){
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" +  "' for this object"));
  }
  throw (std::logic_error("Cannot set float properties for this object"));
};

void PropertyHolder::set (string name, bool value){
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" +  "' for this object"));
  }
  throw (std::logic_error("Cannot set boolean properties for this object"));
};




#endif
