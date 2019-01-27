
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

  Ray ray(eye, Vector (0,0,eyeZ));
  for (int x = 0; x< output->width(); x++ ) {
    for (int y = minY; y<=maxY; y++ ) {

          //Vector direction ( (x * step_x) + viewLeft, (y * step_y) + viewTop , eyeZ);

          ray.direction.x = (x * step_x) + viewLeft;
          ray.direction.y = (y * step_y) + viewTop;

          //ViewQueueItem vqi(ray, x, y);
          //scene->renderQueueItem(this, vqi);

          if (antialias) {
            ViewQueueItem vqi(ray, x, y);
            antialias->antialias(vqi, this, this->scene);
          }
          else {
            QueueItemResults queueItemResults;
            queueItemResults.pixel_x = x;
            queueItemResults.pixel_y = y;
            scene->testQueueItem(ray, queueItemResults);
            scene->processQueueItemResults(this, queueItemResults);
          }

          if (interpolate) {

            if (x>1) {
              Colour currentColour = output->getPixel(x,y);
              Colour prevPixel = output->getPixel(x-2,y);

              FLOAT diff = prevPixel.diff(currentColour);

              if (diff<interpolateThreshold) {
                Colour interpolatedColour = (currentColour + prevPixel) * 0.5;
                output->setPIxel(x-1,y, interpolatedColour);
              else {
                if (antialias) {
                  ViewQueueItem vqi(ray, x-1, y);
                  antialias->antialias(vqi, this, this->scene);
                }
                else {
                  QueueItemResults queueItemResults;
                  queueItemResults.pixel_x = x-1;
                  queueItemResults.pixel_y = y;
                  scene->testQueueItem(ray, queueItemResults);
                  scene->processQueueItemResults(this, queueItemResults);
                }
              }

            }
            x++;

          }

      }

  }



}
