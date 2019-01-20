#include "SimpleAntiAlias.hpp"
#include "Scene.hpp"
#include <cstdlib>


SimpleAntiAlias::SimpleAntiAlias(unsigned int samples) {

  this->samples = samples;
}

void SimpleAntiAlias::antialias (
  ViewQueueItem &queueItem, View *view, Scene *scene) {

  QueueItemResults queueItemResults;
  queueItemResults.pixel_x = queueItem.pixel_x;
  queueItemResults.pixel_y = queueItem.pixel_y;

  scene->testQueueItem(queueItem, queueItemResults);
  scene->processQueueItemResults (view, queueItemResults);


  for (int i = 1; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

      Point p(randX, randY, 0.0);

      Ray extraRay = Ray(queueItem.ray.start, queueItem.ray.direction + p, true);
      extraRay.startIsEye = true;
      ViewQueueItem vqi(extraRay, queueItem.pixel_x, queueItem.pixel_y);

      queueItemResults.clear();
      scene->testQueueItem(vqi,queueItemResults );
      scene->processQueueItemResults (view, queueItemResults);

  }


}
