#ifdef EXPERIMENTAL

  #ifndef COLOURPROPERTY_HPP
  #define COLOURPROPERTY_HPP

  #include "Property.hpp"
  #include "Float.hpp"
  #include "Colour.hpp"
  #include <string>

  using namespace std;
  class PropertyColour: public Colour, public PropertyHolder {


  public:

    PropertyColour();
    PropertyColour (FLOAT r, FLOAT g, FLOAT b);
    PropertyColour (const Colour&);
    PropertyColour (const Colour*);
    virtual void set (string name, FLOAT data);
    virtual FLOAT getFloat (string name);
  };


  #endif
#endif
