#include  "Sphere.hpp"
#include <math.h>

SHAPE_PTR SpherePtr() {
  return std::make_shared<Sphere>();
}

Vector Sphere::getShapeNormal(IntersectHit &ih) {
  if (!ih.hasShapeNormal) {
    if (!ih.hasShapePoint) {
      ih.shapeRay.calcPos(ih.t, ih.shapePoint);
      ih.hasShapePoint = true;
    }
    ih.shapeNormal = Vector (ih.shapePoint[0],ih.shapePoint[1], ih.shapePoint[2] );
    ih.hasShapeNormal = true;
  }
  return ih.shapeNormal;
}

void Sphere::shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay) {
  FLOAT a = (ray.direction * ray.direction);
  FLOAT b = 2.0 * (ray.direction * ray.start);

  FLOAT c = dot(ray.start, ray. start) - 1.0;//ray.start * ray.start;

  FLOAT discriminant = ((b * b) - (4.0 * a * c));

  if(discriminant < 0) {
    return;
  }

  FLOAT sqroot = sqrt(discriminant);

  FLOAT two_a = 2.0 * a;
  FLOAT t1 = ((0.0 - b) + sqroot) / (two_a);
  FLOAT t2 = ((0.0 - b) - sqroot) / (two_a);



  if (t1 < 0 && t2 < 0) {
    return;
  }

  IntersectHit hit;
  hit.shape = this;
  hit.shapeRay = ray;
  hit.worldRay = worldRay;
  hit.hasShapePoint = false;
  hit.hasShapeNormal = false;

  if (t1 < 0 && t2 >= 0) {
    //Point p = ray.calcPos(t2);
    results.addResult(t2, hit);
  }
  else if (t1 >= 0 && t2 < 0) {
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
