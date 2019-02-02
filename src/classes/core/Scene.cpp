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
#include <iostream>
using namespace std;

void Scene::adder(shared_ptr<Shape> shape) {
  shapes.push_back(shape);
}

void  Scene::adder(shared_ptr<Light> light) {
  lights.push_back(light);
}

void Scene::adder(shared_ptr<View> view) {
  views.push_back(view);
}




void Scene::render(ViewPtr view) {
  #ifdef SPLITTERS
  shapeSorter.addShapes(shapes);
  shapeSorter.sort();
  #endif

  view->setScene(this);
  view->processChunkSetup();

  if (useMultiThread) {
    #ifdef DEBUG
    cout << "MultiThread render ... " << endl;
    #endif
    MTrender(view);
  }
  else {
    #ifdef DEBUG
    cout << "Single thread render ... " << endl;
    #endif
    view->processChunk(0, view->output->height()-1);

  }

}

/** brief Static function to be called by std::thread
*/
void Scene::threadRenderEntryPoint(MTInfo *info) {
  info->scene->threadRenderChunk(info);

}


/*
Render a range of Y pixels
*/
void Scene::threadRenderChunk (MTInfo *mtInfo) {

  int minY, maxY;

  int c = 0;

  while (mtInfo->viewChunker->nextChunk(minY, maxY)) {

    mtInfo->view->processChunk(minY, maxY);
    c++;
  }
}

void Scene::MTrender(ViewPtr view) {

  int processes = std::thread::hardware_concurrency();

  std::thread threads[processes];

  vector <MTInfo> threadInfos(processes);

  ViewChunker viewChunker(view->output->height()-1, 20);  // split by columns

  for (int i = 0; i < processes; i++) {
      threadInfos[i].scene = this;
      threadInfos[i].view = view;
      threadInfos[i].viewChunker = &viewChunker;

      threads[i] = std::thread (Scene::threadRenderEntryPoint, &threadInfos[i]);
  }

  for (int i = 0; i < processes; i++) {
      threads[i].join();
  }
}


/*brief test a ray against all the shapes in the scene
*/
void Scene::testQueueItem(Ray &ray, QueueItemResults &queueItemResults) {
  //loop thru each shape

  #ifdef SPLITTERS
  //vector<ShapePtr> shapes;
  //shapeSorter.getShapes(shapes, ray);
  shapeSorter.testIntersect(queueItemResults, ray);
  #else

  for (auto it = shapes.begin(); it!=shapes.end(); it++) {

    (*it)->testIntersect(queueItemResults, ray);


  }
  #endif
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



      if (view->antialias) {

       Ray ray = queueItemResults.begin()->second->getWorldRay();

        view->antialias->getExtraQueueItems(
            view,

            ray, queueItemResults.pixel_x,
            queueItemResults.pixel_y);
      }
    }
}


bool Scene::shadowTest(Ray &ray) {

      QueueItemResults queueItemResults;

      //Looping thru vector much quick than looping thru map!!
      auto it = shapes.begin();
      int size = shapes.size();
      for (int i =0; i<size && queueItemResults.size() == 0; i++) {

        (*it)->testIntersect(queueItemResults, ray);

        it++;
      }

      return queueItemResults.size() > 0;

}
