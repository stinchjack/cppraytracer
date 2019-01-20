#ifndef QUEUECHUNKER_HPP
#define QUEUECHUNKER_HPP

#include <vector>
#include "ViewQueueItem.hpp"


using namespace std;

class QueueChunker {
  private:

  int chunk;
  int current = 0;
  int size;

  public:
  vector<ViewQueueItemPtr>* queue;
  QueueChunker (vector<ViewQueueItemPtr> *queue, int chunk );

  bool nextChunk (vector<ViewQueueItemPtr>::iterator &chunkStart,
      vector<ViewQueueItemPtr>::iterator &chunkEnd);


};

#endif
