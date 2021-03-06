#ifdef EXPERIMENTAL

#include <vector>
#include <set>
#include "Shape.hpp"
#include "View.hpp"
#include <iostream>

using namespace std;

//typedef vector<ShapePtr> ShapeArray;
typedef set<ShapePtr> ShapeArray;

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
    inline UniformSpaceSubdivider(){};
    UniformSpaceSubdivider(int voxelSideLength);
    void addShapes(ShapeArray shapes) ;
    void addShapes(map<std::string, ShapePtr> shapes);
    void addShape(ShapePtr shape);
    void sort(ViewPtr view);
    void calcVoxelIndices
        (FLOAT xPos, FLOAT yPos, FLOAT zPos, int &xVoxel, int &yVoxel, int &zVoxel);
    void setupVoxels(FLOAT xVoxles, FLOAT yVoxles, FLOAT zVoxles);
    void testIntersect (Ray &ray, QueueItemResults &results);
    void xWalk(  Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes);
    void yWalk(  Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes);
    void zWalk(  Ray &ray, int startXIndex, int startYIndex, int startZIndex, ShapeArray &testShapes);
  };
  #endif
#endif
