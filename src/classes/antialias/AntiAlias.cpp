#include "Antialias.hpp"
#include "EDAntialias.hpp"
#include "View.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

NoAntiAlias::NoAntiAlias() {
  samples = 1;
}

void Antialias::setOutput (shared_ptr<Output> output) {
  this->output = output;
  setupPixelStatus();
}

void Antialias::setRange (float rangeX,float  rangeY) {
  this->rangeX = rangeX;
  this->rangeY = rangeY;
}

void Antialias::setupPixelStatus() {


  if (output != nullptr) {
    pixelStatus.resize(output->width());
    fill(pixelStatus.begin(), pixelStatus.end(), vector<int>(output->height()));
    for (auto it = pixelStatus.begin(); it != pixelStatus.end(); it++) {
      //it->resize (output->height());
      fill(it->begin(), it->end(), EDA_NOT_RENDERED);
    }
  }
}

int Antialias::getPixelStatus(int screenX, int screenY) {
  return pixelStatus[screenX][screenY];
}
void Antialias::setPixelStatus(int screenX, int screenY, int status) {
  pixelStatus[screenX][screenY] = status;
}

int Antialias::getSamples(int screenX, int screenY) {
  return samples;
}

void NoAntiAlias::getInitalQueueItems(
      std::deque<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      unsigned int pixel_x,
      unsigned int pixel_y) {

  queue.push_back(make_shared<ViewQueueItem>(ray, pixel_x, pixel_y));

}

void Antialias::getExtraQueueItems(ViewPtr view,
      std::deque<shared_ptr<ViewQueueItem>> &queue,
      Ray & ray,
      int pixel_x,
      int pixel_y) {

          return;
}
