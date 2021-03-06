
#ifndef ANTIALIAS_HPP
#define ANTIALIAS_HPP


#include <vector>
#include "ViewQueueItem.hpp"
#include "QueueItemResults.hpp"
#include <memory>
#include "Output.hpp"
class Scene;

#define ANTIALIAS_PTR std::shared_ptr<Antialias>

using namespace std;

class View;
typedef shared_ptr<View> ViewPtr ;

class Antialias {

  protected:
  shared_ptr<Output> output = nullptr;
  vector<vector<int>> pixelStatus;


  int samples;

  public:

  float rangeX, rangeY;


  void setupPixelStatus();
  void setRange (float rangeX, float rangeY);
  virtual void setOutput (shared_ptr<Output> output);
  virtual int getPixelStatus(int screenX, int screenY);
  void setPixelStatus(int screenX, int screenY, int status);
  virtual int getSamples(int screenX, int screenY);



  virtual void getExtraQueueItems(View *view,
        Ray & ray,
        int pixel_x,
        int pixel_y);


  virtual void antialias (
        ViewQueueItem &queueItem, View *view, Scene *scene) = 0;

};


#endif
