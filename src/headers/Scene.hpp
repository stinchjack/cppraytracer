#ifndef SCENE_HPP
#define SCENE_HPP

#include "Shape.hpp"
#include "View.hpp"
#include <map>
#include <string>

#define SCENE_PTR std::shared_ptr<Scene>

class Scene {

private:

  void resultMerge (map<int, IntersectHit> &main, map<int, IntersectHit> &extras);
  public:
    std::map<std::string, SHAPE_PTR> shapes;
    std::map<std::string, View> views;


    //void render(const view&);
    void renderQueue (View &view, deque<ViewQueueItem> renderQueue);
    void render(const std::string &viewName);
};

#endif
