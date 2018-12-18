#include  "Sphere.hpp"
#include <math.h>

SHAPE_PTR SpherePtr() {
  return std::make_shared<Sphere>();
}

IntersectResult Sphere::testIntersect (Ray &ray) {
  FLOAT a = ray.start * ray.start;
  FLOAT b = 2.0 * (ray.start * ray.direction);
  FLOAT c = (ray.direction * ray.direction) - 1.0;


  FLOAT discriminant = ((b * b) - (4.0 * a * c));
  if(discriminant < 0) {
    return NoIntersect();
  }

  FLOAT sqroot = sqrt(discriminant);

  FLOAT two_a = 2.0 * a;
  FLOAT t1 = ((0.0 - b) + sqroot) / (two_a);
  FLOAT t2 = ((0.0 - b) - sqroot) / (two_a);

  FLOAT t;

  if (t1 < 0 && t2 < 0) {
    return NoIntersect();
  }
  else if (t1 < 0 && t2 >= 0) {
      t = t2;
  }
  else if (t1 >= 0 and t2 < 0) {
      t = t1;
  }
  else {
      if (t1 < t2) {
        t = t1;
      }
      else {
        t = t2;
      }
  }

  IntersectHit result;
  result.hit = true;
  result.t = t;
  result.shape = this;
  result.raw_point = ray.calcPos(t);
  result.raw_normal = result.raw_point;

  return result;
}
