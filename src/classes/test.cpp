#include "Vector.hpp"
#include "PngOutput.hpp"
#include <stdio.h>
#include <iostream>
#include "Scene.hpp"
#include "Sphere.hpp"
#include "SimpleAntiAlias.hpp"
#include "EDAntialias.hpp"
#include "GLWindowOutput.hpp"
#include "LightModel.hpp"
#include "Square.hpp"

#include <chrono>
#include <thread>


using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
//using namespace std::literals::chrono_literals;
using std::this_thread::sleep_for;

void testPng();

int main (int argc, char **argv) {



  testPng();


  return 0;
}

void testPng() {

  time_point<Clock> start = Clock::now();

   //PNGOUTPUT_PTR output = make_shared<PngOutput>(640, 640);
   shared_ptr<GLWindowOutput> output = make_shared<GLWindowOutput>(400, 400);
   Scene scene;
   scene.useMultiThread = false;


   scene.shapes["square1"] = SquarePtr(-100, 100, -100, 100);
   scene.shapes["square1"]->transformation.setShift((Point){0, 0, 0});
   //scene.shapes["sqaure1"]->transformation.setScale(1.0, 1.0 , 1.0);
   //scene.shapes["sphere1"]->transformation.setRotate(Vector(0,0,1), 45);
   scene.shapes["square1"]->diffuse = make_shared<PlainTexture>(Colour (.2,.2,.2));
   scene.shapes["square1"]->specular = make_shared<PlainTexture>(Colour (1,1,1));


  /* scene.shapes["square2"] = SquarePtr(-1, 1, -1, 1);
   scene.shapes["square2"]->transformation.setShift((Point){0, 0, 3.5});
   //scene.shapes["sqaure1"]->transformation.setScale(1.0, 1.0 , 1.0);
   //scene.shapes["sphere1"]->transformation.setRotate(Vector(0,0,1), 45);
   scene.shapes["square2"]->diffuse = make_shared<PlainTexture>(Colour (.8,.80,0));*/




    /*scene.shapes["sphere2"] = SpherePtr();
    scene.shapes["sphere2"]->transformation.setShift((Point){0, 0, 100});
    scene.shapes["sphere2"]->transformation.setScale(1, 1, .5);
    //scene.shapes["sphere2"]->transformation.setRotate(Vector(0,0,1), 45);
    scene.shapes["sphere2"]->diffuse = make_shared<PlainTexture>(Colour (1,1,1));*/


   scene.shapes["sphere1"] = SpherePtr();
   scene.shapes["sphere1"]->transformation.setShift((Point){-3, 3, -3});
   //scene.shapes["sphere1"]->transformation.setScale(1.0, 2 , 1.0);
   //scene.shapes["sphere1"]->transformation.setRotate(Vector(0,0,1), 45);
   scene.shapes["sphere1"]->diffuse = make_shared<PlainTexture>(Colour (.8,0,0));


   /*scene.shapes["sphere3"] = SpherePtr();
   scene.shapes["sphere3"]->transformation.setShift((Point){-2,-2, 8});
   scene.shapes["sphere3"]->transformation.setScale(3.0, 3, 3);
   scene.shapes["sphere3"]->diffuse = make_shared<PlainTexture>(Colour (1,.5,1));*/



   scene.views["view1"] = View (18,18,100);
   scene.views["view1"].setOutput(output);
   scene.lights["pointlight1"] = make_shared<PointLight>(Colour(1,1,1), (Point){0,0,-6});

   scene.lights["pointlight2"] = make_shared<PointLight>(Colour(1,1,1), (Point){-3,3,0.5});

   //scene.views["view1"].setAntiAlias(std::make_shared<SimpleAntiAlias> (SimpleAntiAlias(120)));

   //scene.views["view1"].setAntiAlias(
  //std::make_shared<EDAntiAlias> (EDAntiAlias(50, 0.3)));


   //LightModel::processShadows  = false;
   scene.render("view1");

   time_point<Clock> end = Clock::now();
   milliseconds diff = duration_cast<milliseconds>(end - start);
   std::cout << diff.count() << "ms" << std::endl;

   output->makeWindow("hello world");
   output->show();

   //cout << "waitkey" << endl;
   //output->waitKey();

   //sleep(6);
}
