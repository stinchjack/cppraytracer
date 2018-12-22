#include "Output.hpp"
#include <algorithm>    // std::fill
#include <iostream>
int Output::width() {
  return pixels.size();
}


int Output::height() {
    return pixels[0].size();
}


void Output::resize(unsigned int size_x, unsigned int size_y) {
  pixels.resize(size_y);
  std::fill(pixels.begin(), pixels.end(), vector<Colour>(size_y));

  samples.resize(size_y);
  std::fill(samples.begin(), samples.end(), vector<int>(size_y));

}

int Output::getSampleCount (unsigned int x, unsigned int y) {
  return samples [x][y];
}

Colour Output::getPixel(unsigned int x, unsigned  int y) {

  return pixels[x][y];
}

void Output::addPixel(unsigned int x, unsigned int y, const Colour &c) {
  pixels[x][y]+=c;

}
void Output::setPixel(unsigned int x, unsigned int y, const Colour &c) {
  pixels[x][y] = c;
}
