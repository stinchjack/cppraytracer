#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Colour.hpp"

#include <memory>


using namespace std;


class IntersectHit;
struct UVPair;


#define TEXTURE_PTR shared_ptr<Texture>

class Mapping;
class Texture {

public:
  virtual Colour getColour (IntersectHit &ir, shared_ptr<Mapping> map);
  virtual Colour getColour (IntersectHit &ir, const UVPair &uvPair) = 0;
};

class PlainTexture: public Texture {
  Colour c;

public:
  PlainTexture(const Colour &c);
  virtual Colour getColour (IntersectHit &ir, shared_ptr<Mapping> map);
  virtual Colour getColour (IntersectHit &ir, const UVPair &uvPair);
};





#endif
