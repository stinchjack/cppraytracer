#include "Ray.hpp"

Ray::Ray () {

}

Ray::Ray (const Point& start, const Vector& direction) {
  this->start = start;
  this->direction = direction;
}


Point Ray::calcPos(const FLOAT t) {
 return start + (direction * t);
}


Vector Ray::reflection (Vector &normal)
 {
  Vector ir = direction; // # cartesian_normalise(incident_ray[RAY_DIR]);

  FLOAT ri_dot_n = normal * direction ;


  if (ri_dot_n  < 0) {
    ir = Vector (0,0,0) - ir;
    ri_dot_n = 0 - ri_dot_n;
  }

  Vector twoN_expr = normal * (ri_dot_n * 2.0);

  Vector reflectedVector = twoN_expr - ir; // cartesian_sub(twoN_expr, ir )

  return reflectedVector;

}
