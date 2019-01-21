
#ifndef EDANTIALIAS_HPP
#define EDANTIALIAS_HPP


#include "Antialias.hpp"
#include "Scene.hpp"
// pixel not yet rendered
#define EDA_NOT_RENDERED 0

// set after pixel has been rendered with one ray
#define EDA_ONE_SAMPLE 1

// set when  multiple sample have been queued
#define EDA_MULTI_SAMPLE 2

#define EDA_MULTI_PROCESS 3
class EDAntiAlias:public Antialias{

  private:
  vector<vector<int>> pixelStatus;

  float threshold;

  public:

  int getSamples(int screenX, int screenY);
  EDAntiAlias(unsigned int samples, float threshold);
  //void setupPixelStatus();
  virtual Colour antialias (
        ViewQueueItem &queueItem, View *view, Scene *scene);

  inline int getPixelStatus(int screenX, int screenY) {
    return pixelStatus[screenX][screenY];
  }
  inline void setPixelStatus(int screenX, int screenY, int status) {
    pixelStatus[screenX][screenY] = status;
  }


  //std::vector<QueueItem> outputUpdated (const View&);
};



#endif
