#include "QueueItemResults.hpp"

/*
map<float, IntersectHit> QueueItemResults::getMap() {
  return queueItemResults;
}
*/

IntersectHitPtr QueueItemResults::addResult (float t,  Shape * shape) {

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

IntersectHitPtr  QueueItemResults::closestResult() {
  return this->begin()->second;
}
/*
int QueueItemResults::resultCount() {
  return queueItemResults.size();
}*/
