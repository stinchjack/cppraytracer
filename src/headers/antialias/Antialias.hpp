
#ifndef ANTIALIAS_HPP
#define ANTIALIAS_HPP


#include <deque>
#include "ViewQueueItem.hpp"
#include <memory>
#include "Output.hpp"

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

  virtual void getInitalQueueItems(
        std::deque<ViewQueueItem> &queue,
        Ray & ray,
        unsigned int pixel_x,
        unsigned int pixel_y) = 0;

  virtual void getExtraQueueItems(ViewPtr view,
        std::deque<ViewQueueItem> &queue,
        Ray & ray,
        int pixel_x,
        int pixel_y);

  //virtual std::deque<QueueItem> outputUpdated (const View&) = 0;

};

class NoAntiAlias:public Antialias{

  public:
  NoAntiAlias();
  void getInitalQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);

  //std::deque<QueueItem> outputUpdated (const View&);
};


#endif
