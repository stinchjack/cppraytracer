#include "Scene.hpp"
#include "IntersectResult.hpp"
#include <map>
#include <thread>
#include <iterator>
#include "MultiThread.hpp"
#include "QueueChunker.hpp"

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

      threads[i] = std::thread (Scene::threadRenderQueue, &threadInfos[i]);
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

      if (queueItemResults.resultCount() > 0) {
        // map<int, IntersectHit>::iterator qu = queueItemResults.begin();
        //FLOAT t = it->first;
        //IntersectHit  resultInfo = it->second;
        //Colour pixel = view->output->getPixel(queueItem.pixel_x, queueItem.pixel_y);

        //unsigned int sampleCount = view->output->getSampleCount(queueItem.pixel_x, queueItem.pixel_y);
        //pixel += Colour(1,1,1);
        //pixel += (Colour(.2, .2,  .2)); // * (1.0f / views[viewName].sampleCount[queueItem.pixel_x][queueItem.pixel_y]));

        view->output->addPixel(queueItem.pixel_x, queueItem.pixel_y, Colour(1,1,1));

      }
}
