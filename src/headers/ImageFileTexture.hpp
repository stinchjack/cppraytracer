#ifndef IMAGEFILETEXTURE_HPP
#define IMAGEFILETEXTURE_HPP

#include "Magick++.h"
#include <iostream>
#include <string>
#include "Texture.hpp"
using namespace std;
using namespace Magick;


class ImageFileTexture: public Texture{
private:

  Magick::Image image;
  int width, height;
  Magick::PixelPacket *pixels;


public:
  ImageFileTexture(string filename);
  virtual Colour getColour (IntersectHit &ir, const UVPair &uvPair);

};

#endif
