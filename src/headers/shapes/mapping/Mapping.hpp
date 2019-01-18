
#ifndef MAPPING_HPP
#define MAPPING_HPP

#include "IntersectHit.hpp"

struct UVPair{
  FLOAT u, v;
};


class Mapping {
public:
   virtual UVPair getUVPair(IntersectHitPtr ir) = 0;
};

class NoMapping: public Mapping {
public:
   virtual UVPair getUVPair(IntersectHitPtr ir);
};

#endif
