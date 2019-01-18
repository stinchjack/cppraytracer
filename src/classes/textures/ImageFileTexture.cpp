
#include "ImageFileTexture.hpp"

ImageFileTexture::ImageFileTexture(string filename){
  InitializeMagick("");
  image.read(filename);
  width = image.columns();
  height = image.rows();
  pixels = image.getPixels(0, 0, width, height);
}

Colour ImageFileTexture::getColour (IntersectHitPtr ir, const UVPair &uvPair) {

  int row = (1.0 - uvPair.v) * (FLOAT) height;
  int column = uvPair.u * (FLOAT) width;
  Magick::ColorRGB px = image.pixelColor( column, row );

  return Colour (px.red(), px.green(), px.blue());

  /*int offset = width * xpos + ypos;

  FLOAT red = pixels[offset];
  FLOAT red = pixels[offset + 1];
  FLOAT red = pixels[offset + 2];
*/
}
