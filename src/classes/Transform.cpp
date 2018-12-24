#include "Transform.hpp
Transform::setShift (Point &p) {
  doShift = true;
  shift = p;
}

Point Transform::transform(Point &p) {
  
  if (doShift) {
    return p + shift;
  }
  return p;
}


Point Transform::inverseTransform(Point &p) {
  
  if (doShift) {
    return p - shift;
  }
  return p;
}

Vector Transform::transform(Vector &v) {
  
  if (!doScale && !doRotate) {
    return Vector(v);
  }
  if (doScale && !doRotate) {
    return Vector * scale;
  }

}
