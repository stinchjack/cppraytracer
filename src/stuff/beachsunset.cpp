#include "RT.hpp"

#include <stdio.h>
#include <iostream>

#include <chrono>
#include <thread>


using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
//using namespace std::literals::chrono_literals;
using std::this_thread::sleep_for;


void sunset() {


    time_point<Clock> start = Clock::now();

     //PNGOUTPUT_PTR output = make_shared<PngOutput>(640, 640);
     shared_ptr<GLWindowOutput> output = make_shared<GLWindowOutput>(400, 400);
     Scene scene;

     #ifdef DEBUG
     scene.useMultiThread = false;
     #else
     scene.useMultiThread = true;
     #endif




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




      //scene.shapes["outersphere"] = SpherePtr();

      scene.add<Sphere>("outersphere");

      scene.shapes["outersphere"]->setShift((Point){0, 0, 0});
      scene.shapes["outersphere"]->setScale(60,25,60);
      scene.shapes["outersphere"]->setRotate(Vector(0,1,0), 180);

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

          flag ++;
          string num = to_string(i) + to_string(j);

           //scene.shapes["sphere3"+num] = SpherePtr();
           scene.add<Sphere>("sphere3"+num);
           scene.shapes["sphere3"+num]->setShift((Point){(4.0f * j),(4.0f * i),0.0});
           scene.shapes["sphere3"+num]->setScale(2.0  , 2, 2);

           if (flag++ % 2 == 0) {
             scene.shapes["sphere3"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
             scene.shapes["sphere3"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
           }
           else {
             //scene.shapes["sphere3"+num]->setDiffuse<PlainTexture>(altColour);
             scene.shapes["sphere3"+num]->diffuse = make_shared<PlainTexture>(altColour);
           }


            scene.add<Sphere>("sphere4"+num);
            scene.shapes["sphere4"+num]->setShift((Point){1.0f + (4.0f * j),.60f + (4.0f * i),-1.0});
            scene.shapes["sphere4"+num]->setScale(2.0, 2, 2);
            if (flag++ % 2 == 0) {
              scene.shapes["sphere4"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
              scene.shapes["sphere4"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
            }
            else {
              scene.shapes["sphere4"+num]->diffuse = make_shared<PlainTexture>(altColour);
            }

            scene.add<Sphere>("sphere5"+num);
            scene.shapes["sphere5"+num]->setShift((Point){2.0f+ (4.0f * j),1.2f + (4.0f * i),-2.0});
            scene.shapes["sphere5"+num]->setScale(2.0, 2, 2);
            scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
            scene.shapes["sphere5"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
            if (flag++ % 2 == 0) {
              scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
              scene.shapes["sphere5"+num]->specular = make_shared<PlainTexture>(Colour (1,1,1));
            }
            else {
              scene.shapes["sphere5"+num]->diffuse = make_shared<PlainTexture>(altColour);
            }


            scene.add<Sphere>("sphere6"+num);
            scene.shapes["sphere6"+num]->setShift((Point){3.0f+ (4.0f * j),1.8f + (4.0f * i),-3.0});
            scene.shapes["sphere6"+num]->setScale(2.0, 2, 2);
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



     scene.add<Sphere>("sphere");
     scene.add<View>("View1", 30,30,28);
     scene.views["View1"]->setOutput(output);

     scene.add<PointLight>("pointlight", Colour(.4,.4,.4), (Point){-20,-20,0});
     scene.add<PointLight>("pointlight2", Colour(.4,.4,.4), (Point){-20,22,0});



    //scene.views["View1"]->setAntiAlias(std::make_shared<SimpleAntiAlias> (20));
     scene.views["View1"]->setAntiAlias(std::make_shared<EDAntiAlias> (25, .9));

    // for explicitly setting no antialas, use:
    // scene.views["view1"].setAntiAlias(nullptr);



     LightModel::processShadows  = true;
     scene.render("View1");

     time_point<Clock> end = Clock::now();
     milliseconds diff = duration_cast<milliseconds>(end - start);
     std::cout << diff.count() << "ms" << std::endl;

     output->makeWindow("hello world");
     output->show();


}
