#ifdef EXPERIMENTAL

#define OCT_STATUS_LEAF 1
#define OCT_STATUS_BRANCH 2

class OctTreeNode {
  ShapeArray allShapes;
  NodeHolder *parent;
  BoundingBox Bbox;
  FLOAT midX;
  FLOAT midY;
  FLOAT midZ;
  int status = OCT_STATUS_LEAF;
  int splitThreshold = 15;
  vector<vector<vector<OctTreeNode>>> leaves;


  virtual addShape(ShapePtr shape) {

      allShapes.push_back(shape);

      shapeBox = shape->getBox()->getWorldBox();

      if (Bbox.left > shapeBox.left) {
        Bbox.left = shapeBox.left;
      }
      if (Bbox.right < shapeBox.right) {
        Bbox.right = shapeBox.right;
      }
      if (Bbox.top > shapeBox.top) {
        Bbox.top = shapeBox.top;
      }
      if (Bbox.bottom < shapeBox.bottom) {
        Bbox.bottom = shapeBox.bottom;
      }
      if (Bbox.front > shapeBox.front) {
        Bbox.front= shapeBox.front;
      }
      if (Bbox.back < shapeBox.back) {
        Bbox.back= shapeBox.back;
      }
  }

void sort()  {
  if (shapes.size() < splitThreshold) {
    return;
  }

  midX = (Bbox.left + Bbox.right) / 2.0;
  midY = (Bbox.top + Bbox.bottom) / 2.0;
  midZ = (Bbox.front + Bbox.back) / 2.0;

  int size= shapes.size();
  auto it = shapes.begin();
  for  (int i=0;i<size;i++) {
    addToShapeToBranach(*it);
    it++;
  }

}




  virtual void getShapes(Ray &ray, ShapeArray &shapes) {
    if (status == OCT_STATUS_LEAF) {
      return shapes = this->shapes;
    }
    else {
      // do branch
      if (ray.start.x <= box.left) {
        xTest = box.left;
      }
      else {
        xTest = box.right;
      }
      if (ray.start.y <= box.bottom) {
        yTest = box.bottom;
      }
      else {
        yTest = box.top;
      }
      if (ray.start.z <= box.front) {
        zTest = box.front;
      }
      else {
        zTest = box.back;
      }

      FLOAT t[3] = {-1, -1, -1};


      if (ray.direction.x != 0.0) {
        t[0] = (xTest - ray.start.x) / ray.direction.x;
      }
      if (ray.direction.y != 0.0) {
        t[1] = (yTest - ray.start.y) / ray.direction.y;
      }
      if (ray.direction.z != 0.0) {
        t[2] = (zTest - ray.start.z) / ray.direction.z;
      }

      Point firstPoint;
      bool hasFirstPoint=false;
      for (int i; i < 2 && !hasFirstPoint; i++) {
        if (t[i] < 0) {
          continue;
        }
        firstPoint = ray.calcPos(t[i]);
        if (firstPoint.x>=box.left && firstPoint.x<=box.right
          && firstPoint.y>=box.bottom && firstPoint.y<=box.top
          && firstPoint.z>=box.front && firstPoint.y<=box.back) {
            hasFirstPoint = true;
        }

      }

      if (!hasFirstPoint) {
        //no shapes
      }


      midX = (Bbox.left + Bbox.right) / 2.0;
      midY = (Bbox.top + Bbox.bottom) / 2.0;
      midZ = (Bbox.front + Bbox.back) / 2.0;
      if (firstPoint.x < midX) {

      }

    }
  }

  int findBrnaches (Point &p) {

    FLOAT startX;
    FLOAT startY;
    FLOAT startZ;

    if (firstPoint.x < midX-.0001) {
      startX = 0;
    }
    else {
      startX = 1;
    }

    if (firstPoint.y < midY-.0001) {
      startY = 0;
    }
    else {
      startY = 1;
    }

    if (firstPoint.x < midz-.0001) {
      startZ = 0;
    }
    else {
      startZ = 1;
    }

    if (firstPoint.x < midX-.0001) {
      endX = 0;
    }
    else {
      endX = 1;
    }

    if (firstPoint.y < midY-.0001) {
      endY = 0;
    }
    else {
      endY = 1;
    }

    if (firstPoint.x < midz-.0001) {
      endZ = 0;
    }
    else {
      endZ = 1;
    }


  }


  virtual int shapeCount () {
    return shapes.size();
  }



  void upgradeToBranch(){
    leaves.resize(2);
    leaves[0].resize(2);
    leaves[1].resize(2);
    leaves[0][0].resize(2);
    leaves[1][1].resize(2);
    leaves[0][1].resize(2);
    leaves[1][0].resize(2);
    for (int i; i<2; i++) {
      leaves[i].resize(2);
      for (int j; j<2; j++) {
        leaves[i][j].resize(2);
        for (int k; k<2; k++) {
          leaves[i][j][k]
        }
      }
    }
    status == OCT_STATUS_BRANCH;
  }


  testIntersected(Ray &ray) {

     FLOAT t = (zpos - ray.start.z) / ray.direction.z;

     Point point = ray.calcPos(t);

     if ((point.x < left) || (point.y < top) ||
       (point.x> right) || (point.y > bottom)) {
         return;
       }
   }


};
