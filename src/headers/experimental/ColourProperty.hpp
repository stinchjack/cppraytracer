#ifdef EXPERIMENTAL

  #ifndef COLOURPROPERTY_HPP
  #define COLOURPROPERTY_HPP

  #include "Property.hpp"
  class PropertyColour: Colour, PropertyHolder {


  public:
    PropertyColour::PropertyColour();

    virtual void set (string name, FLOAT data);

    <template class = T>
    virtual T get(string pName);
    PropertyValue get(string name);
  };


  #endif
#endif
