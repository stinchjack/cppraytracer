#include "PngOutput.hpp"
#include <iostream>


PngOutput::PngOutput(int size_x, int size_y) {
  resize(size_x, size_y);
}

int PngOutput::save(string filename) {

  // see https://www.nongnu.org/pngpp/doc/0.2.9/

  if (!pixels) {
    return -1;
  }

  png::image< png::rgb_pixel > pngImage(width(), height());


  int iWidth = width();
  int iHeight = height();

  for (int x = 0;x<iWidth;x++) {
    for (int y = 0;y<iHeight;y++) {

      int offset = ((x * iHeight) + y) * 3;

      FLOAT r,g,b;
      r = pixels[offset];
      g = pixels[offset + 1];
      b = pixels[offset + 2];

      pngImage[x][y] = png::rgb_pixel(r * 255, g * 255, b * 255);
      //pngImage[y][x] = png::rgb_pixel(255, 255, 123);

    }
  }



  pngImage.write(filename);

  return 0;
}
