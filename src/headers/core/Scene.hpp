#ifndef SCENE_HPP
#define SCENE_HPP

#include "Texture.hpp"
#include "Light.hpp"
#include "Shape.hpp"
#include "View.hpp"
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <iostream>


using namespace std;

#define SCENE_PTR std::shared_ptr<Scene>


typedef shared_ptr<Scene> ScenePtr;

#include "IntersectHit.hpp"
#include "MultiThread.hpp"

class Scene {
  friend class LightModel;
 private:
  void adder(string label, shared_ptr<Shape> shape);
  void adder(string label, shared_ptr<Light> light);
  void adder(string label, shared_ptr<View> view);

  vector<shared_ptr<Shape>>  tempShapes;


  std::vector<shared_ptr<Light>> tempLights;
  void setupTempLights();
  void setupTempShapes();
  public:

    bool useMultiThread = false;
    int maxReflections = 5;

    map<std::string, SHAPE_PTR> shapes;
    map<std::string, shared_ptr<View>> views;
    map<std::string, shared_ptr<Light>> lights;

    template <class T, class... Args>
      shared_ptr<T> add (string label, Args&&... args) {
        shared_ptr<T> pointer = make_shared<T>(args...);
        adder (label, pointer);
        return pointer;
    }

    //void render(const view&);
    bool shadowTest(Ray &ray);
    void renderQueue (ViewPtr view);
    static void threadRenderEntryPoint(struct MTInfo *info);
    void threadRenderQueue(struct MTInfo *info);
    void threadRenderChunk (MTInfo *mtInfo);
    void testQueueItem(ViewQueueItem &queueItem, QueueItemResults &queueItemResults);
    void renderQueueItem(ViewPtr view, ViewQueueItemPtr queueItem);
    void renderQueueItem(View *view, ViewQueueItem &queueItem);
    void processQueueItemResults(ViewPtr view, QueueItemResults &queueItemResults);
    void processQueueItemResults(View *view, QueueItemResults &queueItemResults);
    void render(const std::string &viewName);
    void MTrender(const std::string &viewName);


    //~Scene();
};

#endif
