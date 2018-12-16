#include "ColourPtr.hpp"

inline COLOUR_PTR colourPtr() {
  return std::make_shared <Colour> (new Colour());
}

inline COLOUR_PTR colourPtr(FLOAT r, FLOAT g, FLOAT b) {
  return std::make_shared <Colour> (new Colour(r,g,b));
}

inline COLOUR_PTR colourPtr(const Colour &c) {
  return std::make_shared <Colour> (new Colour(c));
}
