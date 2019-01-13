#include "CircularRampTexture.hpp"

#include <stdexcept>

CircularRampTexture::CircularRampTexture(vector<Colour> &colourArray) {

  if (colourArray.size<2) {
    throw std::invalid_argument( "colourArray needs at least two values" );
  }

  this->colourArray = colourArray;
  this->colourDist = 1.0 / (colourArray.size() - 1);

}

CircularRampTexture::getColour (IntersectHit &ir, shared_ptr<Mapping> map) {
  UVPair uvPair = map->getUVPair(ir);
  FLOAT   dist = sqrt((uvPair.u - 0.5) *
                      (uvPair.u - 0.5) +
                      (uvPair.v - 0.5) *
                      (uvPair.v - 0.5)) / POINT707

  int i = int((FLOAT)dist / self.colourDist);
  if (i >= (colourArray.size() - 1)) {
    i--;
  }

  FLOAT p1 = (dist / colourDist_) - i;


  return (colourArray(i)*(1.0 - p1)_ + (colourArray(i+1) * p1);

}


    def colour(self, uv_tuple):

        dist = sqrt((uv_tuple[0] - 0.5) *
                    (uv_tuple[0] - 0.5) +
                    (uv_tuple[1] - 0.5) *
                    (uv_tuple[1] - 0.5)) / self.___point707__

        i = int(math.trunc(dist / self.__colour_dist__))

        if i >= (len(self.__colour_array__) - 1):
            i = i - 1

        clr1 = self.__colour_array__[i]
        clr2 = self.__colour_array__[i + 1]

        p1 = (dist / self.__colour_dist__) - i
