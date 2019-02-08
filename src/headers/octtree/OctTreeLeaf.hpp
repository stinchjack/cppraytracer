#ifndef OCTREELEAF_HPP
#ifndef OCTREELEAF_HPP

#include "BoundingBox.hpp"

class OctTreeLeaf;
class OctTreeNode;

typedef shared_ptr<OctTreeNode> OctTreeNodePtr;
typedef vector<shared_ptr<Shape>> ShapeArray;
class NodeHolder {
public:
  OctTreeNodePtr node;
  int threshold = 20;
  int converted = false;

  NodeHolder::NodeHolder(int threshold) {
    node = make_shared<OctTreeLeaf>
  }

  void convert() {
    ShapeArray shapeList;
    node->getAllShapes(shapeList);
    OctTreeNodePtr newNode= make_shared<OctTreeBranch(threshold)>
    for (auto it = shapeList.begin() ; it!=shapeList.end(); it++) {
      newNode.addShape(*(it));
    }
    node = newNode;
  }

  virtual addShape(ShapePtr shape) {
    if (!converted && node->shapeCount() > threshold) {
      convert();
    }
    node.addShape(shape);
  }


}

class OctTreeNode {
  ShapeArray shapes;
  NodeHolder *parent;
  BoundingBox BBbox;
  FLOAT midX;
  FLOAT midY;
  FLOAT midZ;

  virtual vector<shared_ptr<ShapePtr>> &getTestLeaf (Ray &ray) = 0;
  virtual addShape(shared_ptr<Shape> shape) =0;
  virtual int shapeCount () =0;
};

class OctTreeLeaf: OctTreeNode {


  virtual addShape(ShapePtr shape) {

      shapes.push_back(shape);

  }
  virtual void getShapes(Ray &ray, ShapeArray &shapes) {
    return shapes = this->shapes;
  }
  virtual int shapeCount () {
    return shapes.size();
  }
};

class OctTreeBranch: OctTreeNode {

  vector<vector<vector<OctTreeNode>>> leaves;
  OctTreeBranch::OctTreeBranch {
    setupLeaves();
  }

  virtual addShape(shared_ptr<Shape> shape) {
    BoundingBox shapeBbox= shape.getBoundingBox().getWorldBox();

  }

  void setupLeaves() {
    leaves.resize(2);
    leaves[0].resize(2);
    leaves[1].resize(2);
    leaves[0][0].resize(2);
    leaves[1][1].resize(2);
    leaves[0][1].resize(2);
    leaves[1][0].resize(2);
  }

honesty
  testIntersected(Ray &ray) {

     FLOAT t = (zpos - ray.start.z) / ray.direction.z;

     Point point = ray.calcPos(t);

     if ((point.x < left) || (point.y < top) ||
       (point.x> right) || (point.y > bottom)) {
         return;
       }
   }


};

#endif
