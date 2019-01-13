#ifndef SQUAREMAPPING_HPP
#define SQUAREMAPPING_HPP

#include "Texture.hpp"
#include "Point.hpp"

class SquareMapping: public Mapping {

public:

  SquareMapping ();
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
