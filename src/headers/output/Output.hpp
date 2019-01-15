#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <string>
#include "Float.hpp"
#include "Colour.hpp"
#include <memory>

using namespace std;

#define OUTPUT_PTR std::shared_ptr<Output>

class View;

class Output {

  protected:

    FLOAT *pixels = nullptr;

    virtual void resize(int x, int y);

    int myWidth;
    int myHeight;

  public:

    int width();
    int height();

    virtual void setPixel(int x, int y, const Colour &c);
    virtual void addPixel(int x, int y, const Colour &c);
    virtual Colour getPixel(int x, int y);
    ~Output();

};


class FileOutput: public Output {

  public:
  virtual int save(string filename) = 0;


};


#endif
