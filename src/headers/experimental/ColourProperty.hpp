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

    virtual void set (string name, FLOAT data);

    template <class T>
    virtual T get(string pName);
    PropertyValue get(string name);
  };


  #endif
#endif
