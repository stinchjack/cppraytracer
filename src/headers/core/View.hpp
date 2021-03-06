#ifndef VIEW_HPP
#define VIEW_HPP


#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Ray.hpp"
#include "Output.hpp"
#include "Antialias.hpp"
#include "ViewQueueItem.hpp"
using namespace std;

//#define VIEW_PTR std::shared_ptr<View>
typedef std::shared_ptr<View> ViewPtr;
class Scene;

class View {

  //friend class Antialias;
friend class Scene;

private:
  Scene *scene = 0;
  ANTIALIAS_PTR antialias = nullptr;


  float viewWidth, viewHeight;
  float eyeZ;

  Ray transform(Ray &ray);

  shared_ptr<Output> output = nullptr;

  /************/
  // used for View::processChunk
  void processChunkSetup();


  Point eye;
  float viewLeft;
  float viewTop;

  float step_x;
  float step_y;
  /*************/



public:

  bool interpolate =false;
  FLOAT interpolateThreshold = .4;

  inline View (){};
  View (float viewWidth, float viewHeight, float eyeZ);

  vector<vector<unsigned int>> sampleCount; // to support antialiasing

  void processChunk(int minY, int maxY);
  Scene *getScene();
  void setScene(Scene * sc);
  void setOutput(shared_ptr<Output> opt);
  void setAntiAlias(ANTIALIAS_PTR antialias);
  Ray getPixelRay(int x, int y);
  Point getEye();

};


#endif
