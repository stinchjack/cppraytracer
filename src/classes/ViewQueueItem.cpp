#include "ViewQueueItem.hpp"

ViewQueueItem::ViewQueueItem (Ray &ray, unsigned int pixel_x,  unsigned int pixel_y){
  this->ray = ray;
  this->pixel_x = pixel_x;
  this->pixel_y = pixel_y;
}
