#include "Vector.hpp"
#include <stdio.h>
#include <iostream>


void inline Vector::setup(void) {
  hasLength = 0;
  hasNormalised = 0;

}

Vector::Vector() {
  setup();
}

Vector::Vector(FLOAT x, FLOAT y, FLOAT z) {
  setup();
  hasLength = 0;
  hasNormalised = 0;

  this->x = x;
  this->y = y;
  this->z = z;

}

Vector::Vector(const Point& p) {

  setup();
  hasLength = 0;
  hasNormalised = 0;

  this->x = p.x;
  this->y = p.y;
  this->z = p.z;

}


FLOAT Vector::length() {

  if (!hasLength) {
    myLength = sqrt ((x * x) + (y * y) + (z * z));
    hasLength = 1;
  }

  return myLength;
}

Vector& Vector::normalised() {

  if (!hasNormalised) {

    myNormalised = new Vector (x /  length(), y / myLength, z/ myLength);
    hasNormalised = 1;
  }
  return *myNormalised;

}

FLOAT Vector::operator*(Point &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

FLOAT Vector::operator*(Vector &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}


Vector::~Vector() {
  if (hasNormalised) {
    delete myNormalised;
  }

}
