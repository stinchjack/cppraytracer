#ifndef SPHEREMAPPING_HPP
#define SPHEREMAPPING_HPP

#include "Mapping.hpp"
#include  "IntersectHit.hpp"

class SphereMapping:public Mapping {

public:
  SphereMapping();
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
