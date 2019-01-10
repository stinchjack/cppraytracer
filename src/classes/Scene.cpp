#include "Transform.hpp"
#include "Scene.hpp"
#include "IntersectHit.hpp"
#include <map>
#include <thread>
#include <iterator>
#include "MultiThread.hpp"
#include "QueueChunker.hpp"
#include "EDAntialias.hpp"
#include "LightModel.hpp"

//unsigned int nthreads = std::thread::hardware_concurrency();

using namespace std;


//https://stackoverflow.com/questions/10988338/c-unlocking-a-stdmutex-before-calling-stdunique-lock-wait
void Scene::renderQueue (View *view) {
  deque<ViewQueueItem> &renderQueue = view->renderQueue;
  while (!renderQueue.empty()) {


    ViewQueueItem queueItem = renderQueue.front();
    renderQueue.pop_front();
    renderQueueItem(view, queueItem);
  }
}


void Scene::render(const std::string &viewName) {
  views[viewName].setScene(this);
  if (useMultiThread) {
    cout << "MultiThread render ... " << endl;
    MTrender(viewName);
  }
  else {
    cout << "Single thread render ... " << endl;
    views[viewName].makeInitialRenderQueue();

    renderQueue(&views[viewName]);
  }
}


void Scene::threadRenderEntryPoint(MTInfo *info) {
  info->scene->threadRenderQueue(info);
}

void Scene::threadRenderQueue (MTInfo *mtInfo) {

  deque<ViewQueueItem>::iterator Qstart;
  deque<ViewQueueItem>::iterator Qend;

  int c = 0;

  while (mtInfo->chunker->nextChunk(Qstart, Qend)) {

    for (deque<ViewQueueItem>::iterator it = Qstart;
        it != (Qend + 1); it++)
      {
        ViewQueueItem queueItem = *it;

        mtInfo->scene->renderQueueItem(mtInfo->view, queueItem);
        c++;
      }
  }

  //cout <<"thread total "<<c<<endl;
}

void Scene::MTrender(const std::string &viewName) {

  int processes = std::thread::hardware_concurrency();

  View view = views[viewName];
  view.makeInitialRenderQueue();



  std::thread threads[processes];

  vector <MTInfo> threadInfos(processes);


  QueueChunker chunker(&view.renderQueue, 50000);

  for (int i = 0; i < processes; i++) {


      threadInfos[i].scene = this;
      threadInfos[i].view = &view;

      threadInfos[i].chunker = &chunker;

      threads[i] = std::thread (Scene::threadRenderEntryPoint, &threadInfos[i]);
  }

  for (int i = 0; i < processes; i++) {
      threads[i].join();
  }


}

void Scene::renderQueueItem(View *view, ViewQueueItem &queueItem) {


      //cout <<"RQi  "<<endl;
      QueueItemResults queueItemResults;
      //loop thru each shape
      map<string, SHAPE_PTR>::iterator it = shapes.begin();

      while (it !=shapes.end()) {
        SHAPE_PTR shape = it->second;

        shape->testIntersect(queueItemResults, queueItem.ray);

        it++;
      }


      //if there is a hit ....
      if (queueItemResults.size() > 0) {
        int  samples;


        if (view->antialias) {
          samples = view->antialias->getSamples(queueItem.pixel_x, queueItem.pixel_y);
        }
        else {
          samples = 1;
        }

        FLOAT hitT = queueItemResults.begin()->first;
        IntersectHit &ih = queueItemResults.begin()->second;

        ih.t = hitT;


        Colour newCol = LightModel::getColour(queueItemResults, samples, this);
        //newCol = Colour(1,1,1);

        view->output->addPixel(
          queueItem.pixel_x, queueItem.pixel_y,
          newCol);

      }

      if (view->antialias) {

        if(view->antialias->getPixelStatus(queueItem.pixel_x, queueItem.pixel_y) == EDA_NOT_RENDERED) {
          view->antialias->setPixelStatus(queueItem.pixel_x, queueItem.pixel_y, EDA_ONE_SAMPLE);
          // cout << view->antialias->getPixelStatus(queueItem.pixel_x, queueItem.pixel_y) <<endl;


        }
        view->antialias->getExtraQueueItems(
          view,
          view->renderQueue,
            queueItem.ray, queueItem.pixel_x,
            queueItem.pixel_y);
      }

}


bool Scene::shadowTest(Ray &ray) {


      //cout <<"RQi  "<<endl;
      QueueItemResults queueItemResults;
      //loop thru each shape
      map<string, SHAPE_PTR>::iterator it = shapes.begin();

      while (it !=shapes.end()) {
        SHAPE_PTR shape = it->second;

        shape->testIntersect(queueItemResults, ray);

        it++;
      }

      return queueItemResults.size();


}
