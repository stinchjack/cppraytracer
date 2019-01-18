#include "QueueItemResults.hpp"

/*
map<float, IntersectHit> QueueItemResults::getMap() {
  return queueItemResults;
}
*/

void QueueItemResults::addResult (float t,  Shape * shape)) {

  IntersectHitPtr ih = make_shared<IntersectHit>(shape, t);

  if (find(t) == end() ) {
      // newT not found in main map
    this->operator[](t) = ih;

  }
  else {
    this->operator[](t+.0001) = ih;
  }

  return ih;
}

IntersectHitOtr  QueueItemResults::closestResult() {
  return this->begin()->second;
}
/*
int QueueItemResults::resultCount() {
  return queueItemResults.size();
}*/
