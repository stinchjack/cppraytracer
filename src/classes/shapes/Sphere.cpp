#include  "Sphere.hpp"
#include <math.h>

Sphere::Sphere() {
  box = BoundingBox(-1,1,-1,1,-1,1);
}

Vector Sphere::getShapeNormal(IntersectHit *ih) {
  return Vector(ih->getShapePoint());

}

void Sphere::shapeTestIntersect (QueueItemResults &results, Ray &ray, Ray &worldRay) {
  FLOAT a = (ray.direction * ray.direction);
  FLOAT c = (ray.start * ray. start) - 1.0;//ray.start * ray.start;
  FLOAT b = 2.0 * (ray.direction * ray.start);
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



  if (ray.isShadowRay) {
    if ((t1 > 0  && t1 <=1.0 )||
      (t2 > 0 && t2<=1.0)) {
      results.addResult(0, this);
    }
    return;
  }


  if (t1 < 0 && t2 >= 0) {
    //Point p = ray.calcPos(t2);

    IHPtr hit = results.addResult (t2, this);
    hit->setShapeRay(ray);
    hit->setWorldRay(worldRay);
  }
  else if (t1 >= 0 && t2 < 0) {
    //Point p = ray.calcPos(t1);

    IHPtr hit = results.addResult (t1, this);
    hit->setShapeRay(ray);
    hit->setWorldRay(worldRay);


  }
  else if (t1 > 0  &&  t2 > 0) {

      IHPtr hit = results.addResult (t1, this);
      hit->setShapeRay(ray);
      hit->setWorldRay(worldRay);

      IHPtr hit2 = results.addResult (t2, this);
      hit2->setShapeRay(ray);
      hit2->setWorldRay(worldRay);

  }

}
