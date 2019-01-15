<template class = T>

enum class PropertyType {Integer, Float, Bool}


class PropertyValue {
  void * value = nullptr;
  PropertyType pType;

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


  FLOAT getFloat() {
    if(pType!=Float) {
      throw (std::logic_error("Cannot set integer properties for this object"));
    }
  }
  ~PropertyValue() {
    if (value) {
      delete value;
    }
  }
}

class PropertyHolder {

  map <string, PropertyType> properties;
  virtual void set (string name, int value) {
    if (properties.find(name) == properties.end()) {
      throw (std::logic_error("No property '" +  "' for this object"));
    }
    throw (std::logic_error("Cannot set integer properties for this object"));

  }

  virtual void set (string name, FLOAT value){
    if (properties.find(name) == properties.end()) {
      throw (std::logic_error("No property '" +  "' for this object"));
    }
    throw (std::logic_error("Cannot set float properties for this object"));
  };

  virtual void set (string name, bool value){
    if (properties.find(name) == properties.end()) {
      throw (std::logic_error("No property '" +  "' for this object"));
    }
    throw (std::logic_error("Cannot set boolean properties for this object"));
  };

  <template class = T>
  virtual T get(string pName) =0;


}

// int getInt(string propName)

class PropertyColour: Colour, PropertyHolder {


  PropertyColour::PropertyColour {
    properties['red'] = Float;
    properties['green'] = Float;
    properties['blue'] = Float;
  }



  virtual void set (string name, FLOAT data) {
    if (name == 'red') {
      r = (FLOAT) data;
    }
    else if (name == 'green') {
      g = (FLOAT) data;
    }
    else if (name == 'blue') {
      b = (FLOAT) data;
    }
    else {
      throw (std::logic_error("no float property ' " + name + "' for this object"));
    }
  }

  <template class = T>
    virtual T get(string pName) {
    if (name == 'red') {
      return PropertyValue(r);
    }
    if (name == 'green') {
      return PropertyValue(g);
    }
    if (name == 'blue') {
      return PropertyValue(b);
    }
  }

  PropertyValue get(string name) {
    if (name == 'red') {
      return PropertyValue(r);
    }
    if (name == 'green') {
      return PropertyValue(g);
    }
    if (name == 'blue') {
      return PropertyValue(b);
    }
  }

}
