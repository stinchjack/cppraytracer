#ifndef SQUAREMAPPING_HPP
#define SQUAREMAPPING_HPP

#include "Textrure.hpp"

class SquareMapping: public Mapping {
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
