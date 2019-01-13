#ifndef CIRCULARRAMPTEXTURE_HPP
#define CIRCULARRAMPTEXTURE_HPP
#include <vector>
#include "Texture.hpp"

#define POINT707 .707106781187

class CircularRampTexture: public Texture{
private:

  vector<Colour> colourArray;
  FLOAT colourDist;

public:
  CircularRampTexture(vector<Colour> &colourArray);
  Colour getColour (IntersectHit &ir, shared_ptr<Mapping> map);

};

#endif
