#ifndef BOUNDINGBOX_HPP
#define BOUNDINGBOX_HPP

#include <vector>
#include "Point.hpp"

struct BoundingBoxPlanes {
  FLOAT left;
  FLOAT right;
  FLOAT top;
  FLOAT bottom;
  FLOAT front;
  FLOAT back;
}

class BoundingBox {

  vector<vector<vector<Point>>> box; //sahpe space
  vector<vector<vector<Point>>> transformedBox; //world space

  BoundingBoxPlanes transformedPlanes;
  bool hasTransformedBox = false;
  bool hasTransformedPlanes = false;


  BoundingBox::BoundingBox(BoundingBoxPlanes &bbp) {
    BoundingBox(bbp.left, bbp.right, bbp.top, bbp.bottom, bbp.front, bbp.back);
  }

  BoundingBox::BoundingBox(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) {
    setup(left, right, top, bottom, front, back);
  }

  BoundingBox::setup(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, FLOAT front, FLOAT back) {


    //setup vectors
    box.resize(2);
    box[0].resize(2);
    box[1].resize(2);
    box[0][0].resize(2);
    box[0][1].resize(2);
    box[1][0].resize(2);
    box[1][1].resize(2);

    transformedBox.resize(2);
    transformedBox[0].resize(2);
    transformedBox[1].resize(2);
    transformedBox[0][0].resize(2);
    transformedBox[0][1].resize(2);
    transformedBox[1][0].resize(2);
    transformedBox[1][1].resize(2);


    box [0][0][0] = Point(left, top, front);
    box [0][0][1] = Point(left, top, back);
    box [0][1][0] = Point(left, bottom, front);
    box [0][1][1] = Point(left, bottom, back);
    box [0][0][0] = Point(right, top, front);
    box [0][0][1] = Point(right, top, back);
    box [0][1][0] = Point(right, bottom, front);
    box [0][1][1] = Point(right, bottom, back);
  }

  void makeWorldBox(Transform &transform) {
    if (hasTransformedBox) return;
    for (int i =0; i<2; i++){
      for (int j =0; j<2; j++){
        for (int k =0; k<2; k++){
          transformedBox[i][j][k] = transform.inverseTransform(box[i][j][k]);
        }
      }
    }
    hasTransformedBox = true;
  }

  BoundingBoxPlanes getWorldPlanes(Transform &transform) {
    if (hasTransformedPlanes) {
      return transformedPlanes;
    }
    makeWorldBox(transform);

    BoundingBoxPlanes bbp;
    bbp.left = box[0][0][0].x;
    bbp.right = box[0][0][0].x;
    bbp.top = box[0][0][0].y;
    bbp.bottom = box[0][0][0].y;
    bbp.front = box[0][0][0].z;
    bbp.back = box[0][0][0].z;

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
    transformedPlanes = bbp;
    return transformedPlanes;
  }


};



#endif
