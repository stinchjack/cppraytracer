#include "CircularRampTexture.hpp"

#include <stdexcept>
#include <math.h>

CircularRampTexture::CircularRampTexture(vector<Colour> &colourArray) {

  if (colourArray.size() < 2) {
    throw std::invalid_argument( "colourArray needs at least two values" );
  }

  this->colourArray = colourArray;
  this->colourDist = 1.0 / (colourArray.size() - 1);

}

Colour CircularRampTexture::getColour (IntersectHitPtr ir, const UVPair &uvPair) {
  FLOAT   dist = sqrt((uvPair.u - 0.5) *
                      (uvPair.u - 0.5) +
                      (uvPair.v - 0.5) *
                      (uvPair.v - 0.5)) / POINT707;

  unsigned int i = int((FLOAT)dist / colourDist);
  if (i >= (colourArray.size() - 1)) {
    i--;
  }

  FLOAT p1 = (dist / colourDist) - i;
  return colourArray[i] * (1.0 - p1) + (colourArray[i + 1] * p1);

}
