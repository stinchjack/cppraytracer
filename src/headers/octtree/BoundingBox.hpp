#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP


#include "Point.hpp"
#include "Transform.hpp"
#include <vector>

using namespace std;
struct BoundingBoxPlanes {
  FLOAT left;
  FLOAT right;
  FLOAT top;
  FLOAT bottom;
  FLOAT front;
  FLOAT back;
};

class BoundingBox {
private:

  vector<vector<vector<Point>>> shapeBox; //sahpe space
  vector<vector<vector<Point>>> transformedBox; //world space

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
