#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Colour.hpp"

#include <memory>


using namespace std;


//typedef shared_ptr<IntersectHit> IntersectHitPtr;
struct UVPair;


class IntersectHit;

class Mapping;
class Texture {

public:
  virtual Colour getColour (shared_ptr<IntersectHit>  ir, shared_ptr<Mapping> map);
  virtual Colour getColour (shared_ptr<IntersectHit>  ir, const UVPair &uvPair) = 0;

};

class PlainTexture: public Texture {
  Colour c;

public:
  PlainTexture(const Colour &c);
  virtual Colour getColour (shared_ptr<IntersectHit>  ir, shared_ptr<Mapping> map);
  virtual Colour getColour (shared_ptr<IntersectHit>  ir, const UVPair &uvPair);
};





#endif
