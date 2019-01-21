
#ifndef ANTIALIAS_HPP
#define ANTIALIAS_HPP


#include <vector>
#include <memory>


#include "Colour.hpp"

class LightModel;
class Output;
class Scene;
class Antialias;
class ViewQueueItem;
class QueueItemResults;
class View;

typedef std::shared_ptr<Antialias> AntialiasPtr;
typedef std::shared_ptr<Antialias> AntiAliasPtr;

using namespace std;

class Antialias {

  protected:
  shared_ptr<Output> output = nullptr;

  int samples;

  public:

  float rangeX, rangeY;

  void setRange (float rangeX, float rangeY);
  void setOutput (shared_ptr<Output> output);
  virtual int getSamples(int screenX, int screenY);

  virtual Colour antialias (
        ViewQueueItem &queueItem, View *view, Scene *scene) = 0;

};


#endif
