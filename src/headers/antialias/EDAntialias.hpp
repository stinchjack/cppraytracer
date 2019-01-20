
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


  float threshold;



  public:
  void setOutput (shared_ptr<Output> output);
  int getSamples(int screenX, int screenY);
  EDAntiAlias(unsigned int samples, float threshold);
  void getInitalQueueItems(
      std::vector<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);
  virtual void getExtraQueueItems (ViewPtr view,
        std::vector<shared_ptr<ViewQueueItem>> &queue,
        Ray & ray,
        int pixel_x,
        int pixel_y);



  //std::vector<QueueItem> outputUpdated (const View&);
};



#endif
