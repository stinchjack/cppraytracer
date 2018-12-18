#include "Output.hpp"
#include <algorithm>    // std::fill

int Output::width() {
  return pixels.size();
}


int Output::height() {
    return pixels[0].size();
}

Colour Output::getPixel(unsigned int x, unsigned  int y) {
    return pixels[x][y];
}

void Output::resize(unsigned int size_x, unsigned int size_y) {
  pixels.resize(size_y);
  std::fill(pixels.begin(), pixels.end(), vector<Colour>(size_y));

}

void Output::setPixel(unsigned int x, unsigned int y, const Colour &c) {
  pixels[x][y] = c;
}
