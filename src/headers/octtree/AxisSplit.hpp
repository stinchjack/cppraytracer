
#ifndef ZSPLIT_HPP
#define ZSPLIT_HPP
#include <set>
#include <vector>
#include "Shape.hpp"
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

class AxisSplit {

protected:

  unsigned int splitThreshold = 5;
  bool sorted = false;
  bool sorting = false;
  FLOAT mid;
  FLOAT axisLow, axisHigh;
  vector<ShapePtr>  allShapes, unsortableShapes;

#ifdef DEBUG
  string type = "AxisSplit";
#endif

  AxisSplit *parent = nullptr;
  shared_ptr<AxisSplit> axisLowSorter= nullptr;
  shared_ptr<AxisSplit> axisHighSorter= nullptr;


public:
  virtual void addShape(ShapePtr shape);
  void addShapes(vector<ShapePtr> shapes);
  void testIntersectLoop(vector<ShapePtr> shapes, QueueItemResults &result, Ray& ray);
  void testIntersect(QueueItemResults &results, Ray& ray);
  void sort();

  void getShapes (vector<ShapePtr> &shapeArray, Ray &ray);

  virtual void getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start)=0;

  virtual FLOAT getPlaneLow(BoundingBoxPlanes &planes) =0 ;
  virtual FLOAT getPlaneHigh(BoundingBoxPlanes &planes) =0 ;
  virtual void makeChildSplitters() =0;

  #ifdef DEBUG
    int depth();
  #endif
};

class XSplit:public AxisSplit {

public:
  XSplit(AxisSplit *parent);
  virtual FLOAT getPlaneLow(BoundingBoxPlanes &planes);
  virtual FLOAT getPlaneHigh(BoundingBoxPlanes &planes);
  virtual void getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start);
  virtual void makeChildSplitters();
};

class YSplit:public AxisSplit {

public:
  YSplit(AxisSplit *parent);
  virtual FLOAT getPlaneLow(BoundingBoxPlanes &planes);
  virtual FLOAT getPlaneHigh(BoundingBoxPlanes &planes);
  virtual void getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start);
  virtual void makeChildSplitters();
};

class ZSplit:public AxisSplit {

public:
  ZSplit(AxisSplit *parent);
  virtual FLOAT getPlaneLow(BoundingBoxPlanes &planes);
  virtual FLOAT getPlaneHigh(BoundingBoxPlanes &planes);
  virtual void getRayInfo(Ray &ray, FLOAT &direction, FLOAT &start);
  virtual void makeChildSplitters();
};


#endif
