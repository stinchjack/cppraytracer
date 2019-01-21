#include "EDAntialias.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "View.hpp"
#include "Antialias.hpp"
#include "ViewQueueItem.hpp"
#include "Scene.hpp"
#include "QueueItemResults.hpp"
#include "Output.hpp"
#include "SimpleAntiAlias.hpp"
#include "Scene.hpp"
#include "LightModel.hpp"

EDAntiAlias::EDAntiAlias(unsigned int samples, float threshold) {

  samples = samples;
  threshold= threshold;


  if (output != nullptr) {
    pixelStatus.resize(output->width());
    fill(pixelStatus.begin(), pixelStatus.end(), vector<int>(output->height()));

    auto it = pixelStatus.begin();
    int size = pixelStatus.size();

    //for (auto it = pixelStatus.begin(); it != pixelStatus.end(); it++) {
    for (int i=0; i<size; i++) {
      //it->resize (output->height());

      fill(it->begin(), it->end(), EDA_NOT_RENDERED);
      it++;
    }
  }
}


Colour EDAntiAlias::antialias (
  ViewQueueItem &queueItem, View *view, Scene *scene) {

  QueueItemResults queueItemResults;
  queueItemResults.pixel_x = queueItem.pixel_x;
  queueItemResults.pixel_y = queueItem.pixel_y;

  scene->testQueueItem(queueItem, queueItemResults);
  Colour newCol = LightModel::getColour(queueItemResults, samples, scene, scene->maxReflections);

  //check surrounding pixels

  int xStart = max ((int)queueItem.pixel_x - 1, 0);
  int xEnd = min ((int)queueItem.pixel_x + 1, output->width() - 1);

  int yStart = max ((int)queueItem.pixel_y - 1, 0);
  int yEnd = min ((int)queueItem.pixel_y + 1, output->height() - 1);

  bool doExtraSamples = false;

  for (int i = xStart; i <= xEnd && !doExtraSamples; i++ ) {
    for (int j = yStart; j <= yEnd && !doExtraSamples; j++ ) {

      //if one of mthe surrounding pixels is over the threshold, add extra sampling rays to the queue
      float diff = view->getOutput()->getPixel(i,j).diff(newCol);


      if (diff > threshold) {
        doExtraSamples = true;
        newCol = newCol * (1.0 / samples);
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
      }
    }
  }
  return newCol;
}

int EDAntiAlias::getSamples(int screenX, int screenY) {
    if (pixelStatus[screenX][screenY] == EDA_MULTI_SAMPLE) {
      return samples;
    }
    return 1;
}


/*
  if (doExtraSamples) {

    //Colour sample1 = output->getPixel(pixel_x, pixel_y) / samples;
    output->setPixel(pixel_x, pixel_y, newColour / samples);

    for (int i = 0; i < samples - 1; i++) {
        float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
        float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

        Ray extraRay = Ray(ray.start, ray.direction + Point{randX, randY, 0.0});
        pixelStatus[pixel_x][pixel_y] = EDA_MULTI_SAMPLE;

        // needs re-write
      /view->getScene()->renderQueueItem(view, make_shared<ViewQueueItem> (extraRay, pixel_x, pixel_y));
      }


  }*/
