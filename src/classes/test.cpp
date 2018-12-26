#include "Vector.hpp"
#include "PngOutput.hpp"
#include <stdio.h>
#include <iostream>
#include "Scene.hpp"
#include "Sphere.hpp"
#include "SimpleAntiAlias.hpp"
#include "EDAntialias.hpp"

void testPng();

int main (int argc, char **argv) {


  testPng();
  return 0;
}

void testPng() {

   PNGOUTPUT_PTR output = PngOutputPtr(400,400);
   Scene scene;
   scene.useMultiThread = false;
   scene.shapes["sphere1"] = SpherePtr();
   scene.views["view1"] = View (5,5,3);
   scene.views["view1"].setOutput(output);
   //scene.views["view1"].setAntiAlias(std::make_shared<SimpleAntiAlias> (SimpleAntiAlias(120)));

   //scene.views["view1"].setAntiAlias(
  //std::make_shared<EDAntiAlias> (EDAntiAlias(50, 0.3)));

   scene.shapes["sphere1"]->transformation.setShift((Point){0.0,0,5});

   scene.render("view1");

   output->save ("test8.png");
}
