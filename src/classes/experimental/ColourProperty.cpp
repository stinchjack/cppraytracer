#ifdef EXPERIMENTAL
#include "ColourProperty.hpp"


  PropertyColour() {
    properties["red"] = Float;
    properties["green"] = Float;
    properties["blue"] = Float;
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

  template <class T>
  T PropertyColour::get(string Name) {
    if (name == "red") {
      return r;
    }
    if (name == "green") {
      return g;
    }
    if (name == "blue") {
      return b;
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
