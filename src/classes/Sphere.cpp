#include  "Sphere.hpp"
#include <math.h>

SHAPE_PTR SpherePtr() {
  return std::make_shared<Sphere>();
}

Vector Sphere::getShapeNormal(IntersectHit &ih) {
  return Vector(ih.getShapePoint());

}

void Sphere::shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay) {
  FLOAT a = (ray.direction * ray.direction);
  FLOAT b = 2.0 * (ray.direction * ray.start);

  FLOAT c = (ray.start * ray. start) - 1.0;//ray.start * ray.start;
  //FLOAT c = dot(ray.start, ray. start) - 1.0;//ray.start * ray.start;

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



  if (worldRay.isShadowRay) {
    results.addResult(0, IntersectHit (this, 0));
    return;
  }


  if (t1 < 0 && t2 >= 0) {
    //Point p = ray.calcPos(t2);

    IntersectHit hit(this, t2);
    hit.setShapeRay(ray);
    hit.setWorldRay(worldRay);

    results.addResult(t2, hit);
  }
  else if (t1 >= 0 && t2 < 0) {
    //Point p = ray.calcPos(t1);

    IntersectHit hit(this, t1);
    hit.setShapeRay(ray);
    hit.setWorldRay(worldRay);


    results.addResult(t1, hit);

  }
  else if (t1 > 0  &&  t2 > 0) {

      IntersectHit hit1(this, t1);
      hit1.setShapeRay(ray);
      hit1.setWorldRay(worldRay);


      results.addResult(t1, hit1);

      IntersectHit hit2(this, t2);
      hit2.setShapeRay(ray);
      hit2.setWorldRay(worldRay);

      results.addResult(t2, hit2);


  }

}
