#include "QueueItemResults.hpp"



IntersectHitPtr QueueItemResults::addResult (float t,  Shape * shape) {

  IntersectHitPtr ih = make_shared<IntersectHit>(shape, t);
  insert (std::pair<float, IntersectHitPtr>(t, ih));
  return ih;
}
