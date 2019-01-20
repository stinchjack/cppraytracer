#include "SimpleAntiAlias.hpp"
#include "Scene.hpp"
#include <cstdlib>


SimpleAntiAlias::SimpleAntiAlias(unsigned int samples) {

  this->samples = samples;
}

void SimpleAntiAlias::getInitalQueueItems(
      std::vector<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {

  queue.push_back(make_shared<ViewQueueItem>(ray, pixel_x, pixel_y));

  for (int i = 1; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

      Point p(randX, randY, 0.0);

      Ray extraRay = Ray(ray.start, ray.direction + p, true);

      queue.push_back(make_shared<ViewQueueItem>(extraRay, pixel_x, pixel_y));
  }
}



void SimpleAntiAlias::antialias (
  ViewQueueItemPtr queueItem, ViewPtr view, Scene *scene) {

  //queue.push_back(make_shared<ViewQueueItem>(ray, pixel_x, pixel_y));

  for (int i = 0; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);
      QueueItemResults queueItemResults;
      queueItemResults.pixel_x = queueItem->pixel_x;
      queueItemResults.pixel_y = queueItem->pixel_y;
      Point p(randX, randY, 0.0);

      Ray extraRay = Ray(queueItem->ray.start, queueItem->ray.direction + p, true);
      extraRay.startIsEye = true;
      ViewQueueItem vqi(extraRay, queueItem->pixel_x, queueItem->pixel_y);

      scene->testQueueItem(vqi,queueItemResults );

      scene->processQueueItemResults (view, queueItemResults);
      //queue.push_back(make_shared<ViewQueueItem>(extraRay, pixel_x, pixel_y));
  }
}


void SimpleAntiAlias::antialias (
  ViewQueueItem &queueItem, View *view, Scene *scene) {

  //queue.push_back(make_shared<ViewQueueItem>(ray, pixel_x, pixel_y));

  for (int i = 0; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);
      QueueItemResults queueItemResults;
      queueItemResults.pixel_x = queueItem.pixel_x;
      queueItemResults.pixel_y = queueItem.pixel_y;
      Point p(randX, randY, 0.0);

      Ray extraRay = Ray(queueItem.ray.start, queueItem.ray.direction + p, true);
      extraRay.startIsEye = true;
      ViewQueueItem vqi(extraRay, queueItem.pixel_x, queueItem.pixel_y);

      scene->testQueueItem(vqi,queueItemResults );

      scene->processQueueItemResults (view, queueItemResults);
      //queue.push_back(make_shared<ViewQueueItem>(extraRay, pixel_x, pixel_y));
  }


}
