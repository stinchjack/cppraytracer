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
  deque<ViewQueueItemPtr>* queue;
  QueueChunker (deque<ViewQueueItemPtr> *queue, int chunk );

  bool nextChunk (deque<ViewQueueItemPtr>::iterator &chunkStart,
      deque<ViewQueueItemPtr>::iterator &chunkEnd);


};

#endif
