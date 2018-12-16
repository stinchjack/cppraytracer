#ifndef PNGOUTPUT_HPP
#define PNGOUTPUT_HPP

#include "Output.cpp"

#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define PNG_DEBUG 3

#include <png.h>


template <int size_x, int size_y>
class PngOutput: public FileOutput <size_x, size_y> {

public:

  int save(string filename);



};


template <int size_x, int size_y>
int PngOutput<size_x,size_y>::save(string filename) {

  float data [size_x * size_y];

  //foreach row
  int row=0;
  for(typename std::array<FLOAT,size_y>::iterator it = this->pixel.begin(); it != this->pixel.end(); ++it) {

    cout<<row++<<endl;
  }

  return 0;
}


#endif
