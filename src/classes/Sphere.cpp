#include  "Sphere.hpp"
#include <math.h>

SHAPE_PTR SpherePtr() {
  return std::make_shared<Sphere>();
}

map<int, IntersectHit> Sphere::testIntersect (Ray &ray) {
  FLOAT a = ray.start * ray.start;
  FLOAT b = 2.0 * (ray.start * ray.direction);
  FLOAT c = (ray.direction * ray.direction) - 1.0;


  FLOAT discriminant = ((b * b) - (4.0 * a * c));

  map<int, IntersectHit> results;

  if(discriminant < 0) {
    return results;
  }

  FLOAT sqroot = sqrt(discriminant);

  FLOAT two_a = 2.0 * a;
  FLOAT t1 = ((0.0 - b) + sqroot) / (two_a);
  FLOAT t2 = ((0.0 - b) - sqroot) / (two_a);

  if (t1 < 0 && t2 < 0) {
    return results;
  }
  else if (t1 < 0 && t2 >= 0) {
    Point p = ray.calcPos(t2);
    results[t2] = IntersectHit (ray, p,  p);
    results[t2].shape = this;
  }
  else if (t1 >= 0 and t2 < 0) {
    Point p = ray.calcPos(t1);
    results[t1] = IntersectHit (ray, p,  p);
    results[t1].shape = this;
  }
  else {
      if (t1 < t2) {
        Point p = ray.calcPos(t1);
        results[t1] = IntersectHit (ray, p,  p);
        results[t1].shape = this;

        results[t2] = IntersectHit (ray);
        results[t2].shape = this;
      }
      else {
        Point p = ray.calcPos(t2);
        results[t2] = IntersectHit (ray, p, p);
        results[t2].shape = this;
        results[t1] = IntersectHit (ray);
        results[t1].shape = this;
      }
  }

  return results;
}
