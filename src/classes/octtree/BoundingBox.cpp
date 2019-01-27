#include "BoundingBox.hpp"

BoundingBox::BoundingBox() {
  setupArrays();
}

BoundingBox::BoundingBox(BoundingBox &box) {
  this->shapeBox = box.shapeBox;
  this->transformedBox = box.transformedBox;
  this->shapeSpacePlanes = box.shapeSpacePlanes;
  this->hasTransformedBox = box.hasTransformedBox;
  this->hasTransformedPlanes = box.hasTransformedPlanes;
}

BoundingBox::BoundingBox(BoundingBoxPlanes &bbp) {
  BoundingBox(bbp.left, bbp.right, bbp.top, bbp.bottom, bbp.front, bbp.back);
}

BoundingBox::BoundingBox(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) {
  setup(left, right, top, bottom, front, back);
}

void BoundingBox::setupArrays() {

}

void BoundingBox::setup(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) {


  shapeBox [0][0][0] = Point(left, top, front);
  shapeBox [0][0][1] = Point(left, top, back);
  shapeBox [0][1][0] = Point(left, bottom, front);
  shapeBox [0][1][1] = Point(left, bottom, back);

  shapeBox [1][0][0] = Point(right, top, front);
  shapeBox [1][0][1] = Point(right, top, back);
  shapeBox [1][1][0] = Point(right, bottom, front);
  shapeBox [1][1][1] = Point(right, bottom, back);
}


void BoundingBox::makeWorldBox(Transform &transform) {
  if (hasTransformedBox) return;

  transformedBox[0][0][0] = transform.inverseTransform(shapeBox[0][0][0]);
  transformedBox[0][0][1] = transform.inverseTransform(shapeBox[0][0][1]);
  transformedBox[0][1][0] = transform.inverseTransform(shapeBox[0][1][0]);
  transformedBox[0][1][1] = transform.inverseTransform(shapeBox[0][1][1]);

  transformedBox[1][0][0] = transform.inverseTransform(shapeBox[1][0][0]);
  transformedBox[1][0][1] = transform.inverseTransform(shapeBox[1][0][1]);
  transformedBox[1][1][0] = transform.inverseTransform(shapeBox[1][1][0]);
  transformedBox[1][1][1] = transform.inverseTransform(shapeBox[1][1][1]);


  hasTransformedBox = true;
}




BoundingBoxPlanes BoundingBox::getWorldPlanes(Transform &transform) {
  if (hasTransformedPlanes) {
    return worldSpacePlanes;
  }
  makeWorldBox(transform);


  worldSpacePlanes.left = transformedBox[0][0][0].x;
  worldSpacePlanes.right = transformedBox[0][0][0].x;
  worldSpacePlanes.top = transformedBox[0][0][0].y;
  worldSpacePlanes.bottom = transformedBox[0][0][0].y;
  worldSpacePlanes.front = transformedBox[0][0][0].z;
  worldSpacePlanes.back = transformedBox[0][0][0].z;

  worldSpacePlanes.update (transformedBox[0][0][1]);
  worldSpacePlanes.update (transformedBox[0][1][0]);
  worldSpacePlanes.update (transformedBox[0][1][1]);

  worldSpacePlanes.update (transformedBox[1][0][0]);
  worldSpacePlanes.update (transformedBox[1][1][0]);
  worldSpacePlanes.update (transformedBox[1][1][0]);
  worldSpacePlanes.update (transformedBox[1][1][1]);

  hasTransformedPlanes = true;

  return worldSpacePlanes;
}
