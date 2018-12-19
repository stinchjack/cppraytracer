
#ifndef ANTIALIAS_HPP
#define ANTIALIAS_HPP


#include <deque>
#include "ViewQueueItem.hpp"

#define ANTIALIAS_PTR std::shared_ptr<Antialias>


class Antialias {


  public:

  float rangeX, rangeY;
  unsigned int samples;

  void setRange (float rangeX, float rangeY);


  virtual void getQueueItems(
        std::deque<ViewQueueItem> &queue,
        Ray & ray,
        unsigned int pixel_x,
        unsigned int pixel_y) = 0;

  //virtual std::deque<QueueItem> outputUpdated (const View&) = 0;

};

class NoAntiAlias:public Antialias{

  public:
  NoAntiAlias();
  void getQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);

  //std::deque<QueueItem> outputUpdated (const View&);
};

/*
class EDAntiAlias {

  public:

  float threshold;

  EDAntiAlias (float th);

  std::deque<QueueItem> antialias(int outputX, int outputY);
  //std::deque<QueueItem> outputUpdated (const View&);
};*/

#endif
