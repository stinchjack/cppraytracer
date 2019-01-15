#ifndef GLWINDOWOUTPUT_HPP
#define GLWINDOWOUTPUT_HPP

#include "Output.hpp"
#include "Colour.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstring>

// see http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

// compile using
// g++ opengltest.cpp -lGL -lglfw -lGLEW -lglut -o test

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>


#include <GL/gl.h>
// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
//using namespace glm;

#include <iostream>

class GLWindowOutput: public Output {

private:
  GLFWwindow* window;
  GLfloat *pixels = nullptr;

public:
  static GLWindowOutput *ptr;

  GLWindowOutput(int size_x, int size_y);
  void resize(int size_x, int size_y);
  int makeWindow(const char *title);
  virtual void setPixel(int x, int y, const Colour &c);
  virtual void addPixel(int x, int y, const Colour &c);
  virtual Colour getPixel(int x, int y);
  static void showImage();
  void show();

};



#endif
