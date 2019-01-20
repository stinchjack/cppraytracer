#include "QueueItemResults.hpp"

/*
map<float, IntersectHit> QueueItemResults::getMap() {
  return queueItemResults;
}
*/

IntersectHitPtr QueueItemResults::addResult (float t,  Shape * shape) {

  IntersectHitPtr ih = make_shared<IntersectHit>(shape, t);

/*  if (find(t) != end() ) {
    t += .0001;
  }*/

  this->insert(ih);

  return ih;
}

IntersectHitPtr  QueueItemResults::closestResult() {
  return *this->begin();
}
