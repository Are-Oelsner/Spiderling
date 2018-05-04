#include "Sphere.h"

Sphere::
Sphere() {}

Sphere::
Sphere(glm::vec3 pos, float rad) {
  position = pos;
  radius = rad;
}

Collision
Sphere::
collide(Ray ray) {
  Collision col;
  glm::vec3 L = position-ray.position;
  float tc = dot(L, ray.direction);
  if(glm::length(tc) < 0.0) // No collision
    return col;
  float d = glm::sqrt((tc*tc)-(length(L)*length(L)));
  if(d > radius)
    return col;
  float t1c = glm::sqrt((radius*radius) - (d*d));
  col.S = tc - t1c;
  //t2 = tc + t1c // exit point
  col.position = ray.position + ray.direction*col.S;
  col.normal = normalize(position-col.position);
  col.material = getMaterial();
  return col;
}
