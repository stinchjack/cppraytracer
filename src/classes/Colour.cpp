#include "Colour.hpp"
#include "Float.hpp"

Colour::Colour() {
  fill((FLOAT)0);
}

Colour::Colour (FLOAT r, FLOAT g, FLOAT b) {
  this->operator[](0) = r;
  this->operator[](1) = g;
  this->operator[](2) = b;
}

Colour::Colour (const Colour &c) {
  this->operator[](0) = c[0];
  this->operator[](1) = c[1];
  this->operator[](2) = c[2];
}

Colour::Colour (const Colour *c) {
  this->operator[](0) = c->operator[](0);
  this->operator[](1) = c->operator[](1);
  this->operator[](2) = c->operator[](2);
}

Colour Colour::operator+(const Colour &c) {
  return Colour (this->operator[](0) + c[0],
    this->operator[](1) + c[1],
    this->operator[](2) + c[2]);
}


Colour& Colour::operator+=(const Colour &c) {
  this->operator[](0) += c[0];
  this->operator[](1) += c[1];
  this->operator[](2) += c[2];
  return *this;
}

Colour Colour::operator*(FLOAT scale) {
  return Colour (this->operator[](0) * scale,
    this->operator[](1)  * scale,
    this->operator[](2)  * scale);
}

Colour Colour::operator*(const Colour &c) {
  return Colour (this->operator[](0) * c[0],
    this->operator[](1) * c[1],
    this->operator[](2) * c[2]);
}
