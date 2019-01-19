#include "QueueChunker.hpp"
#include <iostream>

QueueChunker::QueueChunker(deque<ViewQueueItemPtr>  *queue , int chunk) {
  this->chunk = chunk;
  this->queue = queue;
  this->size = queue->size();
  this->current = 0;
}

bool QueueChunker::nextChunk (deque<ViewQueueItemPtr>::iterator &chunkStart,
    deque<ViewQueueItemPtr>::iterator &chunkEnd) {

    if ((current + 1) >= size) {
      return false;
    }

    int start = current;
    int end = current + chunk - 1;


    if ((end +1) >= size) {
      end = size - 1;
    }
    current = end + 1;

    //cout << "chunk " << start << " to " << end <<endl;

    chunkStart = queue->begin() + start;
    chunkEnd = queue->begin()+ end;

    return true;
}
