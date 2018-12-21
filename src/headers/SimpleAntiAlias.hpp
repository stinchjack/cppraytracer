
#ifndef SIMPLEANTIALIAS_HPP
#define SIMPLEANTIALIAS_HPP


#include "Antialias.hpp"


class SimpleAntiAlias:public Antialias{


  public:
  SimpleAntiAlias(unsigned int samples);
  void getInitalQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);

  //std::deque<QueueItem> outputUpdated (const View&);
};



#endif
