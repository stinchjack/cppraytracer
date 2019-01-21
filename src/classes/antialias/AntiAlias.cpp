#include "Antialias.hpp"
#include "EDAntialias.hpp"
#include "View.hpp"
#include <algorithm>
#include <iostream>

using namespace std;



void Antialias::setOutput (shared_ptr<Output> output) {
  this->output = output;
}

void Antialias::setRange (float rangeX,float  rangeY) {
  this->rangeX = rangeX;
  this->rangeY = rangeY;
}



int Antialias::getSamples(int screenX, int screenY) {
  return samples;
}
