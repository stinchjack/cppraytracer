#include "GLWindowOutput.hpp"




// see https://stackoverflow.com/questions/9110487/undefined-reference-to-a-static-member
GLWindowOutput *GLWindowOutput::ptr;

GLWindowOutput::GLWindowOutput(int size_x, int size_y) {
  resize(size_x, size_y);
}

void GLWindowOutput::resize(int size_x, int size_y) {


  myWidth = size_x;
  myHeight = size_y;
  int memSize = size_x * size_y * 3;
  if (pixels) {
    delete[] pixels;
  }
  pixels = new GLfloat[memSize];

  for (int i=0; i<memSize; i++) {
    pixels[i] = 0.0;
  }


}


void GLWindowOutput::addPixel(int x, int y, const Colour &c) {

  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * (y * myWidth + x);

  pixels[offset + 0]  += c.r;
  pixels[offset + 1]  += c.g;
  pixels[offset + 2]  += c.b;




}

void GLWindowOutput::setPixel(int x, int y, const Colour &c) {
  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * ((y * myWidth) + x);

  pixels[offset + 0]  = 1.0;
  pixels[offset + 1]  = 1.0;
  pixels[offset + 2]  = 0;


}


void GLWindowOutput::show() {

  cout <<"GLWindowOutput::show()" <<endl;

  ptr = this;
  GLWindowOutput::showImage();
  ptr = nullptr;
}

void GLWindowOutput::showImage() {

  glClear(GL_COLOR_BUFFER_BIT);
  //glClearColor(0.0, 0.0, 0.0, 1.0);//clear red
  glDrawPixels(ptr->myWidth, ptr->myHeight, GL_RGB,
    GL_FLOAT, ptr->pixels);
  glutSwapBuffers();
  glutMainLoop();

}


int GLWindowOutput::makeWindow(const char *title) {

    char *dummyArgs[1];
    char dummyExecName[] = "execuatable_name";
    dummyArgs[0] = dummyExecName;
    int argc = 1;

    glutInit(&argc, dummyArgs);
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);//optional
    glutInitWindowSize(myHeight, myWidth); //optional
    glutCreateWindow(title);
    glutDisplayFunc(GLWindowOutput::showImage);
    return 0;
}
