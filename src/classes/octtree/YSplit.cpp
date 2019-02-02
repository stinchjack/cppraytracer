#include "AxisSplit.hpp"
#include <iostream>
#include <algorithm>


YSplit::YSplit (AxisSplit *parent) {
  #ifdef DEBUG
    type = "YSplit";
  #endif
  this->parent = parent;
}

void YSplit::getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start) {
  direction = ray.direction.y;
  start = ray.start.y;
}

FLOAT YSplit::getPlaneLow(BoundingBoxPlanes &planes) {
  return planes.top;
}
FLOAT YSplit::getPlaneHigh(BoundingBoxPlanes &planes) {
  return planes.bottom;
}
void YSplit::makeChildSplitters() {
  axisLowSorter = make_shared<ZSplit>(this);
  axisHighSorter = make_shared<ZSplit>(this);
}
