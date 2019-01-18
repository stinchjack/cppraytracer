#ifdef EXPERIMENTAL
  #include "Property.hpp"

  /*PropertyValue::PropertyValue(int newValue) {
    pType = PropertyType::Integer;
    int *tempVal = new int;
    *tempVal = newValue;
    this->value = (void *)tempVal;

  }
  PropertyValue::PropertyValue(FLOAT newValue){
    pType = PropertyType::Float;
    float *tempVal = new FLOAT;
    *tempVal = newValue;
    this->value = (void *)tempVal;

  }
  PropertyValue::PropertyValue(bool newValue){
    pType = PropertyType::Bool;
    bool *tempVal = new bool;
    *tempVal = newValue;
    this->value = (void *)tempVal;
  }*/

/*
  FLOAT PropertyValue::getFloat() {
    if(pType!=PropertyType::Float) {
      throw (std::logic_error("Cannot set integer properties for this object"));
    }
  }*/


/*
  PropertyValue::~PropertyValue() {
    if (value) {

      if (pType == PropertyType::Integer) {
        delete (int *) value;
      }

      if (pType == PropertyType::Bool) {
        delete (bool *) value;
      }

      if (pType == PropertyType::Float) {
        delete (FLOAT *) value;
      }
    }
  }
*/

void PropertyHolder::set (string name, int value) {
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" +  name +"' for this object"));
  }
  throw (std::logic_error("Cannot set integer properties for this object"));

}

void PropertyHolder::set (string name, FLOAT value){
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" +  name + "' for this object"));
  }
  throw (std::logic_error("Cannot set float properties for this object"));
};

void PropertyHolder::set (string name, bool value){
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" + name + "' for this object"));
  }
  throw (std::logic_error("Cannot set boolean properties for this object"));
};
/*
template <class T>
T PropertyHolder::get (string name) {
  if (properties.find(name) == properties.end()) {
    throw (std::logic_error("No property '" + name +  "' for this object"));
  }
  if (properties[name] == PropertyType::Integer) {
    getInt(name);
  }
  if (properties[name] == PropertyType::Bool) {
    getBool(name);
  }
  if (properties[name] == PropertyType::Float) {
    getFloat(name);
  }
}*/

int PropertyHolder::getInt (string name) {
  throw (std::logic_error("no integer properties for this object"));
}

bool PropertyHolder::getBool (string name) {
  throw (std::logic_error("no boolean properties for this object"));
}

FLOAT PropertyHolder::getFloat (string name) {
  throw (std::logic_error("no Float properties for this object"));
}




#endif
