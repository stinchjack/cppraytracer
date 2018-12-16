/* e.g.
  ** shared pointer to new Colour object with 0,0,0
  ColourPtr diffuse = colourPtr();
  or
  ColourPtr diffuse();


  ** shared pointer to new Colour object with specifed values
  ColourPtr diffuse2 = colourPtr(0.1, 0.2, 0.3);
  or
  ColourPtr (0.1, 0.2, 0.3);

  ColourPtr diffuse3 = colourPtr(dissfuse2);
  or
  ColourPtr (dissfuse2);

*/

#ifndef COLOURPTR_HDR
#define COLOURPTR_HDR

#define COLOUR_PTR std::shared_ptr<Colour>

#include "Colour.hpp"
#include "Float.hpp"
#include <memory>

inline COLOUR_PTR colourPtr();
inline COLOUR_PTR colourPtr(FLOAT r, FLOAT g, FLOAT b);
inline COLOUR_PTR colourPtr(const Colour &c);


#endif
