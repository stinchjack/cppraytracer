#include "Transform.hpp"
#include "Scene.hpp"
#include "IntersectHit.hpp"
#include <map>
#include <thread>
#include <iterator>
#include <memory>
#include "MultiThread.hpp"
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
  int size= shapes.size();
  int i=0;

  tempShapes.resize(0);
  while (i<size) {

    tempShapes.push_back ( it->second);
    it++;
    i++;
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
  views[viewName]->processChunkSetup();
  setupTempShapes();
  setupTempLights();
  if (useMultiThread) {
    cout << "MultiThread render ... " << endl;
    MTrender(viewName);
  }
  else {
    cout << "Single thread render ... " << endl;
    views[viewName]->processChunk(0, views[viewName]->output->height()-1);

  }

}

/** brief Static function to be called by std::thread
*/
void Scene::threadRenderEntryPoint(MTInfo *info) {
  info->scene->threadRenderChunk(info);

}



void Scene::threadRenderChunk (MTInfo *mtInfo) {

  int minY, maxY;

  int c = 0;

  while (mtInfo->viewChunker->nextChunk(minY, maxY)) {
    mtInfo->view->processChunk(minY, maxY);
    c++;
  }


  //cout <<"thread total "<<c<<endl;
}

void Scene::MTrender(const std::string &viewName) {

  int processes = std::thread::hardware_concurrency();

  ViewPtr view = views[viewName];
  //view->makeInitialRenderQueue();
  std::thread threads[processes];

  vector <MTInfo> threadInfos(processes);

  ViewChunker viewChunker(view->output->height()-1, 20);  // split by columns

  for (int i = 0; i < processes; i++) {
      threadInfos[i].scene = this;
      threadInfos[i].view = view;
;
      threadInfos[i].viewChunker = &viewChunker;

      threads[i] = std::thread (Scene::threadRenderEntryPoint, &threadInfos[i]);
  }

  for (int i = 0; i < processes; i++) {
      threads[i].join();
  }
}



void Scene::testQueueItem(ViewQueueItem &queueItem, QueueItemResults &queueItemResults) {
  //loop thru each shape

  auto it = tempShapes.begin();
  //auto end = tempShapes.end();
  int size = tempShapes.size();
  int i=0;
  //while (it !=end())) {
  while (i < size) {

    //potential alternate placement for extra antialias rays

    (*it)->testIntersect(queueItemResults, queueItem.ray);

    it++;
    i++;
  }


}

void Scene::renderQueueItem(View *view, ViewQueueItem &queueItem) {

      if (view->antialias) {
        view->antialias->antialias(queueItem, view, this);
      }
      else {
        QueueItemResults queueItemResults;
        queueItemResults.pixel_x = queueItem.pixel_x;
        queueItemResults.pixel_y = queueItem.pixel_y;
        testQueueItem(queueItem, queueItemResults);
        processQueueItemResults(view, queueItemResults);
      }
}


void Scene::processQueueItemResults(View *view, QueueItemResults &queueItemResults) {

      //if there is a hit ....
      if (queueItemResults.size() > 0) {
        int  samples;

        if (view->antialias) {
          samples = view->antialias->getSamples(queueItemResults.pixel_x, queueItemResults.pixel_y);
        }
        else {
          samples = 1;
        }

        Colour newCol = LightModel::getColour(queueItemResults, samples, this, maxReflections) / samples;
        //newCol = Colour(1,1,1);

        view->output->addPixel(
          queueItemResults.pixel_x, queueItemResults.pixel_y,
          newCol);

      }

      if (view->antialias) {

        if(view->antialias->getPixelStatus(queueItemResults.pixel_x, queueItemResults.pixel_y) == EDA_NOT_RENDERED) {
          view->antialias->setPixelStatus(queueItemResults.pixel_x, queueItemResults.pixel_y, EDA_ONE_SAMPLE);
          // cout << view->antialias->getPixelStatus(queueItem->pixel_x, queueItem->pixel_y) <<endl;
        }
        /*view->antialias->getExtraQueueItems(
          view,
          view->renderQueue,
            queueItem->ray, queueItemResults.pixel_x,
            queueItemResults.pixel_y);*/
      }

}


bool Scene::shadowTest(Ray &ray) {

      QueueItemResults queueItemResults;

      //Looping thru vector much quick than looping thru map!!
      auto it = tempShapes.begin();
      int size = tempShapes.size();
      for (int i =0; i<size; i++) {

        (*it)->testIntersect(queueItemResults, ray);

        it++;
      }

      return queueItemResults.size() > 0;

}
