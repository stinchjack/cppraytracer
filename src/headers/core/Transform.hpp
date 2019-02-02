#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Point.hpp"
#include "Vector.hpp"




class Transform {
private:
  FLOAT mtxFwd[3][3] = { {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

  FLOAT mtxInv[3][3]= {{1, 0, 0},  {0, 1, 0},  {0, 0, 1}};


  bool doShift = false;
  bool doScale = false;
  bool doRotate = false;

  Point shift = Point(0,0,0);
  FLOAT scaleX = 1, scaleY = 1, scaleZ = 1;
  FLOAT rotateAngle;
  Vector rotateAxis;
  void rotationMatrix();

public:
  inline Transform(){};
  void setShift(const Point &p);
  void setScale(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ );
  void setRotate(const Vector &axis, FLOAT angle);

  inline Vector transform (Vector &v);

  Vector inverseTransform (Vector &v);

  // the two methods below transform in-place
  Point inverseTransform (const Point &p) const;
  inline Point transform (const Point &p) const;
  inline bool doesRotate();

};

bool Transform::doesRotate() {
  return doRotate;
}
Point Transform::transform(const Point &p) const {

  /*if (!doShift && !doScale && !doRotate) {
    return p;
  }*/

  Point newPoint (p);

  if (doShift) {
    newPoint -= shift;
  }

  if (doScale && !doRotate) {

    newPoint.x /= scaleX;
    newPoint.y /= scaleY;
    newPoint.z /= scaleZ;

  }

  if (doRotate) {

    // if rotation or rotation + scale

    FLOAT new_x = (mtxFwd[0][0] * newPoint.x) + (mtxFwd[0][1] * newPoint.y) + (mtxFwd[0][2] * newPoint.z);
    FLOAT new_y = (mtxFwd[1][0] * newPoint.x) + (mtxFwd[1][1] * newPoint.y) + (mtxFwd[1][2] * newPoint.z);
    FLOAT new_z = (mtxFwd[2][0] * newPoint.x) + (mtxFwd[2][1] * newPoint.y) + (mtxFwd[2][2] * newPoint.z);

    newPoint.x = new_x;
    newPoint.y = new_y;
    newPoint.z = new_z;

  }

  return newPoint;
}

Vector Transform::transform(Vector &v) {

  if (!doScale && !doRotate) {
    return Vector(v);
  }
  if (doScale && !doRotate) {
    return Vector (v.x / scaleX, v.y / scaleY, v.z / scaleZ);
  }

  // if rotation or rotation + scale


  // 1x3 by 3x1 matrix multiplcation
  FLOAT new_vector_x = (mtxFwd[0][0] * v.x) + (mtxFwd[0][1] * v.y) + (mtxFwd[0][2] * v.z);
  FLOAT new_vector_y = (mtxFwd[1][0] * v.x) + (mtxFwd[1][1] * v.y) + (mtxFwd[1][2] * v.z);
  FLOAT new_vector_z = (mtxFwd[2][0] * v.x) + (mtxFwd[2][1] * v.y) + (mtxFwd[2][2] * v.z);



  return Vector(new_vector_x, new_vector_y, new_vector_z);
}


#endif
