#ifndef SPHEREMAPPING_HPP
#define SPHEREMAPPING_HPP

#include "Texture.hpp"
#include  "IntersectHit.hpp"

class SphereMapping:public Mapping {
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
