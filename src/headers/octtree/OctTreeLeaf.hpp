#ifndef OCTREELEAF_HPP
#ifndef OCTREELEAF_HPP

class OctTreeLeaf;
class OctTreeNode;

typedef OctTreeNode* OctTreeNodePtr;

class OctTreeNode {
  virtual OctTreeLeaf &getTestLeaf (Ray &ray) = 0;
  virtual addShape(shared_ptr<Shape> shape) =0;
};

class OctTreeLeaf: OctTreeNode {
  vector<shared_ptr<Shape>> shapes;

  virtual addShape(shared_ptr<Shape> shape) {
    shapes.push_back(shape);
  }
  virtual vector<shared_ptr<Shape>> &getShapes(Ray & ray) {
    return shapes;
  }
};

class OctTreeBranch: OctTreeNode {
  vector<shared_ptr<Shape>> shapes; // for shapes that cant be split;

  vector<vector<vector<OctTreeNodePtr>>> leaves;
  OctTreeBranch::OctTreeBranch {
    setupLeaves();
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

};

#endif
