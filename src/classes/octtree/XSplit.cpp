#include "AxisSplit.hpp"
#include <iostream>
#include <algorithm>

  XSplit::XSplit (AxisSplit *parent) {
    #ifdef DEBUG
      type = "XSplit";
    #endif
    this->parent = parent;
  }

  void XSplit::getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start) {
    direction = ray.direction.x;
    start = ray.start.x;
  }

  FLOAT XSplit::getPlaneLow(BoundingBoxPlanes &planes) {
    return planes.left;
  }
  FLOAT XSplit::getPlaneHigh(BoundingBoxPlanes &planes) {
    return planes.right;
  }

  void XSplit::makeChildSplitters() {
    axisLowSorter = make_shared<YSplit>(this);
    axisHighSorter = make_shared<YSplit>(this);
  }
