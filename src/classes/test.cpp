#include "Vector.hpp"
#include "PngOutput.hpp"
#include <stdio.h>
#include <iostream>
#include "Scene.hpp"
#include "Sphere.hpp"
#include "SimpleAntiAlias.hpp"

void testPng();

int main (int argc, char **argv) {


  testPng();
  return 0;
}

void testPng() {

   PNGOUTPUT_PTR output = PngOutputPtr(200,200);
   Scene scene;
   scene.shapes["sphere1"] = SpherePtr();
   scene.views["view1"] = View (3,3,3);
   scene.views["view1"].setOutput(output);
   scene.views["view1"].setAntiAlias(std::make_shared<SimpleAntiAlias> (SimpleAntiAlias(12)));
   scene.render("view1");

   output->save ("test.png");
}
