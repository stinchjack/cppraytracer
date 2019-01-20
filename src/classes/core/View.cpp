
#include "View.hpp"
#include "Scene.hpp"
#include <algorithm>
View::View () {

}

View::View (float viewWidth, float viewHeight, float eyeZ) {
  this->viewWidth = viewWidth;
  this->viewHeight = viewHeight;
  this->eyeZ = eyeZ;

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

/*ViewQueueItemPtr View::popQueueItem() {
  ViewQueueItemPtr item = renderQueue.front();
  renderQueue.pop_front();
  return item;
}*/

bool View::queueEmpty() {
  return renderQueue.empty();
}



void View::makeInitialRenderQueue() {

  if (this->antialias) {
    this->antialias->setOutput (this->output);
  }


  Point eye(0,0, 0- eyeZ);

  float viewLeft = 0.0 - (viewWidth / 2.0);
  float viewTop = 0.0 - (viewHeight / 2.0);

  float step_x = viewWidth / output->width();
  float step_y = viewHeight / output->height();

  if (antialias) {
    // tell the antialiasong object the size of the pixel in which
    // to generate extra rays
    antialias->setRange (step_x, step_y);
  }


  for (int x = 0; x< output->width(); x++ ) {
    for (int y = 0; y< output->height(); y++ ) {

          Vector direction ( (x * step_x) + viewLeft, (y * step_y) + viewTop , eyeZ);

          Ray ray(eye, direction);

          renderQueue.push_back(make_shared<ViewQueueItem> (ray, x, y));

          /*if (antialias == nullptr) {
            ray.startIsEye = true;

            renderQueue.push_back(make_shared<ViewQueueItem> (ray, x, y));
          }
          else {
            antialias->getInitalQueueItems(renderQueue, ray, x, y);
          }*/

      }

  }


}
