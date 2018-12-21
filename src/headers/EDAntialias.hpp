
#ifndef EDANTIALIAS_HPP
#define EDANTIALIAS_HPP


#include "Antialias.hpp"

// pixel not yet rendered
#define EDA_NOT_RENDERED 0

// set after pixel has been rendered with one ray
#define EDA_ONE_SAMPLE 1

// set when  multiple sample have been queued
#define EDA_MULTI_SAMPLE 2

class EDAntiAlias:public Antialias{

  private:


  float threshold;



  public:
  void setOutput (shared_ptr<Output> output);
  int getSamples(int screenX, int screenY);
  EDAntiAlias(unsigned int samples, float threshold);
  void getInitalQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);
  void getExtraQueueItems (
        std::deque<ViewQueueItem> &queue,
        Ray & ray,
        int pixel_x,
        int pixel_y, Colour &newColour);



  //std::deque<QueueItem> outputUpdated (const View&);
};



#endif
