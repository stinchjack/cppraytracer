#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "Colour.hpp"
#include "Ray.hpp"
#include "IntersectResult.hpp"
#include "QueueItemResults.hpp"
#include "Transform.hpp"

#define SHAPE_PTR shared_ptr<Shape>

class Shape {

  protected:

  Colour diffuse;
  Colour specular;
  Colour transparency;



  /*
  Transform transform;
  virtual Ray transformRay(const Ray &) = 0;
  */

  public:
  Transform transformation;
  void setDiffuse (const Colour &);
  void setSpecular (const Colour &);
  void setTransparency (const Colour &);

  void testIntersect (QueueItemResults &results, Ray &ray);
  Ray transform (Ray &ray);

  virtual void shapeTestIntersect (QueueItemResults &results, Ray &ray) = 0;
};


#endif
