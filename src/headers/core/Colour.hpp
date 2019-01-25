
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

  inline Colour (){};
  inline Colour (FLOAT r, FLOAT g, FLOAT b);
  inline Colour (const Colour&);
  inline Colour (const Colour*);
  inline Colour operator+(const Colour&);
  inline FLOAT &operator[](int i);
  inline Colour& operator+=(const Colour&);
  inline Colour operator*(const Colour&);
  inline Colour operator*(FLOAT scale);
  inline Colour operator/(FLOAT scale);
  inline FLOAT diff (Colour &c1);
};


FLOAT & Colour::operator[](int i) {
  switch (i) {
    case 0:
    return r;
    break;

    case 1: return g; break;

    case 2: return b; break;

    default:
    return r;
    break;
  }
}

Colour::Colour (FLOAT r, FLOAT g, FLOAT b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

Colour::Colour (const Colour &c) {
  this->r = c.r;
  this->g = c.g;
  this->b = c.b;
}

Colour::Colour (const Colour *c) {
  this->r = c->r;
  this->g = c->g;
  this->b = c->b;
}

Colour Colour::operator+(const Colour &c) {
  return Colour (
    this->r + c.r,
    this->g + c.g,
    this->b + c.b);
}


Colour& Colour::operator+=(const Colour &c) {
  this->r += c.r;
  this->g += c.g;
  this->b += c.b;
  return *this;
}

Colour Colour::operator*(FLOAT scale) {
  return Colour (this->r * scale,
    this->g  * scale,
    this->b  * scale);
}
Colour Colour::operator/(FLOAT scale) {
  return Colour (this->r / scale,
    this->g  / scale,
    this->b  / scale);
}

Colour Colour::operator*(const Colour &c) {
  return Colour (this->r * c.r,
    this->g * c.g,
    this->b * c.b);
}

FLOAT Colour::diff (Colour &c1) {
  FLOAT diff = 0.0;
  FLOAT rdiff = c1.r - this->r;
  FLOAT gdiff = c1.g - this->g;
  FLOAT bdiff = c1.b - this->b;


  diff += (rdiff > 0? rdiff: - rdiff );
  diff += (gdiff > 0? gdiff: - gdiff );
  diff += (bdiff > 0? bdiff: - bdiff );

  return diff;
}



#endif
