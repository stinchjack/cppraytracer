#ifndef QUEUEITEMRESULTS_HPP
#define QUEUEITEMRESULTS_HPP

#include <map>
#include "IntersectHit.hpp"

using namespace std;

class QueueItemResults: public map<float, IntersectHitPtr> {

  //private:
  //map<float, IntersectHit> queueItemResults;



  public:
    unsigned int pixel_x;
    unsigned int pixel_y;

    IntersectHitPtr addResult (float t, Shape * shape);
    //void addResult (float t, shared_ptr<IntersectHit> ih);

    //int resultCount();
    IntersectHitPtr closestResult();
    //map<float, IntersectHit> getMap();

};

#endif
