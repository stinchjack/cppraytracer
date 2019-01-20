#ifndef MULTITHREAD_HPP
#define MULTITHREAD_HPP

#include "Scene.hpp"
#include "View.hpp"
#include "Colour.hpp"
#include "ViewQueueItem.hpp"

#include <vector>
#include "ViewChunker.hpp"



struct MTInfo {
  Scene *scene;
  ViewPtr view;

  ViewChunker *viewChunker;

};




#endif
