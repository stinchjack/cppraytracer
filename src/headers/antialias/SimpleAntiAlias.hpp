
#ifndef SIMPLEANTIALIAS_HPP
#define SIMPLEANTIALIAS_HPP


#include "Antialias.hpp"


class SimpleAntiAlias:public Antialias{


  public:
  SimpleAntiAlias(unsigned int samples);
  /*void getInitalQueueItems(
      std::vector<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y);*/

  /*virtual void antialias (
        ViewQueueItemPtr queueItem, ViewPtr view, Scene *scene);*/

  virtual void antialias (
        ViewQueueItem &queueItem, View *view, Scene *scene);
};



#endif
