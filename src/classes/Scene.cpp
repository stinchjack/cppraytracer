#include "Scene.hpp"

using namespace std;

void Scene::render(const std::string &viewName) {
  views[viewName].makeInitialRenderQueue();
  while (!views[viewName].queueEmpty()) {

    //loop thru each shape
    map<string, SHAPE_PTR>::iterator it = shapes.begin();
    while (it !=shapes.end()) {
      SHAPE_PTR shape = it->second;
      ViewQueueItem queueItem = views[viewName].popQueueItem();
      IntersectResult iResult = shape->testIntersect(queueItem.ray);
      if (iResult.hit) {
        views[viewName].output->setPixel(queueItem.pixel_x, queueItem.pixel_y, Colour(1,1,1));
      }
      it++;
    }

  }
}
