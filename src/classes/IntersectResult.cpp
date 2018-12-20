#include "IntersectResult.hpp"

IntersectHit::IntersectHit() {

}

IntersectHit::IntersectHit(Ray &ray, Shape *sh) {
  this->ray = ray;
  this->shape = sh;  
}


IntersectHit::IntersectHit(Ray &ray, Point &raw_point, Point &raw_normal, Shape *sh) {

  this->ray = ray;
  this->raw_point = raw_point;
  this->raw_normal = raw_normal;
  this->shape = sh;

}
