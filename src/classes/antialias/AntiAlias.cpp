#include "Antialias.hpp"
#include "EDAntialias.hpp"
#include "View.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

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

int Antialias::getPixelStatus(int screenX, int screenY) {
  return pixelStatus[screenX][screenY];
}
void Antialias::setPixelStatus(int screenX, int screenY, int status) {
  pixelStatus[screenX][screenY] = status;
}

int Antialias::getSamples(int screenX, int screenY) {
  return samples;
}

void Antialias::getExtraQueueItems(View *view,
      Ray & ray,
      int pixel_x,
      int pixel_y) {

          return;
}
