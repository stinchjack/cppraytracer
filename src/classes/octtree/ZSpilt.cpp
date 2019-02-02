#include "AxisSplit.hpp"
#include <iostream>
#include <algorithm>




  ZSplit::ZSplit (AxisSplit *parent) {
    #ifdef DEBUG
      type = "ZSplit";
    #endif
    this->parent = parent;
  }

  void ZSplit::getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start) {
    direction = ray.direction.z;
    start = ray.start.z;
  }

  FLOAT ZSplit::getPlaneLow(BoundingBoxPlanes &planes) {
    return planes.front;
  }
  FLOAT ZSplit::getPlaneHigh(BoundingBoxPlanes &planes) {
    return planes.back;
  }
  void ZSplit::makeChildSplitters() {
    axisLowSorter = make_shared<XSplit>(this);
    axisHighSorter = make_shared<XSplit>(this);

  }
