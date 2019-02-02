#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP


#include "Point.hpp"
#include "Transform.hpp"
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
class BoundingBoxPlanes {
public:
  FLOAT left;
  FLOAT right;
  FLOAT top;
  FLOAT bottom;
  FLOAT front;
  FLOAT back;

  inline void update(Point &p);
};

inline void BoundingBoxPlanes::update(Point &p) {

  /*left = min(p.x, left);
  top = min(p.y, top);
  front = min(p.z, front);

  right= max(p.x, right);
  bottom= max(p.x, bottom);
  back= max(p.x, back);*/


  if (this->left > p.x) {
    this->left = p.x;
  }
  if (this->right < p.x) {
    this->right = p.x;
  }

  if (this->top > p.y) {
    this->top = p.y;
  }
  if (this->bottom < p.y) {
    this->bottom = p.y;
  }

  if (this->front > p.z) {
    this->front = p.z;
  }
  if (this->back < p.z) {
    this->back = p.z;
  }
}

class BoundingBox {
private:

  //vector<vector<vector<Point>>> shapeBox; //sahpe space
  //vector<vector<vector<Point>>> transformedBox; //world space

  array<array<array<Point, 2>,2>,2> shapeBox;
  array<array<array<Point, 2>,2>,2> transformedBox;


  BoundingBoxPlanes shapeSpacePlanes;
  BoundingBoxPlanes worldSpacePlanes;
  bool hasTransformedBox = false;
  bool hasTransformedPlanes = false;

public:

  BoundingBox(BoundingBox &bbp);
  BoundingBox(BoundingBoxPlanes &bbp);

  BoundingBox();

  BoundingBox(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) ;

  void setupArrays();
  void setup(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back);

  void makeWorldBox(Transform &transform);

  BoundingBoxPlanes getWorldPlanes(Transform &transform);


};



#endif
