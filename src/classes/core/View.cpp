
#include "View.hpp"
#include "Scene.hpp"
#include <algorithm>

View::View (float viewWidth, float viewHeight, float eyeZ) {
  this->viewWidth = viewWidth;
  this->viewHeight = viewHeight;
  this->eyeZ = eyeZ;

}

Point View::getEye() {
  return Point (0,0,-eyeZ);
}

void View::setAntiAlias(ANTIALIAS_PTR antialias) {
  this->antialias = antialias;
}

void View::setScene(Scene *sc) {
  scene = sc;
}

Scene * View::getScene() {
  return scene;
}

void View::setOutput(OUTPUT_PTR opt) {
  output = opt;
}



void View::processChunkSetup() {

    eye = Point(0,0, 0- eyeZ);

    viewLeft = 0.0 - (viewWidth / 2.0);
    viewTop = 0.0 - (viewHeight / 2.0);

    step_x = viewWidth / output->width();
    step_y = viewHeight / output->height();

    if (antialias) {
      // tell the antialiasong object the size of the pixel in which
      // to generate extra rays
      this->antialias->setOutput (this->output);
      antialias->setRange (step_x, step_y);
    }


}


Ray View::getPixelRay(int x, int y) {
  Vector direction ( (x * step_x) + viewLeft, (y * step_y) + viewTop , eyeZ);

  Ray ray(eye, direction);
  return ray;
}

void View::processChunk(int minY, int maxY) {

  for (int x = 0; x< output->width(); x++ ) {
    for (int y = minY; y<=maxY; y++ ) {

          Vector direction ( (x * step_x) + viewLeft, (y * step_y) + viewTop , eyeZ);

          Ray ray(eye, direction);
          ray.startIsEye = true;

          ViewQueueItem vqi(ray, x, y);
          scene->renderQueueItem(this, vqi);


      }

  }


}
