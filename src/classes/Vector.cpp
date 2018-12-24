#include "Vector.hpp"
#include <stdio.h>
#include <iostream>


Vector::Vector() {

}

Vector::Vector(FLOAT x, FLOAT y, FLOAT z) {

  hasLength = 0;
  hasNormalised = 0;

  this->x = x;
  this->y = y;
  this->z = z;

}

Vector::Vector(const Point& p) {

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

Vector Vector::normalised() {

  if (!hasNormalised) {

    normX = x /  length();
    normY = y / myLength;
    normZ = z / myLength;

    hasNormalised = 1;
  }
  return Vector (normX, normY, normZ);

}


Vector &Vector::operator*=(FLOAT scale)
{

  hasLength = 0;
  hasNormalised = 0;

  x *= scale;
  y *= scale;
  z *= scale;
  
  return this;
}


Vector Vector::operator*(FLOAT scale)
{
  return Vector(x * scale, y * scale, z* scale);
}

FLOAT Vector::operator*(Point &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}



FLOAT Vector::operator*(Vector &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

Vector Vector::operator+(const Point &rhs) {
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}
