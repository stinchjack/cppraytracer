#ifndef OCTTREEV2_HPP
#define OCTTREEV2_HPP

typdef vector <ShapePtr> ShapeVector;

class OctTree {
  ShapeVector allShapes;
  ShapeVector unsortableShapes;
  ShapeVector sortedShapes[2][2][2];
  OctTree *parent = nullptr;
  bool sorted = false;
  int sortThreshold=10;

  void sort() {

    if (sorted || allShapes.size() < sortThreshold) {
      return;
    }

    // safety catch to prevent infinite tree depth
    if (parent && allShapes.size() >= parent->allShapes.size()) {
      return;
    }

    for (auto it=allShapes.begin(); it!=allShapes.end(); it++) {

      BoundingBoxPlanes shapePlanes = shape->getWorldBoundingPlanes();
      FLOAT midX = (planes.right + planes.left) / 2.0;
      FLOAT midY = (planes.top + planes.right) / 2.0;
      FLOAT midZ = (planes.back + planes.front) / 2.0;

      bool lowX = shapePlanes.left < (midX +.001);
      bool highX = shapePlanes.right > (midX -.001);
      bool lowY = shapePlanes.top < (midY +.001);
      bool highY = shapePlanes.bottom > (midY -.001);
      bool lowZ = shapePlanes.front < (midZ +.001);
      bool highZ = shapePlanes.back > (midZ -.001);


      // if goes in all 8 brnaches
      if (lowX && lowY && lowZ && highX && highY && highZ) {
        unsortableShapes.push_back(shape);
        return;
      }

      if (lowX && lowY && lowZ) {
        sortedShapes[0][0][0].push_back(shape);
      }
      if (lowX && lowY && highZ) {
        sortedShapes[0][0][1].push_back(shape);
      }
      if (lowX && highY && lowZ) {
       sortedShapes[0][1][0].push_back(shape);
      }
      if (lowX && highY && highZ) {
        sortedShapes[0][1][1].push_back(shape);
      }
      if (highX && lowY && lowZ) {
        sortedShapes[1][0][0].push_back(shape);
      }
      if (highX && lowY && highZ) {
        sortedShapes[1][0][1].push_back(shape);
      }
      if (highX && highY && lowZ) {
        sortedShapes[1][1][0].push_back(shape);
      }
      if (highX && highY && highZ) {
        sortedShapes[1][1][1].push_back(shape);
      }

    }
  }


  void testIntersect(QueueItemResults &results, ray &ray) {
    if (!sorted) {
      testIntersectLoop(allShapes, results, ray);
      return;
    }

    FLOAT midX = (planes.right + planes.left) / 2.0;
    FLOAT midY = (planes.top + planes.right) / 2.0;
    FLOAT midZ = (planes.back + planes.front) / 2.0;

    bool lowX = ray.start.x <(midX + .001) || ray.direction.x < 0;
    bool highX = ray.start.x > (midX -.001) || ray.direction.x > 0;
    bool lowY = ray.start.y <(midY + .001) || ray.direction.y < 0;
    bool highY = ray.start.y > (midY -.001) || ray.direction.y > 0;
    bool lowZ = ray.start.z <(midZ + .001) || ray.direction.z < 0;
    bool highZ = ray.start.z > (midZ -.001) || ray.direction.z > 0;



    if (lowX && lowY && lowZ) {
      testIntersectLoop(sortedShapes[0][0][0]);
    }
    if (lowX && lowY && highZ) {
      testIntersectLoop(sortedShapes[0][0][1]);
    }
    if (lowX && highY && lowZ) {
      testIntersectLoop(sortedShapes[0][1][0]);
    }
    if (lowX && highY && highZ) {
      testIntersectLoop(sortedShapes[0][1][1]);
    }
    if (highX && lowY && lowZ) {
      testIntersectLoop(sortedShapes[1][0][0]);
    }
    if (highX && lowY && highZ) {
      testIntersectLoop(sortedShapes[1][0][1]);
    }
    if (highX && highY && lowZ) {
      testIntersectLoop(sortedShapes[1][1][0]);
    }
    if (highX && highY && highZ) {
      testIntersectLoop(sortedShapes[1][1][1]);
    }



  }

};

#endif
