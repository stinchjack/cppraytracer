#include "EDAntialias.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "View.hpp"

EDAntiAlias::EDAntiAlias(unsigned int samples, float threshold) {

  this->samples = samples;
  this->threshold= threshold;
}

void EDAntiAlias::getInitalQueueItems (
      std::deque<ViewQueueItem> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {

  queue.push_back(ViewQueueItem(ray, pixel_x, pixel_y));

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

void EDAntiAlias::getExtraQueueItems (View *view,
      std::deque<ViewQueueItem> &queue,
  Ray & ray,
  int pixel_x, int pixel_y) {

  //if the pixel has already been antialiased, do nothing
  if (pixelStatus[pixel_x][pixel_y] != EDA_ONE_SAMPLE) {
    return;
  }
  if (output == nullptr) {
    return;
  }

  Colour newColour = output->getPixel(pixel_x, pixel_y);

  int xStart = max (pixel_x - 1, 0);
  int xEnd = min (pixel_x + 1, output->width() - 1);

  int yStart = max (pixel_y - 1, 0);
  int yEnd = min (pixel_y + 1, output->height() - 1);




  bool doExtraSamples = false;
  // check the 8 pixels surrounding the current one
  for (int i = xStart; i <= xEnd && !doExtraSamples; i++ ) {

    for (int j = yStart; j <= yEnd && !doExtraSamples; j++ ) {

      if (i==pixel_x && j==pixel_y) {
        continue;
      }

      if (pixelStatus[i][j] == EDA_NOT_RENDERED) {
        continue;
      }
      Colour adjColour = output->getPixel(i,j);


      //if one of mthe surrounding pixels is over the threshold, add extra sampling rays to the queue
      float diff = adjColour.diff(newColour, adjColour);


      if (diff>0) {

        doExtraSamples = true;

      }


    }


  }

  if (doExtraSamples) {

    output->setPixel(pixel_x, pixel_y, newColour / samples);

    for (int i = 1; i < samples; i++) {
        float randX =  (((float)rand() / RAND_MAX) * rangeX) - (rangeX / 2.0);
        float randY =  (((float)rand() / RAND_MAX) * rangeY) - (rangeY / 2.0);

        Ray extraRay = Ray(ray.start, ray.direction + Point(randX, randY, 0.0));
        pixelStatus[pixel_x][pixel_y] = EDA_MULTI_SAMPLE;

        ViewQueueItem vqi(extraRay, pixel_x, pixel_y);
        //queue.push_front(vqi); // MultiThread crashes here
        view->getScene()->renderQueueItem(view, vqi);
      }

    // recursively re-test the surrounding pixels

    for (int i = xStart; i <= xEnd; i++ ) {
      for (int j = yStart; j <= yEnd; j++ ) {

        if (i==pixel_x && j==pixel_y) {
          continue;
        }
        if (pixelStatus[i][j] == EDA_NOT_RENDERED) {
          continue;
        }

        FLOAT xDiff = (i- pixel_x) * rangeX;
        FLOAT yDiff = (j- pixel_y) * rangeY;
        //FLOAT newXDir = ray.direction.x + xDiff;
        //FLOAT newYDir = ray.direction.y + yDiff;

        Ray adjRay(ray.start, ray.direction + Point(xDiff, yDiff, 0));

        getExtraQueueItems (view, queue, adjRay, i, j);

      }
    }
  }


}
