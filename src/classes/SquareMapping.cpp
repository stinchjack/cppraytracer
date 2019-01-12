#include "SquareMapping.hpp";

UVPair SquareMapping::getUVPair(IntersectHit &ir) {
  Point p = ir.getShapePoint();
  shared_ptr<Square>  square = (shared_ptr<Square>)ir.getShape();
  //width = rect['right'] - rect['left']
  FLOAT width = sqaure->right - sqaure->left;
  FLOAT height = sqaure->top - sqaure->bottom;

  //u = (p[1] - rect['left']) / width

  UVPair uvPair;

  uvPair.u = (p.x - sqaure->left) / width;
  uvPair.v = (p.y - sqaure->top) / height;
  return (u, v)
}
