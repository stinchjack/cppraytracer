#ifndef QUEUECHUNKER_HPP
#define QUEUECHUNKER_HPP

#include <deque>
#include "ViewQueueItem.hpp"


using namespace std;

class QueueChunker {
  private:

  int chunk;
  int current = 0;
  int size;

  public:
  deque<ViewQueueItem>* queue;
  QueueChunker (deque<ViewQueueItem> *queue, int chunk );

  bool nextChunk (deque<ViewQueueItem>::iterator &chunkStart,
      deque<ViewQueueItem>::iterator &chunkEnd);


};

#endif
