#include <math.h>

class Vector : public Point {

  private:

    FLOAT length;
    Vector normalised;
    int hasLength = 0;
    int hasNormalised = 0;
  public:

    Point operator*(const Point &rhs); // dot product
    FLOAT cross (const Point &rhs);
    FLOAT length();
    Vector& normalised();
}

FLOAT Vector::length() {
  if (hasLength) {
    return hasLength;
  }
  length = sqrt ((x * x) + (y * y) + (z * z));
  return length;
}

Vector& Vector::&normalised() {

  if (hasNormalised) {
    return normalised;
  }

  return Vector (x /  length, y / length, z/ length);


}
