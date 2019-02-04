#ifndef OCTTREE_HPP
#define OCTTREE_HPP

#include "Shape.hpp"
#include <memory>
#include <vector>

class OctTree;
typedef vector <ShapePtr> ShapeVector;
typedef shared_ptr<OctTree> OctTreePtr;

class OctTree {
private:
  ShapeVector allShapes;
  ShapeVector unsortableShapes;
  shared_ptr<OctTree> sortedShapes[2][2][2];
  //vector<vector<vector<OctTreePtr>>>  sortedShapes { };
  FLOAT midX, midY, midZ;

  OctTree *parent = nullptr;
  bool sorted = false;

  BoundingBoxPlanes worldPlanes;

public:
  int sortThreshold=10;

  inline OctTree(){};

  void makeChildren() ;


  void addShape(ShapePtr shape);

  void sort();

  void testIntersectLoop(vector<ShapePtr> shapes, QueueItemResults &results, Ray& ray);
  void testIntersect(QueueItemResults &results, Ray &ray);
};

#endif
