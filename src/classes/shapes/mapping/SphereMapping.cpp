#include "SphereMapping.hpp"
#include <math.h>
#include "Point.hpp"

SphereMapping::SphereMapping () {};

UVPair SphereMapping::getUVPair(IntersectHitPtr ir) {
/*

Maps an intersection result for a sphere to a UV pair.
        :return: tuple (u, v)
        :param intersect_result: the intersection result dictionary

*/

    Point p = ir->getShapePoint();
    UVPair uvPair;
    FLOAT radius = sqrt((p.x * p.x) + (p.z * p.z)); // radius at intersect point

    if (radius == 0) {
      uvPair.u = 0;
      uvPair.v = 0;
      return uvPair;
    }

    FLOAT x = p.x / radius;

    if (x < -1.0) {
        x = -1;
    }
    if (x > 1.0) {
        x = 1;
    }

    FLOAT a1 =  asin(x) + 1.5708;


    if (p.z > 0) {
      a1 = M_PI + (M_PI - a1);
    }

    uvPair.u = a1 / 6.28319;

    FLOAT a2;

    if (p.y > 1.0) {
      a2 = 1.5708;
    }
    else if (p.y < -1.0) {
      a2 = -1.5708;
    }
    else {
      a2 = asin(p.y);
    }
    a2 += 1.5708;

    uvPair.v = a2 / M_PI;


    /*FLOAT a1 = ((180.0/M_PI) * asin(x)) + 90;

    if (p.z > 0) {
      a1 = 180.0 + (180.0 - a1);
    }

    uvPair.u = a1 / 360.0;

    FLOAT a2;

    if (p.y > 1.0) {
      a2 = 90.0;
    }
    else if (p.y < -1.0) {
      a2 = -90.0;
    }

    else {
        a2 = ((180.0/M_PI) * asin(p.y));
    }
    a2 += 90.0;

    uvPair.v = a2 / 180.0;*/

return uvPair;

};
