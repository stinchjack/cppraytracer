#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <array>
#include <string>
#include "Float.hpp"
#include "Colour.hpp"

using namespace std;

template <int size_x, int size_y>
class Output {

  protected:
    int myWidth = size_x;
    int myHeight = size_y;

  public:
    std::array<std::array<Colour,size_y>, size_x> pixel;

    FLOAT width();
    FLOAT height();

};

template <int size_x, int size_y>
class FileOutput: public Output <size_x, size_y> {

  public:
  virtual int save(string filename) = 0;


};


#endif
