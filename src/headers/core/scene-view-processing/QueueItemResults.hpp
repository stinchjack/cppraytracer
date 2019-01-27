#ifndef QUEUEITEMRESULTS_HPP
#define QUEUEITEMRESULTS_HPP

#include <map>
#include <utility>
#include "IntersectHit.hpp"

using namespace std;

class QueueItemResults: public multimap<float, IntersectHitPtr> {

  public:
    unsigned int pixel_x;
    unsigned int pixel_y;

    IntersectHitPtr addResult (float t, Shape * shape);


};



#endif
