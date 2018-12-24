#include "SimpleAntiAlias.hpp"
#include <cstdlib>


SimpleAntiAlias::SimpleAntiAlias(unsigned int samples) {

  this->samples = samples;
}

void SimpleAntiAlias::getInitalQueueItems(
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {


  for (int i = 0; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

      Ray extraRay = Ray(ray.start, ray.direction + Point(randX, randY, 0.0));

      queue.push_back(ViewQueueItem(extraRay, pixel_x, pixel_y));
  }


}