#include "Transform.hpp"
#include "Scene.hpp"
#include "IntersectHit.hpp"
#include <map>
#include <thread>
#include <iterator>
#include <memory>
#include "MultiThread.hpp"
#include "QueueChunker.hpp"
#include "EDAntialias.hpp"
#include "LightModel.hpp"

using namespace std;

void Scene::adder(string label, shared_ptr<Shape> shape) {
  shapes[label] = shape;
}

void  Scene::adder(string label, shared_ptr<Light> light) {
  lights[label] = light;
}

void Scene::adder(string label, shared_ptr<View> view) {
  views[label] = view;
}

/**brief Scene::renderQueue - process render queue for single-thread
 * renders
 * return void
 */

void Scene::renderQueue (ViewPtr view) {

  while (!view->renderQueue.empty()) {

    renderQueueItem(view, view->renderQueue.front());
    view->renderQueue.pop_front();
  }
}

/**brief Copies the map of shapes to a vector
* detail Copies the map of shapes to a vector, since vectors a much
* faster to iterate through
* return void
*/
void Scene::setupTempShapes() {

  /*
  It turns out iterating thru maps is slower than iterating through vectors.
  So, this function copies from the shapes map to vector so the vector can be used
  for the intersection test loop;
  */

  map<string, SHAPE_PTR>::iterator it = shapes.begin();

  tempShapes.resize(0);
  while (it !=shapes.end()) {

    tempShapes.push_back ( it->second);
    it++;
  }
}


/**brief Copies the map of lights to a vector
* detail Copies the map of lights to a vector, since vectors a much
* faster to iterate through
* return void
*/
void Scene::setupTempLights() {
  tempLights.resize(0);
  for (auto lightIterator = lights.begin();
    lightIterator != lights.end(); lightIterator++) {
    tempLights.push_back(lightIterator->second);
  }

}


void Scene::render(const std::string &viewName) {
  views[viewName]->setScene(this);
  setupTempShapes();
  setupTempLights();
  if (useMultiThread) {
    cout << "MultiThread render ... " << endl;
    MTrender(viewName);
  }
  else {
    cout << "Single thread render ... " << endl;
    views[viewName]->makeInitialRenderQueue();

    renderQueue(views[viewName]);
  }

}

/** brief Static function to be called by std::thread
*/
void Scene::threadRenderEntryPoint(MTInfo *info) {
  info->scene->threadRenderQueue(info);
}

void Scene::threadRenderQueue (MTInfo *mtInfo) {

  deque<ViewQueueItemPtr>::iterator Qstart;
  deque<ViewQueueItemPtr>::iterator Qend;

  int c = 0;

  while (mtInfo->chunker->nextChunk(Qstart, Qend)) {

    for (auto it = Qstart;
        it != (Qend + 1); it++)
      {
        //ViewQueueItem queueItem = *it;

        mtInfo->scene->renderQueueItem(mtInfo->view, *it);
        c++;
      }
  }

  //cout <<"thread total "<<c<<endl;
}

void Scene::MTrender(const std::string &viewName) {

  int processes = std::thread::hardware_concurrency();

  ViewPtr view = views[viewName];
  view->makeInitialRenderQueue();



  std::thread threads[processes];

  vector <MTInfo> threadInfos(processes);


  QueueChunker chunker(&view->renderQueue, 50000);

  for (int i = 0; i < processes; i++) {


      threadInfos[i].scene = this;
      threadInfos[i].view = view;

      threadInfos[i].chunker = &chunker;

      threads[i] = std::thread (Scene::threadRenderEntryPoint, &threadInfos[i]);
  }

  for (int i = 0; i < processes; i++) {
      threads[i].join();
  }


}


void Scene::testQueueItem(ViewQueueItemPtr queueItem, QueueItemResults &queueItemResults) {
  //loop thru each shape

  auto it = tempShapes.begin();

  while (it !=tempShapes.end()) {

    (*it)->testIntersect(queueItemResults, queueItem->ray);

    it++;
  }

  /*map<string, SHAPE_PTR>::iterator it = shapes.begin();

  while (it !=shapes.end()) {
    SHAPE_PTR shape = it-void Scene::renderQueueItem(ViewPtr view, ViewQueueItemPtr queueItem) {


      //cout <<"RQi  "<<endl;
      QueueItemResults queueItemResults;

      testQueueItem(queueItem, queueItemResults);



      //if there is a hit ....
      if (queueItemResults.size() > 0) {
        int  samples;


        if (view->antialias) {
          samples = view->antialias->getSamples(queueitem->pixel_x, queueitem->pixel_y);
        }
        else {
          samples = 1;
        }


        Colour newCol = LightModel::getColour(queueItemResults, samples, this, maxReflections) / samples;
        //newCol = Colour(1,1,1);

        view->output->addPixel(
          queueitem->pixel_x, queueItem->pixel_y,
          newCol);

      }

      if (view->antialias) {

        if(view->antialias->getPixelStatus(queueitem->pixel_x, queueitem->pixel_y) == EDA_NOT_RENDERED) {
          view->antialias->setPixelStatus(queueitem->pixel_x, queueitem->pixel_y, EDA_ONE_SAMPLE);
          // cout << view->antialias->getPixelStatus(queueitem->pixel_x, queueitem->pixel_y) <<endl;
        }
        view->antialias->getExtraQueueItems(
          view,
          view->renderQueue,
            queueitem->ray, queueitem->pixel_x,
            queueitem->pixel_y);
      }

}

>second;

    shape->testIntersect(queueItemResults, queueitem->ray);

    it++;
  }*/
}

void Scene::renderQueueItem(ViewPtr view, ViewQueueItemPtr queueItem) {


      //cout <<"RQi  "<<endl;
      QueueItemResults queueItemResults;

      testQueueItem(queueItem, queueItemResults);



      //if there is a hit ....
      if (queueItemResults.size() > 0) {
        int  samples;


        if (view->antialias) {
          samples = view->antialias->getSamples(queueItem->pixel_x, queueItem->pixel_y);
        }
        else {
          samples = 1;
        }


        Colour newCol = LightModel::getColour(queueItemResults, samples, this, maxReflections) / samples;
        //newCol = Colour(1,1,1);

        view->output->addPixel(
          queueItem->pixel_x, queueItem->pixel_y,
          newCol);

      }

      if (view->antialias) {

        if(view->antialias->getPixelStatus(queueItem->pixel_x, queueItem->pixel_y) == EDA_NOT_RENDERED) {
          view->antialias->setPixelStatus(queueItem->pixel_x, queueItem->pixel_y, EDA_ONE_SAMPLE);
          // cout << view->antialias->getPixelStatus(queueItem->pixel_x, queueItem->pixel_y) <<endl;
        }
        view->antialias->getExtraQueueItems(
          view,
          view->renderQueue,
            queueItem->ray, queueItem->pixel_x,
            queueItem->pixel_y);
      }

}


bool Scene::shadowTest(Ray &ray) {


      //cout <<"RQi  "<<endl;
      QueueItemResults queueItemResults;


      //Looping thru vector much quick than looping thru map!!
      for (auto it = tempShapes.begin(); it!=tempShapes.end(); it ++) {

        (*it)->testIntersect(queueItemResults, ray);

        //it++;
      }

      return queueItemResults.size() > 0;


}
