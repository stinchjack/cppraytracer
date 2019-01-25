#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "Colour.hpp"
#include "Ray.hpp"
#include "IntersectHit.hpp"
#include "QueueItemResults.hpp"
#include "BoundingBox.hpp"
#include "Transform.hpp"
#include "Texture.hpp"
#include "Mapping.hpp"
#include <memory>
using namespace std;


//class Transform;

#define SHAPE_PTR shared_ptr<Shape>
typedef shared_ptr<Shape> ShapePtr;

//class Shape;
//typedef shared_ptr<Shape> ShapePtr;


class Shape {

private:

  bool hasTransformedEyePoint = false;
  Point transformedEyePoint;

#ifdef EXPERIMENTAL
protected:
  BoundingBox box;
#endif

public:
  Shape();
  Transform transformation;
  shared_ptr<Texture> diffuse = nullptr;
  shared_ptr<Texture> specular = nullptr;
  shared_ptr<Texture> transparency = nullptr;
  shared_ptr<Mapping> mapping = nullptr;

  template <class T, class... Args>
    shared_ptr<T> setDiffuse (Args&&... args) {
    diffuse  = make_shared<T>(args...);

    return diffuse;

  }

  /*void setDiffuse (const shared_ptr<Texture>);
  void setSpecular (const shared_ptr<Texture>);
  void setTransparency (const shared_ptr<Texture>);*/
  void setMapping (const shared_ptr<Mapping>);

  void testIntersect (QueueItemResults &results, Ray &ray);
  Ray transform (Ray &ray);

  void setShift(const Point &p);
  void setScale(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ );
  void setRotate(const Vector &axis, FLOAT angle);

  virtual void shapeTestIntersect (QueueItemResults &results, Ray &shapeRay, Ray &worldRay) = 0;
  virtual Vector getShapeNormal(IntersectHit *ih) = 0;
  #ifdef EXPERIMENTAL
    BoundingBoxPlanes getWorldBoundingPlanes();
  #endif
};


#endif
