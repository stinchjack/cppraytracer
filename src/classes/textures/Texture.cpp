#include "Texture.hpp"
#include "IntersectHit.hpp"
#include "Mapping.hpp"

Colour Texture::getColour (IntersectHitPtr ir, shared_ptr<Mapping> map) {
  return getColour (ir, map->getUVPair(ir));
}


PlainTexture::PlainTexture(const Colour &c) {
  this->c = c;
}

Colour PlainTexture::getColour (IntersectHitPtr ir, shared_ptr<Mapping> map) {
  return c;
}

Colour PlainTexture::getColour (IntersectHitPtr ir, const UVPair &uvPair) {
  return c;
}

UVPair NoMapping::getUVPair(IntersectHitPtr ir) {
  UVPair pair;
  pair.u  = 0;
  pair.v  = 0;
  return pair;
}
