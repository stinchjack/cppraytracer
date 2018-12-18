#ifndef VIEWQUEUEITEM_HPP
#define VIEWQUEUEITEM_HPP

#include "Ray.hpp"

class ViewQueueItem {
  public:
  ViewQueueItem (Ray &ray, unsigned int pixel_x,  unsigned int pixel_y);
  Ray ray;
  unsigned int pixel_x;
  unsigned int pixel_y;

};

#endif
