// see http://www.opengl-tutorial.org/beginners-tutorials/tutorial-1-opening-a-window/

// compile using
// g++ opengltest.cpp -lGL -lglfw -lGLEW -lglut -o test

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
//using namespace glm;

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
        pixels[i] = 0.5;
      }
}

void setPixel(int x, int y, GLfloat r, GLfloat g, GLfloat b ) {
  return;
  if (!pixels) {
    return;
  }
  int offset = ((x * myHeight) + y) * 3;
  offset = 3 * ((y * myWidth) + x);


  pixels[offset + 0]  = 1;
  pixels[offset + 1]  = 1;
  pixels[offset + 2]  = 1;


}


int main(){


    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    //glfwWindowHint(GLFW_SAMPLES, 1); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3

    cout << "error 0" <<endl;
    printGLError ();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    cout << "error 1" <<endl;
    printGLError ();


    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(myWidth, myHeight, "Tutorial 01", NULL, NULL);


    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW

    cout << "error 2a" <<endl;
    printGLError ();


    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    cout << "error 2b" <<endl;
    printGLError ();

    // Ensure we can capture the escape key being pressed below
    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


    /****/


    makeBuffer(myWidth, myHeight);
    setPixel(10, 10, 1, 1, 1);


    /***/

    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    glClear( GL_COLOR_BUFFER_BIT );

    // Draw nothing, see you in tutorial 2 !

    glEnd();
    cout << "error 3z" <<endl;
    printGLError ();

    glRasterPos2i(0,0);
    cout << "error 3" <<endl;
    printGLError ();


    glBindBuffer(GL_PIXEL_PACK_BUFFER, 0); /* unbind the PBO */
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0); /* unbind the PBO */

    cout << "error 3a" <<endl;
    printGLError ();


        glFlush();
        glfwSwapBuffers(window);

    glDrawPixels(myWidth, myHeight, GL_RGB, GL_FLOAT, pixels);
    cout << "error 4" <<endl;
    printGLError ();


    //glfwPollEvents()

    // Swap buffers
    //glfwSwapBuffers(window);
    glfwPollEvents();

    // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
}
