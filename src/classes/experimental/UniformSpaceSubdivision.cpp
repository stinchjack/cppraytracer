#ifdef EXPERIMENTAL
#include "UniformSpaceSubdivision.hpp"

UniformSpaceSubdivider::UniformSpaceSubdivider(int voxelSideLength) {
  this->voxelSideLength = voxelSideLength;
}

void UniformSpaceSubdivider::addShapes(ShapeArray shapes) {
  auto end = shapes.end();
  for (auto it = shapes.begin();it != end; it++) {
    addShape(*it);
  }
}

void UniformSpaceSubdivider::addShapes(map<std::string, ShapePtr> shapes) {
  auto end = shapes.end();
  for (auto it = shapes.begin();it != end; it++) {
    addShape(it->second);
  }
}

void UniformSpaceSubdivider::addShape(ShapePtr shape) {

    //allShapes.push_back(shape);
    allShapes.insert(shape);
    BoundingBoxPlanes shapeBoundingPlanes = shape->getWorldBoundingPlanes();


    //initial bPlanes with first shape;
    if (allShapes.size() == 1) {
      bPlanes.left = shapeBoundingPlanes.left;
      bPlanes.right = shapeBoundingPlanes.right;
      bPlanes.top = shapeBoundingPlanes.top;
      bPlanes.bottom = shapeBoundingPlanes.bottom;
      bPlanes.front= shapeBoundingPlanes.front;
      bPlanes.back= shapeBoundingPlanes.back;
    }

    else {

      if (bPlanes.left > shapeBoundingPlanes.left) {
        bPlanes.left = shapeBoundingPlanes.left;
      }
      if (bPlanes.right < shapeBoundingPlanes.right) {
        bPlanes.right = shapeBoundingPlanes.right;
      }
      if (bPlanes.top > shapeBoundingPlanes.top) {
        bPlanes.top = shapeBoundingPlanes.top;
      }
      if (bPlanes.bottom < shapeBoundingPlanes.bottom) {
        bPlanes.bottom = shapeBoundingPlanes.bottom;
      }
      if (bPlanes.front > shapeBoundingPlanes.front) {
        bPlanes.front= shapeBoundingPlanes.front;
      }
      if (bPlanes.back < shapeBoundingPlanes.back) {
        bPlanes.back= shapeBoundingPlanes.back;
      }
    }
}



void UniformSpaceSubdivider::sort(ViewPtr view) {

  Point eye = view->getEye();


  // make sure the divided space includes the eye point
  if (bPlanes.left>eye.x)  {
    bPlanes.left = eye.x;
  }
  if (bPlanes.right<eye.x)  {
    bPlanes.right = eye.x;
  }
  if (bPlanes.bottom<eye.y)  {
    bPlanes.bottom = eye.y;
  }
  if (bPlanes.top>eye.y)  {
    bPlanes.top = eye.y;
  }
  if (bPlanes.front>eye.z)  {
    bPlanes.front = eye.z;
  }
  if (bPlanes.back<eye.z)  {
    bPlanes.back = eye.z;
  }

  //calculate size of space
  xSize = bPlanes.right - bPlanes.left;
  ySize = bPlanes.bottom - bPlanes.top;
  zSize = bPlanes.back - bPlanes.front;

  xVoxles = xSize / (FLOAT)voxelSideLength;
  yVoxles = ySize / (FLOAT)voxelSideLength;
  zVoxles = zSize / (FLOAT)voxelSideLength;

  setupVoxels(xVoxles, yVoxles, zVoxles);

  // for each shape
  auto shapeEnd = allShapes.end();
  for (auto it = allShapes.begin(); it != shapeEnd; it++) {
    ShapePtr shape = *it;
    int minXIndex;
    int minYIndex;
    int minZIndex;
    int maxXIndex;
    int maxYIndex;
    int maxZIndex;
    BoundingBoxPlanes shapeBoundingPlanes = shape->getWorldBoundingPlanes();

    //calculate index range of voxels shape is placed into
    calcVoxelIndices (
      shapeBoundingPlanes.left,  shapeBoundingPlanes.top, shapeBoundingPlanes.front,
      minXIndex, minYIndex, minZIndex);

    calcVoxelIndices (
      shapeBoundingPlanes.right,  shapeBoundingPlanes.bottom, shapeBoundingPlanes.back,
      maxXIndex, maxYIndex, maxZIndex);


    //put the shape into each voxel it belongs
    for (int x=minXIndex; x<maxXIndex; x++) {
      for (int y=minYIndex; y<maxYIndex; y++) {
        for (int z=minZIndex; z<maxZIndex; z++) {
          //voxels[x][y][z].push_back(shape);
          voxels[x][y][z].insert(shape);
        }
      }
    }

  }

}

/*
calculate index of voxel
*/
void  UniformSpaceSubdivider::calcVoxelIndices(
  FLOAT xPos, FLOAT yPos, FLOAT zPos, int &xVoxel, int &yVoxel, int &zVoxel) {
  xPos -= bPlanes.left;
  xVoxel = xPos / (FLOAT)voxelSideLength;

  yPos -= bPlanes.top;
  yVoxel = yPos / (FLOAT)voxelSideLength;

  zPos -= bPlanes.front;
  zVoxel = zPos / (FLOAT)voxelSideLength;
}


void UniformSpaceSubdivider::setupVoxels(FLOAT xVoxles, FLOAT yVoxles, FLOAT zVoxles) {

  voxels.resize(xVoxles);
  for (int i=0; i<xVoxles; i++) {
    voxels[i].resize(yVoxles);
    for (int j=0; j<yVoxles; j++) {
      voxels[i][j].resize(zVoxles);
    }
  }

}

void UniformSpaceSubdivider::testIntersect (Ray &ray, QueueItemResults &results) {

  ShapeArray testShapes; // actually set<shared_ptr<Shape>>

  int startXIndex;
  int startYIndex;
  int startZIndex;

  calcVoxelIndices (
    ray.start.x,  ray.start.y, ray.start.z,
    startXIndex, startYIndex, startZIndex);


  if (fabs(ray.direction.x) >=  fabs(ray.direction.y)
    && fabs(ray.direction.x) >=  fabs(ray.direction.z)) {
      xWalk(ray, startXIndex, startYIndex, startZIndex, testShapes);
  }
  else  if (fabs(ray.direction.y) >=  fabs(ray.direction.x)
      && fabs(ray.direction.y) >=  fabs(ray.direction.z)) {
        yWalk(ray, startXIndex, startYIndex, startZIndex, testShapes);
  }
  else {
    zWalk(ray, startXIndex, startYIndex, startZIndex, testShapes);
  }

  auto endShapes = testShapes.end();
  for (auto it = testShapes.begin();it!=endShapes;it++) {
      (*it)->testIntersect(results, ray);
  }

}

void UniformSpaceSubdivider::xWalk(
    Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes) {
    FLOAT yGradient = ray.direction.y / ray.direction.x; //y pos increase per 1 Xpos increase
    FLOAT zGradient = ray.direction.z / ray.direction.x; //z pos increase per 1 Xpos increase
    if (ray.direction.x > 0) {
      for (int x = startXIndex; x < xVoxles ; x++) {
        int y,z;
        y = startYIndex + ((x- startXIndex) * yGradient);
        z = startZIndex + ((x -startXIndex) * zGradient);

        if (y<0 || y>=yVoxles || z<0 || z>=zVoxles) {
          continue;
        }



        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());

      }
    }
    else {
      for (int x = startXIndex; x >= 0 ; x--) {
        int y,z;
        y = startYIndex + ((startXIndex-x) * yGradient);
        z = startZIndex + ((startXIndex-x) * zGradient);

        if (y<0 || y>=yVoxles || z<0 || z>=zVoxles) {
          continue;
        }

        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());
      }
    }

}

void UniformSpaceSubdivider::yWalk(
    Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes) {
    FLOAT xGradient = ray.direction.x / ray.direction.y; //y pos increase per 1 Xpos increase
    FLOAT zGradient = ray.direction.z / ray.direction.y; //z pos increase per 1 Xpos increase
    if (ray.direction.y > 0) {
      for (int y = startYIndex; y < yVoxles ; y++) {
        int x,z;
        x = startXIndex + ((y-startYIndex) * xGradient);
        z = startZIndex + ((y-startYIndex) * zGradient);

        if (x<0 || x>=yVoxles || z<0 || z>=zVoxles) {
          continue;
        }

        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());
      }
    }
    else {
      for (int y = startYIndex; y >= 0 ; y--) {
        int x,z;
        x = startXIndex + ((startYIndex-y) * xGradient);
        z = startZIndex + ((startYIndex-y) * zGradient);

        if (x<0 || x>=yVoxles || z<0 || z>=zVoxles) {
          continue;
        }

        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());
      }
    }

}

void UniformSpaceSubdivider::zWalk(
    Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes) {
    FLOAT xGradient = ray.direction.x / ray.direction.z; //y pos increase per 1 Xpos increase
    FLOAT yGradient = ray.direction.y / ray.direction.z; //z pos increase per 1 Xpos increase
    if (ray.direction.z > 0) {
      for (int z = startZIndex; z < zVoxles; z++) {
        int x,y;
        x = (FLOAT)startXIndex + ((FLOAT)(z-startZIndex) * xGradient);
        y = (FLOAT)startYIndex + ((FLOAT)(z-startZIndex) * yGradient);

        #ifdef DEBUG
        if (x==3) cout << "*"<< x<< " "<< y << " "<< z << endl;
        #endif

        if (x<0 || x>=yVoxles || y<0 || y>=yVoxles) {
          continue;
        }

        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());
      }
    }
    else {
      for (int z = startZIndex; z >= 0; z--) {
        int x,y;
        x = (FLOAT)startXIndex + ((FLOAT)(z-startZIndex) * xGradient);
        y = (FLOAT)startYIndex + ((FLOAT)(z-startZIndex) * yGradient);

        #ifdef DEBUG
        cout << x << " " << y << " "<< z <<endl;
        #endif

        if (x<0 || x>=yVoxles || y<0 || y>=yVoxles) {
          continue;
        }


        testShapes.insert (voxels[x][y][z].begin(),  voxels[x][y][z].end());
      }
    }

}



#endif
