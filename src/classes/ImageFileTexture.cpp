
#include "ImageFileTexture.hpp"

ImageFileTexture(string filename){
  image.read("bar.jpg");
  width = img.columns();
  height = img.rows();
  //pixels = img.getPixels(0, 0, w, h);
}
virtual Colour getColour (IntersectHit &ir, const UVPair &uvPair) {

  int row = u * width;
  int column = v * height;
  Magick::ColorRGB px = img.pixelColor( column, row );

  return Colour (px.red(), px.green(), px.blue());

  /*int offset = width * xpos + ypos;

  FLOAT red = pixels[offset];
  FLOAT red = pixels[offset + 1];
  FLOAT red = pixels[offset + 2];
*/
}
