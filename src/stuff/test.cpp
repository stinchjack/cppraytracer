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
#include "CircularRampTexture.hpp"
#include "SphereMapping.hpp"
#include "ImageFileTexture.hpp"

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
   scene.useMultiThread = true;


  /* scene.shapes["square1"] = SquarePtr(-100, 100, -100, 100);
   scene.shapes["square1"]->transformation.setShift((Point){0, 0, 10});
   //scene.shapes["sqaure1"]->transformation.setScale(1.0, 1.0 , 1.0);
   //scene.shapes["sphere1"]->transformation.setRotate(Vector(0,0,1), 45);
   scene.shapes["square1"]->diffuse = make_shared<PlainTexture>(Colour (.0,0,0));
   scene.shapes["square1"]->specular = make_shared<PlainTexture>(Colour (1,1,1));*/


  /*scene.shapes["square2"] = SquarePtr(-100, 100, -100, 100);
   scene.shapes["square2"]->transformation.setShift((Point){18, 0, 0});
   //scene.shapes["sqaure1"]->transformation.setScale(1.0, 1.0 , 1.0);
   scene.shapes["square2"]->transformation.setRotate(Vector(0,1,0), 90);
   vector<Colour> rampColours = {Colour(1,0,1), Colour(1,0,0), Colour (0,1,1), Colour (1,1,1)};
   scene.shapes["square2"]->diffuse = make_shared<CircularRampTexture>(rampColours);
   //scene.shapes["square2"]->diffuse = make_shared<PlainTexture>(Colour (.2,.0,.2));



  scene.shapes["square3"] = SquarePtr(-8, 8, -8, 8);
   scene.shapes["square3"]->transformation.setShift((Point){0, 0, 8});
   //scene.shapes["sqaure1"]->transformation.setScale(1.0, 1.0 , 1.0);
   //scene.shapes["square3"]->transformation.setRotate(Vector(0,1,0), 00);
   scene.shapes["square2"]->diffuse = make_shared<PlainTexture>(Colour (.2,.0,.2));
  //  rampColours = {Colour(1,0,0), Colour(0,1,0), Colour (1,0,1), Colour(0,0,0)};
   //scene.shapes["square3"]->diffuse = make_shared<ImageFileTexture>("./sunset.jpeg");*/




    scene.shapes["outersphere"] = SpherePtr();
    scene.shapes["outersphere"]->transformation.setShift((Point){0, 0, 0});
    scene.shapes["outersphere"]->transformation.setScale(60,25,60);
    scene.shapes["outersphere"]->transformation.setRotate(Vector(0,1,0), 180);

    //rampColours = {Colour(1,0,0), Colour(0,1,0), Colour (1,0,1), Colour(0,0,0)};
    //scene.shapes["outersphere"]->diffuse = make_shared<CircularRampTexture>(rampColours);
    scene.shapes["outersphere"]->diffuse = make_shared<ImageFileTexture>("./sunset.jpeg");
    scene.shapes["outersphere"]->mapping = make_shared<SphereMapping>();
    //scene.shapes["outersphere"]->diffuse = make_shared<PlainTexture>(Colour (1,1,1));
    //scene.shapes["square2"]->specular = make_shared<PlainTexture>(Colour (1,1,1));


    int flag = 0;
    Colour altColour (0,.8,0);
    for (FLOAT i =-2; i<1 ; i++) {
      for (FLOAT j =-1; j<2 ; j++) {
        continue;
        flag ++;
        string num = to_string(i) + to_string(j);

         scene.shapes["sphere3"+num] = SpherePtr();
         scene.shapes["sphere3"+num]->transformation.setShift((Point){(4.0f * j),(4.0f * i),0.0});
         scene.shapes["sphere3"+num]->transformation.setScale(2.0  , 2, 2);

         if (flag++ % 2 == 0) {
           scene.shapes["sphere3"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
           scene.shapes["sphere3"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
         }
         else {
           scene.shapes["sphere3"+num]->diffuse = make_shared<PlainTexture>(altColour);
         }


          scene.shapes["sphere4"+num] = SpherePtr();
          scene.shapes["sphere4"+num]->transformation.setShift((Point){1.0f + (4.0f * j),.60f + (4.0f * i),-1.0});
          scene.shapes["sphere4"+num]->transformation.setScale(2.0, 2, 2);
          if (flag++ % 2 == 0) {
            scene.shapes["sphere4"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
            scene.shapes["sphere4"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
          }
          else {
            scene.shapes["sphere4"+num]->diffuse = make_shared<PlainTexture>(altColour);
          }


          scene.shapes["sphere5"+num] = SpherePtr();
          scene.shapes["sphere5"+num]->transformation.setShift((Point){2.0f+ (4.0f * j),1.2f + (4.0f * i),-2.0});
          scene.shapes["sphere5"+num]->transformation.setScale(2.0, 2, 2);
          scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
          scene.shapes["sphere5"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
          if (flag++ % 2 == 0) {
            scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
            scene.shapes["sphere5"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
          }
          else {
            scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(altColour);
          }


          scene.shapes["sphere6"+num] = SpherePtr();
          scene.shapes["sphere6"+num]->transformation.setShift((Point){3.0f+ (4.0f * j),1.8f + (4.0f * i),-3.0});
          scene.shapes["sphere6"+num]->transformation.setScale(2.0, 2, 2);
          scene.shapes["sphere6"+num]->diffuse = make_shared<PlainTexture>(altColour);

          if (flag++ % 2 == 0) {
            scene.shapes["sphere6"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
            scene.shapes["sphere6"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
          }
          else {
            scene.shapes["sphere6"+num]->diffuse = make_shared<PlainTexture>(altColour);
          }
      }
    }



   /*scene.shapes["sphere4"] = SpherePtr();
   scene.shapes["sphere4"]->transformation.setShift((Point){-4,-2, 8});
   scene.shapes["sphere4"]->transformation.setScale(3.0, 3, 3);
   scene.shapes["sphere4"]->diffuse = make_shared<PlainTexture>(Colour (1,.5,.5));
   scene.shapes["sphere4"]->specular = make_shared<PlainTexture>(Colour (1,1,1));

   scene.shapes["sphere5"] = SpherePtr();
   scene.shapes["sphere5"]->transformation.setShift((Point){-3,-6, 8});
   scene.shapes["sphere5"]->transformation.setScale(3.0, 1, 3);
   scene.shapes["sphere5"]->diffuse = make_shared<PlainTexture>(Colour (.5,0,.5));
   scene.shapes["sphere5"]->specular = make_shared<PlainTexture>(Colour (1,1,1));*/



   scene.views["view1"] = View (30,30,28);
   scene.views["view1"].setOutput(output);
   scene.lights["pointlight1"] = make_shared<PointLight>(Colour(.4,.4,.4), (Point){-20,-20,0});

   scene.lights["pointlight2"] = make_shared<PointLight>(Colour(.4,.4,.4), (Point){-20,222,0});
   //scene.lights["pointlight3"] = make_shared<PointLight>(Colour(.3, .3, .3), (Point){20,10,-.5});

   //scene.views["view1"].setAntiAlias(std::make_shared<SimpleAntiAlias> (SimpleAntiAlias(20)));
   scene.views["view1"].setAntiAlias(std::make_shared<SimpleAntiAlias> (20));
   //scene.views["view1"].setAntiAlias(std::make_shared<EDAntiAlias> (20, .3));

   //scene.views["view1"].setAntiAlias(
  //std::make_shared<EDAntiAlias> (EDAntiAlias(50, 0.3)));


   LightModel::processShadows  = true;
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
