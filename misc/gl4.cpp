// g++ gl4.cpp -lGL -lglfw -lGLEW -lglut -ggdb -o test

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>


#include <iostream>
using namespace std;

int myWidth = 240;
int myHeight = 240;
GLfloat *pixels = 0;

void printGLError () {
  GLenum error = glGetError();
  switch (error)  {
    case GL_NO_ERROR:
    cout << "No error has been recorded" << endl;
    break;

    case GL_INVALID_ENUM:
    cout << "An unacceptable value is specified for an enumerated argument" << endl;
    break;

    case GL_INVALID_VALUE:
    cout << "A numeric argument is out of range" << endl;
    break;

    case GL_INVALID_OPERATION:
    cout << "The specified operation is not allowed in the current state" << endl;
    break;

    case GL_INVALID_FRAMEBUFFER_OPERATION:
    cout << "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete" << endl;
    break;

    case GL_OUT_OF_MEMORY:
    cout << "There is not enough memory left to execute the command." << endl;
    break;

    default:
    cout << "Out of cheese error"  << endl;

  }
}


void makeBuffer(int width, int height) {

      int memSize = width * height * 3;
      pixels = new GLfloat[memSize];

      // fill buffer with 0's
      for (int i =0; i<memSize; i++) {
        pixels[i] = 0.0;
      }
}

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b ) {

  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * ((y * myWidth) + x);


  pixels[offset + 0]  = r;
  pixels[offset + 1]  = g;
  pixels[offset + 2]  = b;


}

void renderScene(void)
{

   glClear(GL_COLOR_BUFFER_BIT);
   glClearColor(0.0, 0.0, 0.0, 1.0);//clear red
   glDrawPixels(myWidth, myHeight, GL_RGB, GL_FLOAT, pixels);
    glutSwapBuffers();
}

int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(500, 500);//optional
glutInitWindowSize(800, 600); //optional
glutCreateWindow("OpenGL First Window");

makeBuffer(myWidth, myHeight);
setPixel(100, 100, 1.0, 1.0, 0.0);

glutDisplayFunc(renderScene);

glutMainLoop();

return 0;
}
