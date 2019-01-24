#ifndef QUEUEITEMRESULTS_HPP
#define QUEUEITEMRESULTS_HPP

#include <map>
#include "IntersectHit.hpp"

using namespace std;

class QueueItemResults: public map<float, IntersectHitPtr> {

  public:
    unsigned int pixel_x;
    unsigned int pixel_y;

    IntersectHitPtr addResult (float t, Shape * shape);


};

#endif
