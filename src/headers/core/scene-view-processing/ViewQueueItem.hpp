#ifndef VIEWQUEUEITEM_HPP
#define VIEWQUEUEITEM_HPP

#include "Ray.hpp"
#include <memory>

using namespace std;

class ViewQueueItem;

typedef shared_ptr<ViewQueueItem> ViewQueueItemPtr;
typedef shared_ptr<ViewQueueItem> VQIPtr;

class ViewQueueItem {
  public:
  ViewQueueItem (Ray &ray, unsigned int pixel_x,  unsigned int pixel_y);
  ViewQueueItem (Ray &ray);
  Ray ray;
  unsigned int pixel_x;
  unsigned int pixel_y;

};




#endif
