#include "Texture.hpp"
#include "IntersectHit.hpp"

Colour Texture::getColour (IntersectHit &ir, shared_ptr<Mapping> map) {
  return getColour (ir, map->getUVPair(ir));
}


PlainTexture::PlainTexture(const Colour &c) {
  this->c = c;
}

Colour PlainTexture::getColour (IntersectHit &ir, shared_ptr<Mapping> map) {
  return c;
}

Colour PlainTexture::getColour (IntersectHit &ir, const UVPair &uvPair) {
  return c;
}

UVPair NoMapping::getUVPair(IntersectHit &ir) {
  UVPair pair;
  pair.u  = 0;
  pair.v  = 0;
  return pair;
}
