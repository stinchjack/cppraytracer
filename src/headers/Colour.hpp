
#ifndef COLOUR_HPP
#define COLOUR_HPP

#include <array>
#include "Float.hpp"



class Colour{
//class Colour: public std::array<float, 3> {

  public:
  FLOAT r = 0;
  FLOAT g = 0;
  FLOAT b = 0;

  Colour ();
  Colour (FLOAT r, FLOAT g, FLOAT b);
  Colour (const Colour&);
  Colour (const Colour*);
  Colour operator+(const Colour&);
  FLOAT &operator[](int i);
  Colour& operator+=(const Colour&);
  Colour operator*(const Colour&);
  Colour operator*(FLOAT scale);
  Colour operator/(FLOAT scale);
  float diff (Colour &c1);
};



#endif
