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

  this->x = p[0];
  this->y = p[1];
  this->z = p[2];

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
  Vector newVec(normX, normY, normZ);
  newVec.myLength = 1;
  newVec.hasLength = true;
  newVec.hasNormalised =true;
  return newVec;

}

Vector & Vector::normalise() {

  if (length() != 1.0) {

    x /=  myLength;
    y /=  myLength;
    z /= myLength;
    myLength = 1;
    hasLength = true;
    hasNormalised = true;
  }
  return *this;

}


Vector &Vector::operator*=(FLOAT scale)
{

  hasLength = 0;
  hasNormalised = 0;

  x *= scale;
  y *= scale;
  z *= scale;

  return *this;
}


Vector Vector::operator*(FLOAT scale)
{
  return Vector(x * scale, y * scale, z* scale);
}

FLOAT Vector::operator*(Point &rhs) //dot product
{
  return (x * rhs[0]) + (y * rhs[1]) + (z * rhs[2]);
}



FLOAT Vector::operator*(Vector &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}

Vector Vector::operator+(const Point &rhs) {
  return Vector(x + rhs[0], y + rhs[1], z + rhs[2]);
}

Vector & Vector::operator+=(const Vector &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}
