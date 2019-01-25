#include "Vector.hpp"
#include <stdio.h>
#include <iostream>


/*
Vector::Vector(FLOAT x, FLOAT y, FLOAT z) {

  hasLength = 0;
  hasNormalised = 0;

  this->x = x;
  this->y = y;
  this->z = z;

}




void Vector::reverse(){
  x = 0 - x;
  y = 0 - y;
  z = 0 - z;
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



FLOAT Vector::operator*(Vector &rhs)
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}


Vector Vector::operator-(Vector &rhs) const {
  return Vector(x - rhs.x, y - rhs.y, z- rhs.z);
}

Vector & Vector::operator+=(const Vector &rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}
*/

Vector Vector::normalised() {

  if (!hasNormalised) {

    normX = x /  length();
    normY = y / myLength;
    normZ = z / myLength;
    hasNormalised = true;

  }
  Vector newVec(normX, normY, normZ);
  newVec.myLength = 1;
  newVec.hasLength = true;
  newVec.hasNormalised =true;
  return newVec;

}

Vector & Vector::normalise() {

  if (!hasNormalised) {

    x /=  length();
    y /=  myLength;
    z /= myLength;
    myLength = 1;
    hasLength = true;
    hasNormalised = true;
  }
  return *this;

}


FLOAT Vector::operator*(const Point &rhs) const //dot product
{
  return (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
}


Vector Vector::operator+(const Point &rhs) const {
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator-(Point &rhs) const {
  return Vector(x - rhs.x, y - rhs.y, z- rhs.z);
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
