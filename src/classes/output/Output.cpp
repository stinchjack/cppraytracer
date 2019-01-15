#include "Output.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

int Output::width() {
  return myWidth;
}


int Output::height() {
  return myHeight;
}


void Output::resize(int size_x, int size_y) {


  myWidth = size_x;
  myHeight = size_y;
  int memSize = size_x * size_y * 3;
  if (pixels) {
    delete[] pixels;
  }
  pixels = new FLOAT[memSize];

  //memset(pixels, 0, memSize * sizeof(FLOAT));
  //cout << "sizeof(*pixels)" << sizeof(*pixels) <<endl;
  for (int i=0; i<memSize; i++) { pixels[i] = 0.0;}


}


Colour Output::getPixel(int x, int y) {
  if (!pixels) {
    return Colour(0,0,0);
  }

  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * ((y * myWidth) + x);

  return Colour(pixels[offset + 0], pixels[offset + 1], pixels[offset + 2]);
}



void Output::addPixel(int x, int y, const Colour &c) {

  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * (y * myWidth + x);

  pixels[offset + 0]  += c.r;
  pixels[offset + 1]  += c.g;
  pixels[offset + 2]  += c.b;




}
void Output::setPixel(int x, int y, const Colour &c) {
  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * ((y * myWidth) + x);

  pixels[offset + 0]  = 1.0;
  pixels[offset + 1]  = 1.0;
  pixels[offset + 2]  = 0;


}

Output::~Output() {
  if (pixels) {
    delete[] pixels;
    pixels = nullptr;
  }
}
