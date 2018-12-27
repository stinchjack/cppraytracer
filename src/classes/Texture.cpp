#include "Texture.hpp"

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

UVPair SphereMapping::getUVPair(IntersectHit &ir) {
/*
"""
Maps an intersection result for a sphere to a UV pair.
        :return: tuple (u, v)
        :param intersect_result: the intersection result dictionary
"""
*/
/*
    p = intersect_result['raw_point']

    FLOAT radius = sqrt((p[1] * p[1]) + (p[3] * p[3])); // radius at intersect point

    if (radius == 0) {
        return (0, 0)
    }

    FLOAT x = p[1] / radius;

    if x < -1:
        x = -1
    if x > 1:
        x = 1

    a1 = math.degrees(asin(x))
    a1 = a1 + 90

    if (p[3] >= 0):
        a1 = 180 + (180 - a1)

    u = a1 / mpfr(360.0)
    if p[2] > 1: a2 = 90
    elif p[2] < -1: a2 =-90
    else:
        a2 = math.degrees(asin(p[2]))

    a2 = a2 + 90

    v = a2 / mpfr(180.0)

return (u, v)

*/
UVPair pair;
pair.u  = 0;
pair.v  = 0;
return pair;

};
