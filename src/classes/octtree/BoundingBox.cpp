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
  //setup vectors
  shapeBox.resize(2);
  shapeBox[0].resize(2);
  shapeBox[1].resize(2);
  shapeBox[0][0].resize(2);
  shapeBox[0][1].resize(2);
  shapeBox[1][0].resize(2);
  shapeBox[1][1].resize(2);

  transformedBox.resize(2);
  transformedBox[0].resize(2);
  transformedBox[1].resize(2);
  transformedBox[0][0].resize(2);
  transformedBox[0][1].resize(2);
  transformedBox[1][0].resize(2);
  transformedBox[1][1].resize(2);
}

void BoundingBox::setup(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) {


  setupArrays();


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
  for (int i =0; i<2; i++){
    for (int j =0; j<2; j++){
      for (int k =0; k<2; k++){
        transformedBox[i][j][k] = transform.inverseTransform(shapeBox[i][j][k]);
      }
    }
  }
  hasTransformedBox = true;
}




BoundingBoxPlanes BoundingBox::getWorldPlanes(Transform &transform) {
  if (hasTransformedPlanes) {
    return worldSpacePlanes;
  }
  makeWorldBox(transform);

  BoundingBoxPlanes bbp;
  bbp.left = shapeBox[0][0][0].x;
  bbp.right = shapeBox[0][0][0].x;
  bbp.top = shapeBox[0][0][0].y;
  bbp.bottom = shapeBox[0][0][0].y;
  bbp.front = shapeBox[0][0][0].z;
  bbp.back = shapeBox[0][0][0].z;

  for (int i =0; i<2; i++){
    for (int j =0; j<2; j++){
      for (int k =0; k<2; k++){
        if (bbp.left > transformedBox[i][j][k].x) {
          bbp.left = transformedBox[i][j][k].x;
        }
        if (bbp.right < transformedBox[i][j][k].x) {
          bbp.right = transformedBox[i][j][k].x;
        }

        if (bbp.top > transformedBox[i][j][k].y) {
          bbp.top = transformedBox[i][j][k].y;
        }
        if (bbp.bottom < transformedBox[i][j][k].y) {
          bbp.bottom = transformedBox[i][j][k].y;
        }

        if (bbp.front > transformedBox[i][j][k].z) {
          bbp.front = transformedBox[i][j][k].z;
        }
        if (bbp.back < transformedBox[i][j][k].z) {
          bbp.back = transformedBox[i][j][k].z;
        }
      }
    }
  }
  worldSpacePlanes = bbp;
  return worldSpacePlanes;
}
