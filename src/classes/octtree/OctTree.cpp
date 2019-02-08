#include "OctTreeV2.hpp"

  void OctTree::makeChildren() {

    sortedShapes[0][0][0] = make_shared<OctTree>();
    sortedShapes[0][0][0]->parent = this;

    sortedShapes[0][0][1] = make_shared<OctTree>();
    sortedShapes[0][0][1]->parent = this;

    sortedShapes[0][1][0] = make_shared<OctTree>();
    sortedShapes[0][1][0]->parent = this;

    sortedShapes[0][1][1] = make_shared<OctTree>();
    sortedShapes[0][1][1]->parent = this;

    sortedShapes[1][0][0] = make_shared<OctTree>();
    sortedShapes[1][0][0]->parent = this;

    sortedShapes[1][0][1] = make_shared<OctTree>();
    sortedShapes[1][0][1]->parent = this;

    sortedShapes[1][1][0] = make_shared<OctTree>();
    sortedShapes[1][1][0]->parent = this;

    sortedShapes[1][1][1] = make_shared<OctTree>();
    sortedShapes[1][1][1]->parent = this;

  }

  void OctTree::addShapes(vector<ShapePtr> shapes) {
    auto end = shapes.end();
    for (auto it = shapes.begin();it != end; it++) {
      this->addShape(*it);
    }

  }


  void OctTree::addShape(ShapePtr shape) {

    

    allShapes.push_back(shape);

    BoundingBoxPlanes shapePlanes = shape->getWorldBoundingPlanes();
    if (allShapes.size() == 1) {
      worldPlanes = shapePlanes;
    }
    else {
      if (worldPlanes.left > shapePlanes.left) {
        worldPlanes.left = shapePlanes.left;
      }
      if (worldPlanes.right < shapePlanes.right) {
        worldPlanes.right = shapePlanes.right;
      }
      if (worldPlanes.front > shapePlanes.front) {
        worldPlanes.front = shapePlanes.front;
      }
      if (worldPlanes.back < shapePlanes.back) {
        worldPlanes.back = shapePlanes.back;
      }
      if (worldPlanes.top > shapePlanes.top) {
        worldPlanes.top = shapePlanes.top;
      }
      if (worldPlanes.bottom < shapePlanes.bottom) {
        worldPlanes.bottom = shapePlanes.bottom;
      }
    }
    sorted = false;
  }

  void OctTree::sort() {
    #ifdef DEBUG
      //printDepth();
    #endif

    if (sorted || (int)allShapes.size() < sortThreshold) {
      return;
    }

    // safety catch to prevent infinite tree depth
    if (parent && allShapes.size() >= parent->allShapes.size()) {
      return;
    }

    makeChildren();


    midX = (worldPlanes.right + worldPlanes.left) / 2.0;
    midY = (worldPlanes.top + worldPlanes.bottom) / 2.0;
    midZ = (worldPlanes.back + worldPlanes.front) / 2.0;

    for (auto it=allShapes.begin(); it!=allShapes.end(); it++) {
      ShapePtr shape = *it;
      BoundingBoxPlanes shapePlanes = shape->getWorldBoundingPlanes();

      bool lowX = shapePlanes.left < (midX +.001);
      bool highX = shapePlanes.right > (midX -.001);
      bool lowY = shapePlanes.top < (midY +.001);
      bool highY = shapePlanes.bottom > (midY -.001);
      bool lowZ = shapePlanes.front < (midZ +.001);
      bool highZ = shapePlanes.back > (midZ -.001);

      if ((lowX + highX) > 1 ||
          (lowY + highY) > 1 ||
          (lowZ + highZ) > 1) {
        unsortableShapes.push_back(shape);

      }
      else {

          int x = (lowX?0:1);
          int y = (lowY?0:1);
          int z = (lowZ?0:1);

          sortedShapes[x][y][z]->addShape(shape);
      }
    }
    sorted = true;

      sortedShapes[0][0][0]->sort();
      sortedShapes[0][0][1]->sort();
      sortedShapes[0][1][0]->sort();
      sortedShapes[0][1][1]->sort();

      sortedShapes[1][0][0]->sort();
      sortedShapes[1][0][1]->sort();
      sortedShapes[1][1][0]->sort();
      sortedShapes[1][1][1]->sort();

  }

  void OctTree::testIntersect(QueueItemResults &results, Ray &ray) {



    if (!sorted) {
      testIntersectLoop(allShapes, results, ray);
      return;
    }


    bool lowX = ray.start.x <(midX + .0001) || ray.direction.x < 0;
    bool highX = ray.start.x > (midX -.0001) || ray.direction.x > 0;
    bool lowY = ray.start.y <(midY + .0001) || ray.direction.y < 0;
    bool highY = ray.start.y > (midY -.0001) || ray.direction.y > 0;
    bool lowZ = ray.start.z <(midZ + .0001) || ray.direction.z < 0;
    bool highZ = ray.start.z > (midZ -.0001) || ray.direction.z > 0;


    testIntersectLoop(unsortableShapes, results, ray);

    if (lowX && lowY && lowZ) {
      sortedShapes[0][0][0]->testIntersect(results, ray);
    }
    if (lowX && lowY && highZ) {
      sortedShapes[0][0][1]->testIntersect(results, ray);
    }
    if (lowX && highY && lowZ) {
      sortedShapes[0][1][0]->testIntersect(results, ray);
    }
    if (lowX && highY && highZ) {
      sortedShapes[0][1][1]->testIntersect(results, ray);
    }
    if (highX && lowY && lowZ) {
      sortedShapes[1][0][0]->testIntersect(results, ray);
    }
    if (highX && lowY && highZ) {
      sortedShapes[1][0][1]->testIntersect(results, ray);
    }
    if (highX && highY && lowZ) {
      sortedShapes[1][1][0]->testIntersect(results, ray);
    }
    if (highX && highY && highZ) {
      sortedShapes[1][1][1]->testIntersect(results, ray);
    }


  }


  void OctTree::testIntersectLoop(vector<ShapePtr> shapes, QueueItemResults &results, Ray& ray) {
      auto end= shapes.end();
      for (auto it = shapes.begin(); it != end; it++) {
        (*it)->testIntersect(results, ray);
      }
  }
