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
#include "UniformSpaceSubdivision.hpp"

class Scene {
  friend class LightModel;
 private:
  void adder(shared_ptr<Shape> shape);
  void adder(shared_ptr<Light> light);
  void adder(shared_ptr<View> view);

  //vector<shared_ptr<Shape>>  tempShapes;
  //std::vector<shared_ptr<Light>> tempLights;
  //void setupTempLights();
  //void setupTempShapes();


  public:

    #ifdef EXPERIMENTAL
      //UniformSpaceSubdivider shapeSorter;
    #endif
    inline Scene(){};
    bool useMultiThread = false;
    int maxReflections = 5;

    vector <ShapePtr> shapes;
    vector <ViewPtr> views;
    vector <shared_ptr<Light>> lights;

    template <class T, class... Args>
      shared_ptr<T> add (Args&&... args) {
        shared_ptr<T> pointer = make_shared<T>(args...);
        adder (pointer);
        return pointer;
    }

    bool shadowTest(Ray &ray);
    static void threadRenderEntryPoint(struct MTInfo *info);
    void threadRenderChunk (MTInfo *mtInfo);
    inline void testQueueItem(ViewQueueItem &queueItem, QueueItemResults &queueItemResults);
    void testQueueItem(Ray &ray, QueueItemResults &queueItemResults);
    void renderQueueItem(View *view, ViewQueueItem &queueItem);
    void processQueueItemResults(View *view, QueueItemResults &queueItemResults);
    void render(const std::string &viewName);
    void render(ViewPtr view);
    void MTrender(ViewPtr view);

};

void Scene::testQueueItem(ViewQueueItem &queueItem, QueueItemResults &queueItemResults) {
  testQueueItem(queueItem.ray, queueItemResults);
}

/*
void walk(FLOAT walkDirectionAmont, )

*/
#endif
