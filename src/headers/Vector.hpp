
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>
#include "Point.hpp"
#include "Float.hpp"

class Ray;

class Vector;

class Vector {
  friend class Ray;
  friend class Transform;
  friend class Light;
  friend class PointLight;

  private:

    FLOAT myLength;
    FLOAT normX, normY, normZ;
    int hasLength;

    int hasNormalised;

    FLOAT x,y,z;

  public:

    Vector();
    Vector (FLOAT, FLOAT, FLOAT);
    Vector (const Point& p);

    Vector operator*(FLOAT scale); // scale
    Vector& operator*=(FLOAT scale);
    FLOAT operator*(Vector &rhs); // dot product
    FLOAT operator*(Point &rhs); // dot product
    Vector operator+(const Point &rhs);
    Vector& operator+=(const Vector &rhs);
    FLOAT cross (const Vector &rhs);
    FLOAT length();
    Vector normalised();
    Vector &normalise();


};


#endif
