#include "EDAntialias.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "View.hpp"

EDAntiAlias::EDAntiAlias(unsigned int samples, float threshold) {

  this->samples = samples;
  this->threshold= threshold;
}



void EDAntiAlias::setOutput (shared_ptr<Output> output) {
  this->output = output;
  setupPixelStatus();
}

int EDAntiAlias::getSamples(int screenX, int screenY) {
    if (pixelStatus[screenX][screenY] == EDA_MULTI_SAMPLE) {
      return samples;
    }
    return 1;
}

void EDAntiAlias::antialias (
  ViewQueueItem &queueItem, View *view, Scene *scene) {

  QueueItemResults queueItemResults;
  queueItemResults.pixel_x = queueItem.pixel_x;
  queueItemResults.pixel_y = queueItem.pixel_y;

  setPixelStatus(queueItemResults.pixel_x, queueItemResults.pixel_y, EDA_ONE_SAMPLE);
  scene->testQueueItem(queueItem, queueItemResults);
  scene->processQueueItemResults (view, queueItemResults);

}

void EDAntiAlias::getExtraQueueItems (View *view,
  Ray & ray, int pixel_x, int pixel_y) {

  //if the pixel has already been antialiased, do nothing
  if (pixelStatus[pixel_x][pixel_y] != EDA_ONE_SAMPLE) {
    return;
  }
  /*if (output == nullptr) {
    return;
  }*/

  int xStart = max (pixel_x - 1, 0);
  int xEnd = min (pixel_x + 1, output->width() - 1);

  int yStart = max (pixel_y - 1, 0);
  int yEnd = min (pixel_y + 1, output->height() - 1);

  Colour newColour = output->getPixel(pixel_x, pixel_y);
  bool doExtraSamples = false;
  // check the 8 pixels surrounding the current one
  for (int i = xStart; i <= xEnd && !doExtraSamples; i++ ) {
    for (int j = yStart; j <= yEnd && !doExtraSamples; j++ ) {

      if (pixelStatus[i][j] == EDA_NOT_RENDERED
          || (i==pixel_x && j==pixel_y)) {
        continue;
      }

      //if one of mthe surrounding pixels is over the threshold, add extra sampling rays to the queue
      float diff = output->getPixel(i,j).diff(newColour);

      if (diff > threshold) {
        doExtraSamples = true;
      }
    }
  }


  if (doExtraSamples) {
    QueueItemResults queueItemResults;
    queueItemResults.pixel_x = pixel_x;
    queueItemResults.pixel_y = pixel_y;

    output->setPixel(pixel_x, pixel_y, newColour / samples);

    for (int i = 1; i < samples ; i++) {
        float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
        float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

        setPixelStatus(pixel_x, pixel_y, EDA_MULTI_SAMPLE);
        Point p(randX, randY, 0.0);
        Ray extraRay = Ray(ray.start, ray.direction + p, true);

        extraRay.startIsEye = true;
        ViewQueueItem vqi(extraRay, pixel_x, pixel_y);

        queueItemResults.clear();
        view->getScene()->testQueueItem(vqi,queueItemResults );
        view->getScene()->processQueueItemResults (view, queueItemResults);
      }

      // surrounding pixel retest

      for (int i = xStart; i <= xEnd; i++ ) {

        for (int j = yStart; j <= yEnd; j++ ) {
          if (!(pixelStatus[i][j] == EDA_ONE_SAMPLE)
              || (i==pixel_x && j==pixel_y)) {
            continue;
          }

          Ray adjacentRay = view->getPixelRay(i,j);
          adjacentRay.startIsEye = true;
          getExtraQueueItems (view, adjacentRay, i, j);
        }
      }


  }


}
