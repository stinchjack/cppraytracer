
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <math.h>
#include "Point.hpp"
#include "Float.hpp"

class Ray;

class Vector {
  friend class Ray;
  private:

    FLOAT myLength;
    Vector *myNormalised;
    int hasLength;

    int hasNormalised;

    FLOAT x,y,z;

    inline void setup(void);

  public:

    Vector();
    Vector (FLOAT, FLOAT, FLOAT);
    Vector (const Point& p);
    ~Vector();

    FLOAT operator*(const Vector &rhs); // dot product
    FLOAT cross (const Vector &rhs);
    FLOAT length();
    Vector& normalised();

};


#endif
