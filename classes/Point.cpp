Ray
View
Point
Output
  - PNG
Scene
Shape
  - Sphere
BoundingBox
Matrix
Light
AntiAlias
SubSpace
#define FLOAT float


class Point {

  private:

  public:

    FLOAT x,y,z;
    Point();
    Point (FLOAT x,y,z);
    Point (const Float&);

    Point& operator+=(const Point &rhs);
    Point operator+(const Point &rhs);

}


Point::Point() {
  x=0;
  y=0;
  z=0;
}

Point::Point(FLOAT x,y,z) {
  this->x=x;
  this->y=y;
  this->z=z;
}

Point::operator+=(const Point &rhs)
{
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Point::operator+(const Point &rhs)
{
  Point p;

  p.x = x + rhs.x;
  p.y = y + rhs.y;
  p.z = z + rhs.z;

  return p;
}
