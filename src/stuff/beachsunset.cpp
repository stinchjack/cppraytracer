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

      SpherePtr outersphere = scene.add<Sphere>();

      outersphere->setShift((Point){0, 0, 0});
      outersphere->setScale(60,25,60);
      outersphere->setRotate(Vector(0,1,0), 180);

      //rampColours = {Colour(1,0,0), Colour(0,1,0), Colour (1,0,1), Colour(0,0,0)};
      //outersphere->diffuse = make_shared<CircularRampTexture>(rampColours);
      outersphere->diffuse = make_shared<ImageFileTexture>("./sunset.jpeg");
      outersphere->mapping = make_shared<SphereMapping>();
      //outersphere->diffuse = make_shared<PlainTexture>(Colour (1,1,1));
      //outersphere->specular = make_shared<PlainTexture>(Colour (1,1,1));

      ShapePtr sph3, sph4, sph5, sph6;
      int flag = 0;
      Colour altColour (0,.8,0);
      for (FLOAT i =-2; i<1 ; i++) {
        for (FLOAT j =-1; j<2 ; j++) {

          flag ++;
          string num = to_string(i) + to_string(j);

           //scene.shapes["sphere3"+num] = SpherePtr();
           sph3 = scene.add<Sphere>();
           sph3->setShift((Point){(4.0f * j),(4.0f * i),0.0});
           sph3->setScale(2.0  , 2, 2);

           if (flag++ % 2 == 0) {
             sph3->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
             sph3->specular = make_shared<PlainTexture>(Colour (1,1,1));
           }
           else {
             //scene.shapes["sphere3"+num]->setDiffuse<PlainTexture>(altColour);
             sph3->diffuse = make_shared<PlainTexture>(altColour);
           }


            sph4 = scene.add<Sphere>();
            sph4->setShift((Point){1.0f + (4.0f * j),.60f + (4.0f * i),-1.0});
            sph4->setScale(2.0, 2, 2);
            if (flag++ % 2 == 0) {
              sph4->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
              sph4->specular = make_shared<PlainTexture>(Colour (1,1,1));
            }
            else {
              sph4->diffuse = make_shared<PlainTexture>(altColour);
            }

            sph5 = scene.add<Sphere>();
            sph5->setShift((Point){2.0f+ (4.0f * j),1.2f + (4.0f * i),-2.0});
            sph5->setScale(2.0, 2, 2);
            sph5->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
            sph5->specular = make_shared<PlainTexture>(Colour (1,1,1));
            if (flag++ % 2 == 0) {
              sph5->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
              sph5->specular = make_shared<PlainTexture>(Colour (1,1,1));
            }
            else {
              sph5->diffuse = make_shared<PlainTexture>(altColour);
            }


            sph6 = scene.add<Sphere>();
            sph6->setShift((Point){3.0f+ (4.0f * j),1.8f + (4.0f * i),-3.0});
            sph6->setScale(2.0, 2, 2);
            sph6->diffuse = make_shared<PlainTexture>(altColour);

            if (flag++ % 2 == 0) {
              sph6->diffuse = make_shared<PlainTexture>(Colour (0,0,0));
              sph6->specular = make_shared<PlainTexture>(Colour (1,1,1));
            }
            else {
              sph6->diffuse = make_shared<PlainTexture>(altColour);
            }
        }
      }



     //scene.add<Sphere>("sphere");
     ViewPtr v1 = scene.add<View>(30,30,28);
     v1->setOutput(output);

     scene.add<PointLight>(Colour(.4,.4,.4), (Point){-20,-20,0});
     scene.add<PointLight>(Colour(.4,.4,.4), (Point){-20,22,0});



    //v1->setAntiAlias(std::make_shared<SimpleAntiAlias> (20));
    v1->setAntiAlias(std::make_shared<EDAntiAlias> (20, .9));

    // for explicitly setting no antialas, use:
    // scene.views["view1"].setAntiAlias(nullptr);



     LightModel::processShadows  = true;

     time_point<Clock> startRender = Clock::now();

     scene.render(v1);

     time_point<Clock> end = Clock::now();
     milliseconds diff = duration_cast<milliseconds>(end - start);
     milliseconds diffRender = duration_cast<milliseconds>(end - startRender);
     std::cout << "render time: "<< diffRender.count() << "ms" << std::endl;
     std::cout << "total time: "<< diff.count() << "ms" << std::endl;

     output->makeWindow("hello world");
     output->show();

}
