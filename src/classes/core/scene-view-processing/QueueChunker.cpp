#include "QueueChunker.hpp"
#include <iostream>

QueueChunker::QueueChunker(deque<ViewQueueItem>  *queue , int chunk) {
  this->chunk = chunk;
  this->queue = queue;
  this->size = queue->size();
  this->current = 0;
}

bool QueueChunker::nextChunk (deque<ViewQueueItem>::iterator &chunkStart,
    deque<ViewQueueItem>::iterator &chunkEnd) {

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
