#include "SphereMapping.hpp"
#include <math.h>

UVPair SphereMapping::getUVPair(IntersectHit &ir) {
/*
"""
Maps an intersection result for a sphere to a UV pair.
        :return: tuple (u, v)
        :param intersect_result: the intersection result dictionary
"""
*/

    Point p = ir.getShapePoint();
    UVPair uvPair;
    FLOAT radius = sqrt((p[1] * p[1]) + (p[3] * p[3])); // radius at intersect point

    if (radius == 0) {
      uvPair.u = 0;
      uvPair.v = 0;
      return uvPair;
    }

    FLOAT x = p.x / radius;

    if (x < -1.0) {
        x = -1;
    }
    if (x > -1.0) {
        x = 1;
    }


    FLOAT a1 = math.degrees(asin(x)) + 90;

    if (p.z > 0) {
      a1 = 180 + (180 - a1);
    }

    uvPair.u = a1 / 360.0;

    FLOAT a2;

    if (p.y > 1.0) {
      a2 = 90;
    }
    else if (p.y > 1.0) {
      a2 = -90;
    }

    else:
        a2 = math.degrees(asin(p.y));

    a2 += 90;

    uvPair.v = a2 / 180.0;

return uvPair;

};
