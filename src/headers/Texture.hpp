#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Colour.hpp"
#include "IntersectHit.hpp"
#include <memory>


using namespace std;


struct UVPair{
  FLOAT u, v;
};

//class Texture;

// typedef shared_ptr<Texture> TexturePtr;

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




class Mapping {
public:
   virtual UVPair getUVPair(IntersectHit &ir) = 0;
};

class NoMapping: public Mapping {
public:
   virtual UVPair getUVPair(IntersectHit &ir);
};


class SphereMapping: public Mapping {
  virtual UVPair getUVPair(IntersectHit &ir);
};

#endif
