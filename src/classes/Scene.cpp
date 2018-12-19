#include "Scene.hpp"
#include "IntersectResult.hpp"
#include <map>
#include <thread>

//unsigned int nthreads = std::thread::hardware_concurrency();

using namespace std;

void Scene::resultMerge (map<int, IntersectHit> &main, map<int, IntersectHit> &extras) {
  map<int, IntersectHit>::iterator it = extras.begin();
  while (it !=extras.end()) {
    FLOAT newT = it->first;
    if (main.find(newT) == main.end() ) {
        // newT not found in main map
        main[newT] = it->second;

    }
    else {
      main[newT + 0.00001] = it->second;
    }
    it++;
  }
}

void thread(View &view, deque<ViewQueueItem> &renderQueue) {

}
//
void Scene::renderQueue (View &view, deque<ViewQueueItem> renderQueue) {
  while (!renderQueue.empty()) {
    map<int, IntersectHit> queueItemResults;

    ViewQueueItem queueItem = renderQueue.front();
    renderQueue.pop_front();


    //loop thru each shape
    map<string, SHAPE_PTR>::iterator it = shapes.begin();

    while (it !=shapes.end()) {
      SHAPE_PTR shape = it->second;

      map<int, IntersectHit> shapeHits = shape->testIntersect(queueItem.ray);
      if (shapeHits.size() > 0) {
        resultMerge (queueItemResults, shapeHits);
      }
      it++;
    }

    if (queueItemResults.size() > 0) {
      // map<int, IntersectHit>::iterator qu = queueItemResults.begin();
      //FLOAT t = it->first;
      //IntersectHit  resultInfo = it->second;
      Colour pixel = view.output->getPixel(queueItem.pixel_x, queueItem.pixel_y);

      unsigned int sampleCount = view.output->getSampleCount(queueItem.pixel_x, queueItem.pixel_y);
      pixel += (Colour(1,1,1) * (1.0f / sampleCount));
      //pixel += (Colour(.2, .2,  .2)); // * (1.0f / views[viewName].sampleCount[queueItem.pixel_x][queueItem.pixel_y]));

      view.output->addPixel(queueItem.pixel_x, queueItem.pixel_y, pixel);

    }

  }
}

void Scene::render(const std::string &viewName) {
  views[viewName].makeInitialRenderQueue();

  renderQueue(views[viewName], views[viewName].renderQueue);

}
