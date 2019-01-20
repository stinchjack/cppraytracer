#include "EDAntialias.hpp"
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "View.hpp"

EDAntiAlias::EDAntiAlias(unsigned int samples, float threshold) {

  this->samples = samples;
  this->threshold= threshold;
}

/*void EDAntiAlias::getInitalQueueItems (
      std::vector<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {

  queue.push_back(make_shared<ViewQueueItem>(ray, pixel_x, pixel_y));

}
*/

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

void EDAntiAlias::getExtraQueueItems (ViewPtr view,
      std::vector<shared_ptr<ViewQueueItem>> &queue,
  Ray & ray,
  int pixel_x, int pixel_y) {

  //if the pixel has already been antialiased, do nothing
  if (pixelStatus[pixel_x][pixel_y] != EDA_ONE_SAMPLE) {
    return;
  }
  if (output == nullptr) {
    return;
  }



  int xStart = max (pixel_x - 1, 0);
  int xEnd = min (pixel_x + 1, output->width() - 1);

  int yStart = max (pixel_y - 1, 0);
  int yEnd = min (pixel_y + 1, output->height() - 1);



  Colour newColour = output->getPixel(pixel_x, pixel_y) / samples;
  bool doExtraSamples = false;
  // check the 8 pixels surrounding the current one
  for (int i = xStart; i <= xEnd && !doExtraSamples; i++ ) {

    for (int j = yStart; j <= yEnd && !doExtraSamples; j++ ) {


      if (pixelStatus[i][j] == EDA_NOT_RENDERED || (i==pixel_x && j==pixel_y)) {
        continue;
      }


      //if one of mthe surrounding pixels is over the threshold, add extra sampling rays to the queue
      float diff = output->getPixel(i,j).diff(newColour);


      if (diff > threshold) {

        doExtraSamples = true;

        if (pixelStatus[i][j] == EDA_ONE_SAMPLE) {
          FLOAT xDiff = (i- pixel_x) * rangeX;
          FLOAT yDiff = (j- pixel_y) * rangeY;
          pixelStatus[i][j] = EDA_MULTI_PROCESS;

          Ray adjRay(ray.start, ray.direction + (Point){xDiff, yDiff, 0});

          getExtraQueueItems (view, queue, adjRay, i, j);
        }

      }


    }


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


}
