#ifdef EXPERIMENTAL
#include "UniformSpaceSubdivision.hpp"
void UniformSpaceSubdivider::addShape(ShapePtr shape) {

    allShapes.push_back(shape);



    BoundingBoxPlanes shapeBoundingPlanes = shape->getWorldBoundingPlanes();

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



void UniformSpaceSubdivider::sort(View &view) {

  Point eye = view.getEye();


  // make sure the divided space includes the eye point
  if (bPlanes.left>eye.x)  {
    bPlanes.left = eye.x;
  }
  if (bPlanes.right<eye.x)  {
    bPlanes.right = eye.x;
  }
  if (bPlanes.bottom>eye.y)  {
    bPlanes.bottom = eye.y;
  }
  if (bPlanes.top<eye.y)  {
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
  ySize = bPlanes.top - bPlanes.bottom;
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
      shapeBoundingPlanes.left,  shapeBoundingPlanes.bottom, shapeBoundingPlanes.front,
      minXIndex, minYIndex, minZIndex);

    calcVoxelIndices (
      shapeBoundingPlanes.right,  shapeBoundingPlanes.top, shapeBoundingPlanes.back,
      maxXIndex, maxYIndex, maxZIndex);


    //put the shape into each voxel it belongs
    for (int x=minXIndex; x<=maxXIndex; x++) {
      for (int y=minYIndex; y<=maxYIndex; y++) {
        for (int z=minXIndex; z<=maxXIndex; z++) {
          voxels[x][y][z].push_back(shape);
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

  yPos -= bPlanes.bottom;
  yVoxel = yPos / (FLOAT)voxelSideLength;

  zPos -= bPlanes.front;
  zVoxel = zPos / (FLOAT)voxelSideLength;
}


void UniformSpaceSubdivider::setupVoxels(FLOAT xVoxles, FLOAT yVoxles, FLOAT zVoxles) {

  voxels.resize(xVoxles);
  for (int i=0; i<xVoxles; i++) {
    voxels[i].resize(yVoxles);
    for (int j=0; j<yVoxles; j++) {
      voxels[j].resize(zVoxles);
    }
  }

}




#endif
