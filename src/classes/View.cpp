
#include "View.hpp"
#include "Scene.hpp"

View::View () {

}

View::View (float viewWidth, float viewHeight, float eyeZ) {
  this->viewWidth = viewWidth;
  this->viewHeight = viewHeight;
  this->eyeZ = eyeZ;

}

void View::setScene(SCENE_PTR sc) {
  scene = sc;
}
void View::setOutput(OUTPUT_PTR opt) {
  output = opt;
}

ViewQueueItem View::popQueueItem() {
  ViewQueueItem item = renderQueue.front();
  renderQueue.pop();
  return item;
}

bool View::queueEmpty() {
  return renderQueue.empty();
}

void View::makeInitialRenderQueue() {


  Point eye = Point(0,0, 0.0 - eyeZ);

  float viewLeft = 0.0 - (viewWidth / 2.0);
  float viewTop = 0.0 - (viewHeight / 2.0);

  float step_x = viewWidth / output->width();
  float step_y = viewHeight / output->height();


  unsigned int x=0, y=0;
  for(
      typename std::vector<vector<Colour>>::iterator col = output->pixels.begin();
      col != output->pixels.end(); ++col) {
      for(
          typename vector<Colour>::iterator colour = col->begin();
          colour != col->end();  ++colour) {

          Vector direction ( (x * step_x) + viewLeft, (y * step_y) + viewTop , eyeZ);

          Ray ray(eye, direction);

          ViewQueueItem item (ray, x, y);
          renderQueue.push(item);
          x++;
      }
      x=0;
      y++;
  }


}
