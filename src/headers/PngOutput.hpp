#ifndef PNGOUTPUT_HPP
#define PNGOUTPUT_HPP

#include "Output.hpp"
#include "Colour.hpp"

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>

#define PNG_DEBUG 3

#include <png++/png.hpp>

class PngOutput;

#define PNGOUTPUT_PTR std::shared_ptr<PngOutput>
PNGOUTPUT_PTR PngOutputPtr(unsigned size_x, unsigned size_y);

class PngOutput: public FileOutput {

public:
  PngOutput(unsigned size_x, unsigned size_y);
  int save(string filename);

};


#endif
