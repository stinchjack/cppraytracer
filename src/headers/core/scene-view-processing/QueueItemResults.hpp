#ifndef QUEUEITEMRESULTS_HPP
#define QUEUEITEMRESULTS_HPP

#include <set>
#include <utility>
#include "IntersectHit.hpp"

using namespace std;


struct IHPTRcomp {
  inline bool operator() (const IHPtr lhs, const IHPtr rhs) const {
    return lhs->t < rhs->t;
  }
};

class QueueItemResults: public set<IHPtr, IHPTRcomp> {

  public:

    unsigned int pixel_x;
    unsigned int pixel_y;

    IntersectHitPtr addResult (float t, Shape * shape);

    IntersectHitPtr closestResult();

};

#endif
