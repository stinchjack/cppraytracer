#include "Transform.hpp"
#include <cmath>

Transform::Transform() {};

void Transform::setRotate(const Vector &rotateAxis, FLOAT rotateAngle) {
  this->rotateAngle = rotateAngle;
  this->rotateAxis = rotateAxis;
  doRotate = true;
  this->rotationMatrix();
}


void Transform::setScale(FLOAT scaleX, FLOAT scaleY, FLOAT scaleZ ) {
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  this->scaleZ = scaleZ;
  doScale = true;
}

void Transform::setShift (const Point &p) {
  doShift = true;
  shift = p;
}

Point Transform::transform(const Point &p) const {

  /*if (!doShift && !doScale && !doRotate) {
    return p;
  }*/

  Point newPoint (p.x, p.y, p.z);

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


Point Transform::inverseTransform(const Point &p) const {


  Point newPoint (p.x, p.y, p.z);

  if (doShift) {
    newPoint += shift;
  }

  if (doScale && !doRotate) {

    newPoint.x *= scaleX;
    newPoint.y *= scaleY;
    newPoint.z *= scaleZ;

  }

  if (doRotate) {
    // if rotation or rotation + scale

    FLOAT new_x = (mtxInv[0][0] * newPoint.x) + (mtxInv[0][1] * newPoint.y) + (mtxInv[0][2] * newPoint.z);
    FLOAT new_y = (mtxInv[1][0] * newPoint.x) + (mtxInv[1][1] * newPoint.y) + (mtxInv[1][2] * newPoint.z);
    FLOAT new_z = (mtxInv[2][0] * newPoint.x) + (mtxInv[2][1] * newPoint.y) + (mtxInv[2][2] * newPoint.z);

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

Vector Transform::inverseTransform(Vector &v) {

  if (!doScale && !doRotate) {
    return Vector(v);
  }
  if (doScale && !doRotate) {
    return Vector (v.x * scaleX, v.y * scaleY, v.z * scaleZ);
  }

  // if rotation or rotation + scale

  FLOAT new_vector_x = (mtxInv[0][0] * v.x) + (mtxInv[0][1] * v.y) + (mtxInv[0][2] * v.z);
  FLOAT new_vector_y = (mtxInv[1][0] * v.x) + (mtxInv[1][1] * v.y) + (mtxInv[1][2] * v.z);
  FLOAT new_vector_z = (mtxInv[2][0] * v.x) + (mtxInv[2][1] * v.y) + (mtxInv[2][2] * v.z);

  return Vector(new_vector_x, new_vector_y, new_vector_z);
}

//    """A matrix for rotation about an arbitrary axis./
//      See http://math.kennesaw.edu/~plaval/math4490/rotgen.pdf"""

void Transform::rotationMatrix() {
    //def __init__(self, vector, angle):
      /*  """Class constructor for RotationMatrix.
        :param vector: a cartesian vector as an axis.
        :param angle: the amount of rotation about the axis,
                      in degrees"""*/

        Vector &vector = rotateAxis;

        FLOAT rad = (rotateAngle  * M_PI ) / 180.0;
        //rad = radians(angle)
        //one = mpfr(1)
        //zero = mpfr(0)
        FLOAT t = 1.0 - cos(rad);
        FLOAT S = sin(rad);
        FLOAT C = cos(rad);
        FLOAT u2x = vector.x * vector.x;
        FLOAT u2y = vector.y * vector.y;
        FLOAT u2z = vector.z * vector.z;
        FLOAT ux = vector.x;
        FLOAT uy = vector.y;
        FLOAT uz = vector.z;



        FLOAT  c1 = (t * u2x) + C ;
        FLOAT c2 = (t * ux * uy) - (S * uz);
        FLOAT c3 = (t * ux * uz) + (S * uy);

        FLOAT c4 = (t * ux * uy) + (S * uz);
        FLOAT c5 = (t * u2y) + C;
        FLOAT c6 = (t * uy * uz) - (S * ux);

        FLOAT c7 = (t * ux * uz) - (S * uy);
        FLOAT c8 = (t * uy * uz) + (S * ux);
        FLOAT c9 = (t * u2z) + C;

        mtxFwd[0][0] = c1 / scaleX;
        mtxFwd[1][0] = c2 / scaleY;
        mtxFwd[2][0] = c3 / scaleZ;

        mtxFwd[0][1] = c4 / scaleX;
        mtxFwd[1][1] = c5 / scaleY;
        mtxFwd[2][1] = c6 / scaleZ;

        mtxFwd[0][2] = c7 / scaleX;
        mtxFwd[1][2] = c8 / scaleY;
        mtxFwd[2][2] = c9 / scaleZ;


        rad = 0.0 - rad;

         t = 1.0 - cos(rad);
         S = sin(rad);
         C = cos(rad);


        c1 = (t * u2x) + C ;
         c2 = (t * ux * uy) - (S * uz);
         c3 = (t * ux * uz) + (S * uy);

         c4 = (t * ux * uy) + (S * uz);
         c5 = (t * u2y) + C;
         c6 = (t * uy * uz) - (S * ux);

         c7 = (t * ux * uz) - (S * uy);
         c8 = (t * uy * uz) + (S * ux);
         c9 = (t * u2z) + C;



         mtxInv[0][0] = c1 * scaleX;
         mtxInv[1][0] = c2 * scaleY;
         mtxInv[2][0] = c3 * scaleZ;

         mtxInv[0][1] = c4 * scaleX;
         mtxInv[1][1] = c5 * scaleY;
         mtxInv[2][1] = c6 * scaleZ;

         mtxInv[0][2] = c7 * scaleX;
         mtxInv[1][2] = c8 * scaleY;
         mtxInv[2][2] = c9 * scaleZ;
}
