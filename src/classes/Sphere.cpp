#include  "Sphere.hpp"
#include <math.h>

SHAPE_PTR SpherePtr() {
  return std::make_shared<Sphere>();
}

void Sphere::testIntersect (QueueItemResults &results, Ray &ray) {
  FLOAT a = ray.start * ray.start;
  FLOAT b = 2.0 * (ray.start * ray.direction);
  FLOAT c = (ray.direction * ray.direction) - 1.0;


  FLOAT discriminant = ((b * b) - (4.0 * a * c));

  if(discriminant < 0) {
    return;
  }

  FLOAT sqroot = sqrt(discriminant);

  FLOAT two_a = 2.0 * a;
  FLOAT t1 = ((0.0 - b) + sqroot) / (two_a);
  FLOAT t2 = ((0.0 - b) - sqroot) / (two_a);

  IntersectHit hit;
  hit.shape = this;
  hit.ray = ray;

  if (t1 < 0 && t2 < 0) {
    return;
  }
  else if (t1 < 0 && t2 >= 0) {
    //Point p = ray.calcPos(t2);
    results.addResult(t2, hit);
  }
  else if (t1 >= 0 and t2 < 0) {
    //Point p = ray.calcPos(t1);

    results.addResult(t1, hit);

  }
  else {
      if (t1 < t2) {


        results.addResult(t1, hit);

        results.addResult(t2, hit);

      }
      else {
        //Point p = ray.calcPos(t2);
        results.addResult(t2, hit);

        results.addResult(t1, hit);
      }
  }

}
