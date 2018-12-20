#include "PngOutput.hpp"
#include <iostream>


PNGOUTPUT_PTR PngOutputPtr(unsigned size_x, unsigned size_y) {
  return make_shared<PngOutput>(PngOutput(size_x, size_y));
}

PngOutput::PngOutput(unsigned size_x, unsigned size_y) {
  resize(size_x, size_y);
}

int PngOutput::save(string filename) {

  // see https://www.nongnu.org/pngpp/doc/0.2.9/

  png::image< png::rgb_pixel > pngImage(width(), height());

  //float data [width() * height() * 3];

  /*
  int i=0, j=0;
  for(
      typename std::vector<vector<Colour>>::iterator col = this->pixels.begin();
      col != this->pixels.end(); ++col) {
      for(
          typename vector<Colour>::iterator colour = col->begin();
          colour != col->end();  ++colour) {

          //pngImage[j][i] = png::rgb_pixel((*colour)[0] * 255.0, (*colour)[1] * 255.0, (*colour)[2] * 255.0);
          pngImage[j][i] = png::rgb_pixel((*colour)[0] * 255.0, (*colour)[1] * 255.0, (*colour)[2] * 255.0);
          i++;

      }
      i=0;
      j++;
  }*/



  int iWidth = width();
  int iHeight = height();

  for (int x = 0;x<iWidth;x++) {
    for (int y = 0;y<iHeight;y++) {
      Colour c= getPixel(x,y);
      pngImage[x][y] = png::rgb_pixel(c[0] * 255.0, c[1] * 255.0, c[2] * 255.0);
    }
  }



  pngImage.write(filename);

  return 0;
}
