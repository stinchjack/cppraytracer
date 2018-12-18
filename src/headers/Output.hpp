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

  friend class View;

  protected:
    vector<vector<Colour>> pixels;
    void resize(unsigned int x, unsigned int y);

  public:

    int width();
    int height();

    void setPixel(unsigned int x, unsigned int y, const Colour &c);
    Colour getPixel(unsigned int x, unsigned int y);

};


class FileOutput: public Output {

  public:
  virtual int save(string filename) = 0;


};


#endif
