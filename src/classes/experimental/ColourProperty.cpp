#ifdef EXPERIMENTAL
#include "ColourProperty.hpp"
#include "Property.hpp"

  PropertyColour::PropertyColour() {
    properties["red"] = PropertyType::Float;
    properties["green"] = PropertyType::Float;
    properties["blue"] = PropertyType::Float;
    r=0;
    g=0;
    b=0;
  }

  PropertyColour::PropertyColour (FLOAT r, FLOAT g, FLOAT b){
    properties["red"] = PropertyType::Float;
    properties["green"] = PropertyType::Float;
    properties["blue"] = PropertyType::Float;
    this->r=r;
    this->g=g;
    this->b=b;

  }
  PropertyColour::PropertyColour (const Colour& c){
    properties["red"] = PropertyType::Float;
    properties["green"] = PropertyType::Float;
    properties["blue"] = PropertyType::Float;
    this->r=c.r;
    this->g=c.g;
    this->b=c.b;

  }
  PropertyColour::PropertyColour (const Colour* c) {

      properties["red"] = PropertyType::Float;
      properties["green"] = PropertyType::Float;
      properties["blue"] = PropertyType::Float;
      this->r=c->r;
      this->g=c->g;
      this->b=c->b;


  }

  void PropertyColour::set (string name, FLOAT data) {
    if (name == "red") {
      r = (FLOAT) data;
    }
    else if (name == "green") {
      g = (FLOAT) data;
    }
    else if (name == "blue") {
      b = (FLOAT) data;
    }
    else {
      throw (std::logic_error("no float property " " + name + "" for this object"));
    }
  }


  FLOAT PropertyColour::getFloat (string name) {
    if (name == "red") {
      return r;
    }
    else if (name == "green") {
      return g;
    }
    else if (name == "blue") {
      return b;
    }
    else {
      throw (std::logic_error("no float property " " + name + "" for this object"));
    }
  }


// Vector, Pont

#endif
