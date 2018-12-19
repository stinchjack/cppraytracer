#include "IntersectResult.hpp"

IntersectHit::IntersectHit() {
  hit = true;
}

IntersectHit::IntersectHit(Ray &ray) {
  hit = true;
  this->ray = ray;
}


IntersectHit::IntersectHit(Ray &ray, Point &raw_point, Point &raw_normal) {

  hit = true;
  this->ray = ray;
  this->raw_point = raw_point;
  this->raw_normal = raw_normal;

}
