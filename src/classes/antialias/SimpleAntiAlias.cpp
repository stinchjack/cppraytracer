#include "Antialias.hpp"
#include "ViewQueueItem.hpp"
#include "Scene.hpp"
#include "QueueItemResults.hpp"
#include "Output.hpp"

#include "SimpleAntiAlias.hpp"
#include "Scene.hpp"
#include <cstdlib>
#include "LightModel.hpp"

SimpleAntiAlias::SimpleAntiAlias(unsigned int samples) {

  this->samples = samples;
}

Colour SimpleAntiAlias::antialias (
  ViewQueueItem &queueItem, View *view, Scene *scene) {

  QueueItemResults queueItemResults;
  queueItemResults.pixel_x = queueItem.pixel_x;
  queueItemResults.pixel_y = queueItem.pixel_y;

  scene->testQueueItem(queueItem, queueItemResults );
  Colour newCol = LightModel::getColour(queueItemResults, samples, scene, scene->maxReflections);
  newCol = newCol /samples;

  for (int i = 1; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

      Point p(randX, randY, 0.0);

      Ray extraRay = Ray(queueItem.ray.start, queueItem.ray.direction + p, true);
      extraRay.startIsEye = true;
      ViewQueueItem vqi(extraRay, queueItem.pixel_x, queueItem.pixel_y);

      queueItemResults.clear();
      scene->testQueueItem(vqi,queueItemResults );
      Colour extraSample = LightModel::getColour(queueItemResults, samples, scene, scene->maxReflections);
      newCol += extraSample /samples;
  }

  return newCol;

}
