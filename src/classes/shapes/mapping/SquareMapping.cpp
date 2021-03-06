#include "SquareMapping.hpp"
#include "IntersectHit.hpp"
#include "Square.hpp"
SquareMapping::SquareMapping (){}

UVPair SquareMapping::getUVPair(IntersectHitPtr ir) {
  Point p = ir->getShapePoint();
  Square * square = (Square *)ir->getShape();
  //width = rect['right'] - rect['left']
  FLOAT width = square->right - square->left;
  FLOAT height = square->bottom - square->top;

  //u = (p[1] - rect['left']) / width

  UVPair uvPair;

  uvPair.u = (p.x - square->left) / width;
  uvPair.v = (p.y - square->top) / height;
  return uvPair;
}
