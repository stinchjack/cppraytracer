#include "Output.hpp"

template <int size_x, int size_y>
FLOAT Output<size_x, size_y>::width() {
  return myWidth;
}

template <int size_x, int size_y>
FLOAT Output<size_x, size_y>::height() {
  return myHeight;
}
