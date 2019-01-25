
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>
#include "Point.hpp"
#include "Float.hpp"

class Ray;

class Vector;

class Vector {
  friend class Point;

  friend class Ray;
  friend class Transform;
  friend class Light;
  friend class PointLight;
  friend class Square;
  friend class UniformSpaceSubdivider;

  private:

    FLOAT myLength;
    FLOAT normX, normY, normZ;
    int hasLength=0;
    int hasNormalised=0;

    FLOAT x,y,z;

  public:

    inline Vector() {};
    inline Vector (FLOAT, FLOAT, FLOAT);
    Vector (const Point& p);

    inline Vector operator*(FLOAT scale); // scale
    inline Vector& operator*=(FLOAT scale);
    inline FLOAT operator*(Vector &rhs); // dot product
    FLOAT operator*(const Point &rhs) const; // dot product
    Vector operator+(const Point &rhs) const;
    inline Vector operator-(Point &rhs) const;
    inline Vector operator-(Vector &rhs) const;
    inline Vector& operator+=(const Vector &rhs);
    inline void reverse();
    FLOAT cross (const Vector &rhs);
    FLOAT length();
    Vector normalised();
    Vector &normalise();


};

Vector::Vector(FLOAT x, FLOAT y, FLOAT z) {

  this->x = x;
  this->y = y;
  this->z = z;

}

void Vector::reverse(){
  x = 0 - x;
  y = 0 - y;
  z = 0 - z;
}

Vector &Vector::operator*=(FLOAT scale) {

  hasLength = 0;
  hasNormalised = 0;

  x *= scale;
  y *= scale;
  z *= scale;

  return *this;
}

Vector Vector::operator*(FLOAT scale) {
  return Vector(x * scale, y * scale, z* scale);
}

FLOAT Vector::operator*(Vector &rhs) {
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


#endif
