#include "AxisSplit.hpp"
#include <iostream>
#include <algorithm>




  #ifdef DEBUG
    int AxisSplit::depth() {
      int i =0;
      AxisSplit *up = parent;
      while (up) {
          up = up->parent;
          i++;
      }
      return i;
    }
  #endif

void AxisSplit::addShapes(vector<ShapePtr> shapes) {
  auto end = shapes.end();
  for (auto it = shapes.begin();it != end; it++) {
    this->addShape(*it);
  }

}



void AxisSplit::addShape(ShapePtr shape) {

  allShapes.push_back(shape);
  BoundingBoxPlanes shapePlanes = shape->getWorldBoundingPlanes();
  if (allShapes.size() == 1) {
    axisLow = getPlaneLow(shapePlanes);
    axisHigh = getPlaneHigh(shapePlanes);
  }
  else {
    if (axisLow>getPlaneLow(shapePlanes)) {
      axisLow = getPlaneLow(shapePlanes);
    }
    if (axisHigh< getPlaneHigh(shapePlanes)) {
      axisHigh = getPlaneHigh(shapePlanes);
    }
  }
  sorted = false;
}

void AxisSplit::sort() {
  /*if (sorting) {
    return;
  }*/
  if (sorted || allShapes.size() < splitThreshold) {
    return;
  }

  //dont plsit if below the threshold count
  if (allShapes.size() < splitThreshold) {
    return;
  }

  // safety catch to prevent infinite splits
  if (parent && allShapes.size() >= parent->allShapes.size()) {
    return;
  }
  //sorting=true;
  makeChildSplitters();
  //axisLowShapes.resize(0);
  //axisHighShapes.resize(0);
  FLOAT mid = (axisLow + axisHigh) / 2.0;

  for (auto it=allShapes.begin(); it!=allShapes.end(); it++) {
    ShapePtr shape = *it;
    BoundingBoxPlanes shapePlanes = shape->getWorldBoundingPlanes();
    bool addLow=false, addHigh=false;
    if (getPlaneLow(shapePlanes) < (mid + .001))  {

      addLow = true;
    }
    if (getPlaneHigh(shapePlanes) > (mid - .001))  {

      addHigh = true;
    }

    if (addLow && !addHigh) {
      axisLowSorter->addShape(shape);
    }
    if (!addLow && addHigh) {
      axisHighSorter->addShape(shape);
    }

    if (addLow && addHigh) {
      unsortableShapes.push_back(shape);
    }

  }
  sorted=true;

}

void AxisSplit::testIntersectLoop(vector<ShapePtr> shapes, QueueItemResults &results, Ray& ray) {
    auto end= shapes.end();
    for (auto it = shapes.begin(); it != end; it++) {
      (*it)->testIntersect(results, ray);
    }
}

void AxisSplit::testIntersect(QueueItemResults &results, Ray& ray) {

  if (!sorted) {
    testIntersectLoop(allShapes, results, ray);
    return;
  }
  FLOAT start, direction;
  getRayInfo(ray, direction, start);
  testIntersectLoop(unsortableShapes, results, ray);


  bool startLow = start <(mid + .001);
  bool startHigh = start >(mid -.001);
  bool lowDone = false, highDone = false;

  if (startLow && !lowDone) {
      axisLowSorter->testIntersect(results, ray);
      lowDone = true;
      if (results.size()==0 && !highDone) {
        axisHighSorter->testIntersect(results, ray);
        highDone = true;
      }
  }

  if (startHigh && !highDone) {
      axisLowSorter->testIntersect(results, ray);
      highDone = true;
      if (results.size()==0 && !lowDone) {
        axisLowSorter->testIntersect(results, ray);
        highDone = true;
      }
  }

}

void AxisSplit::getShapes (vector<ShapePtr> &shapeArray, Ray &ray) {
  #ifdef DEBUG
    cout << "getShapes depth:" << depth() << endl;
  #endif

  if (!sorted) {
    shapeArray.insert(shapeArray.end(), allShapes.begin(), allShapes.end());
    return;
  }

  FLOAT start, direction;
  getRayInfo(ray, direction, start);
  //if (ray.start.z < mid || ray.direction.z<0)
  if ((start <(mid + .001)) || direction<0) {
      axisLowSorter->getShapes(shapeArray, ray);
      //auto b= shapeArray.end();
      //shapeArray.insert(b,  axisLowShapes.begin(), axisLowShapes.end());
  }
    //if (ray.start.z > mid || ray.direction.z>0)
  if (start >(mid -.001) || direction>0) {
      axisHighSorter->getShapes(shapeArray, ray);
    //auto b= shapeArray.end();
    //shapeArray.insert(b,  axisHighShapes.begin(), axisHighShapes.end());
  }
  shapeArray.insert(shapeArray.end(), unsortableShapes.begin(), unsortableShapes.end());


}
