#ifndef SIMPLEANTIALIAS_HPP
#define SIMPLEANTIALIAS_HPP

#include "Antialias.hpp"

class SimpleAntiAlias:public Antialias{


  public:
  SimpleAntiAlias(unsigned int samples);

  virtual Colour antialias (
        ViewQueueItem &queueItem, View *view, Scene *scene);
};



#endif
