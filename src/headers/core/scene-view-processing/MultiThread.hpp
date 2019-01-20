#ifndef MULTITHREAD_HPP
#define MULTITHREAD_HPP

#include "Scene.hpp"
#include "View.hpp"
#include "Colour.hpp"
#include "ViewQueueItem.hpp"
#include "QueueChunker.hpp"
#include <vector>




struct MTInfo {
  Scene *scene;
  ViewPtr view;
  QueueChunker *chunker;


};




#endif
