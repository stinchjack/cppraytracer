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

  QueueItemResults queueItemResults1;

  scene->testQueueItem(queueItem, queueItemResults1);
  Colour newCol = LightModel::getColour(queueItemResults1, samples, scene, scene->maxReflections);
  newCol = newCol /samples;

  for (int i = 1; i < samples; i++) {
      float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
      float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

      Point p(randX, randY, 0.0);

      Ray extraRay(queueItem.ray.start, queueItem.ray.direction + p, true);
      extraRay.startIsEye = true;

      QueueItemResults queueItemResults2;
      scene->testQueueItem(extraRay, queueItemResults2);
      Colour extraSample = LightModel::getColour(queueItemResults2, samples, scene, scene->maxReflections) / samples;
      newCol += extraSample;
  }

  return newCol;

}
