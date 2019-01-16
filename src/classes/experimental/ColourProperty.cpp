#ifdef EXPERIMENTAL
#include "ColourProperty.hpp"


  PropertyColour::PropertyColour {
    properties["red"] = Float;
    properties["green"] = Float;
    properties["blue"] = Float;
  }



  virtual void PropertyColour::set (string name, FLOAT data) {
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

  <template class = T>
  virtual T PropertyColour::get(string Name) {
    if (name == "red") {
      return PropertyValue(r);
    }
    if (name == "green") {
      return PropertyValue(g);
    }
    if (name == "blue") {
      return PropertyValue(b);
    }
  }

  PropertyValue PropertyColour::get(string name) {
    if (name == "red") {
      return PropertyValue(r);
    }
    if (name == "green") {
      return PropertyValue(g);
    }
    if (name == "blue") {
      return PropertyValue(b);
    }
  }

}
#endif
