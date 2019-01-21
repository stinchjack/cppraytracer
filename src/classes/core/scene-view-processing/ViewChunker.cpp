#include "ViewChunker.hpp"
#include <iostream>

ViewChunker::ViewChunker (int viewMaxY, int chunkSize) {
  this->chunkSize = chunkSize;
  this->viewMaxY = viewMaxY;
  this->current = 0;
}

bool ViewChunker::nextChunk (int &minY, int &maxY) {

    if ((current + 1) >= viewMaxY) {
      return false;
    }

    int startY = current;
    int endY = current + chunkSize - 1;


    if ((endY) >= viewMaxY) {
      endY = viewMaxY;
    }
    current = endY + 1;

    minY = startY;
    maxY = endY;


    return true;
}
