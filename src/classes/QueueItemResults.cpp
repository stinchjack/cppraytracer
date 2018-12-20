#include "QueueItemResults.hpp"


map<float, IntersectHit> QueueItemResults::getMap() {
  return queueItemResults;
}

void QueueItemResults::addResult (float t, const IntersectHit &ih) {

  if (queueItemResults.find(t) == queueItemResults.end() ) {
      // newT not found in main map
    queueItemResults[t] = ih;

  }
  else {
    queueItemResults[t+.0001] = ih;
  }

}

IntersectHit QueueItemResults::closestResult() {
  return (queueItemResults.begin()->second);
}

int QueueItemResults::resultCount() {
  return queueItemResults.size();
}
