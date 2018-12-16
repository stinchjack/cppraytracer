#include "Point.hpp"
#include "Float.hpp"

FLOAT* colour_add (FLOAT *lhs, const FLOAT *rhs) {

  lhs[0] += rhs[0];
  lhs[1] += rhs[1];
  lhs[2] += rhs[2];

  return lhs;
}

FLOAT* colour_scale (FLOAT *lhs, const FLOAT *rhs) {

  lhs[0] *= rhs[0];
  lhs[1] *= rhs[1];
  lhs[2] *= rhs[2];

  return lhs;
}

FLOAT* colour_scale (FLOAT *lhs, FLOAT rhs) {

  lhs[0] *= rhs;
  lhs[1] *= rhs;
  lhs[2] *= rhs;

  return lhs;
}
