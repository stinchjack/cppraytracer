#include "Vector.hpp"


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
  if (hasLength) {
    myLength = sqrt ((data[0] * data[0]) + (data[1] * data[1]) + (data[2] * data[2]));
    hasLength = 1;
  }

  return myLength;
}

Vector& Vector::normalised() {

  if (!hasNormalised) {

    myNormalised = new Vector (data[0] /  length(), data[1] / myLength, data[2]/ myLength);
    hasNormalised = 1;
  }
  return *myNormalised;

}

Vector::~Vector() {
  if (hasNormalised) {
    delete myNormalised;
  }

}
