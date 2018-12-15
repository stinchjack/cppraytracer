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

  data[0] = x;
  data[1] = y;
  data[2] = z;

}

Vector::Vector(const FLOAT *p) {

  setup();
  hasLength = 0;
  hasNormalised = 0;

  data[0] = p[0];
  data[1] = p[1];
  data[2] = p[2];
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
