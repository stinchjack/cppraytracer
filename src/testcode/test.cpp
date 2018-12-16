#include "Vector.hpp"
#include "PngOutput.hpp"
#include <stdio.h>
#include <iostream>


void testPng();

int main (int argc, char **argv) {

  Vector v ((FLOAT)0.4, (FLOAT).3, (FLOAT).2);
  cout<<"V length: "<<v.length()<<endl;

  printf("helclo!\n" );
  testPng();
  return 0;
}

void testPng() {
  PngOutput<200, 300> pic;
   pic.pixel[1][1] = Colour (.1,.2, .3);
  //pic.save ("test.png");
}
