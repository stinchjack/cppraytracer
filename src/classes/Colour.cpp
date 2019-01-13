#include "Colour.hpp"
#include "Float.hpp"
#include <stdlib.h>


Colour::Colour () {
}

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
  return Colour (this->operator[](0) * c.r,
    this->g * c.g,
    this->b * c.b);
}

float Colour::diff (Colour &c1) {
  float diff = 0.0;

  diff = abs(c1.r - this->r)+
      abs(c1.g- this->g)+
      abs(c1.b- this->b);

  return diff;
}
