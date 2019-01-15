#ifndef VIEW_HPP
#define VIEW_HPP


#include <string>
#include <memory>
#include <map>
#include <deque>
#include "Ray.hpp"
#include "Output.hpp"
#include "Antialias.hpp"
#include "ViewQueueItem.hpp"
using namespace std;

#define VIEW_PTR std::shared_ptr<View>

class Scene;

class View {

  //friend class Antialias;
friend class Scene;

private:
  Scene *scene = 0;
  ANTIALIAS_PTR antialias = nullptr;


  float viewWidth, viewHeight;
  float eyeZ;
  deque<ViewQueueItem> renderQueue;
  Ray transform(Ray &ray);

  shared_ptr<Output> output = nullptr;


public:

  //void setAntiAlias(ANTIALIAS_PTR a);
  View ();
  View (float viewWidth, float viewHeight, float eyeZ);

  vector<vector<unsigned int>> sampleCount; // to support antialiasing

  ViewQueueItem popQueueItem();
  bool queueEmpty();

  Scene *getScene();
  void setScene(Scene * sc);
  void setOutput(shared_ptr<Output> opt);
  void setAntiAlias(ANTIALIAS_PTR antialias);

  void makeInitialRenderQueue();


};


#endif