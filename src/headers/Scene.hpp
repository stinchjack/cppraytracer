#ifndef SCENE_HPP
#define SCENE_HPP

#include "Shape.hpp"
#include "View.hpp"
#include <map>
#include <string>

#define SCENE_PTR std::shared_ptr<Scene>

class Scene {

  public:
    std::map<std::string, SHAPE_PTR> shapes;
    std::map<std::string, View> views;


    //void render(const view&);
    void render(const std::string &viewName);
};

#endif
