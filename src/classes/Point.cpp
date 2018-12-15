#include "Point.hpp"
#include "Float.hpp"

FLOAT* point_add (FLOAT *lhs, const FLOAT *rhs) {

  lhs[0] += rhs[0];
  lhs[1] += rhs[1];
  lhs[2] += rhs[2];

  return lhs;
}

FLOAT* point_sub (FLOAT *lhs, const FLOAT *rhs) {

  lhs[0] -= rhs[0];
  lhs[1] -= rhs[1];
  lhs[2] -= rhs[2];

  return lhs;
}

void nothing();
