#ifndef VIEWCHUNKER_HPP
#define VIEWCHUNKER_HPP

#include <vector>
#include "ViewQueueItem.hpp"


using namespace std;

class ViewChunker {
  private:

  int chunkSize;
  int current = 0;
  int viewMaxY;

  public:
  ViewChunker (int viewMaxY, int chunkSize);

  bool nextChunk (int &minY, int &maxY);



};

#endif
