#ifndef SPHEREMAPPING_HPP
#define SPHEREMAPPING_HPP

class SphereMapping: public Mapping {
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
