#ifdef EXPERIMENTAL

#include <vector>
#include "Shape.hpp"
#include "View.hpp"

using namespace std;

typedef vector<ShapePtr> ShapeArray;


#ifndef UNIFORMSPACESUBDIVISION
#define UNIFORMSPACESUBDIVISION
  class UniformSpaceSubdivider {
  private:
    ShapeArray allShapes;
    BoundingBoxPlanes bPlanes;
    int voxelSideLength = 2;
    vector<vector<vector<ShapeArray>>> voxels;

    FLOAT xSize = -1;
    FLOAT ySize = -1;
    FLOAT zSize = -1;
    int xVoxles = -1;
    int yVoxles = -1;
    int zVoxles = -1;

  public:
    void addShape(ShapePtr shape);
    void sort(View &view);
    void calcVoxelIndices
        (FLOAT xPos, FLOAT yPos, FLOAT zPos, int &xVoxel, int &yVoxel, int &zVoxel);
    void setupVoxels(FLOAT xVoxles, FLOAT yVoxles, FLOAT zVoxles);
  };
  #endif
#endif
