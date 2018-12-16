
#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <array>
#include "Float.hpp"


class Colour: public std::array<float, 3> {

  public :
  Colour ();
  Colour (FLOAT r, FLOAT g, FLOAT b);
  Colour (const Colour&);
  Colour (const Colour*);
  Colour operator+(const Colour&);
  Colour& operator+=(const Colour&);
  Colour operator*(const Colour&);
  Colour operator*(FLOAT scale);
};



#endif
