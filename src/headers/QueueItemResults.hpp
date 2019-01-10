#ifndef QUEUEITEMRESULTS_HPP
#define QUEUEITEMRESULTS_HPP

#include <map>
#include "IntersectHit.hpp"

using namespace std;

class QueueItemResults: public map<float, IntersectHit> {

  //private:
  //map<float, IntersectHit> queueItemResults;

  public:
    void addResult (float t, const IntersectHit &ih);
    //int resultCount();
    IntersectHit closestResult();
    //map<float, IntersectHit> getMap();

};

#endif
