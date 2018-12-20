#ifndef MULTITHREAD_HPP
#define MULTITHREAD_HPP

#include "Scene.hpp"
#include "View.hpp"
#include "Colour.hpp"
#include "ViewQueueItem.hpp"
#include "QueueChunker.hpp"
#include <deque>


/*public:
  unsigned int screen_x;
  unsigned int screen_y;
  Colour colour;
};

class MTReturn {
public:
  deque<ViewQueueItem> renderQueue;
  vector<MTPixel> pixels;
};
*/


class MTInfo {
public:
  MTInfo();
  MTInfo(Scene *scene,  View *view);
  Scene *scene =0 ;
  View *view;
  QueueChunker *chunker;


};




#endif
