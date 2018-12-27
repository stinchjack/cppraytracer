#ifndef SCENE_HPP
#define SCENE_HPP

#include "Texture.hpp"

#include "Shape.hpp"
#include "View.hpp"
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <iostream>


using namespace std;

#define SCENE_PTR std::shared_ptr<Scene>

#include "IntersectResult.hpp"
#include "MultiThread.hpp"

class Scene {

private:

  public:
    bool useMultiThread = false;

    std::map<std::string, SHAPE_PTR> shapes;
    std::map<std::string, View> views;


    //void render(const view&);
    void renderQueue (View *view);
    static void threadRenderEntryPoint(struct MTInfo *info);
    void threadRenderQueue(struct MTInfo *info);
    void renderQueueItem(View *view, ViewQueueItem &queueItem);
    void render(const std::string &viewName);
    void MTrender(const std::string &viewName);
};

#endif
