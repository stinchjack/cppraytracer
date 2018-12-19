#include "Antialias.hpp"

NoAntiAlias::NoAntiAlias() {
  samples = 1;
}

void Antialias::setRange (float rangeX,float  rangeY) {
  this->rangeX = rangeX;
  this->rangeY = rangeY;
}

void NoAntiAlias::getQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {

  queue.push_back(ViewQueueItem(ray, pixel_x, pixel_y));

}
