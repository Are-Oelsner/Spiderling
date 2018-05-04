#include "GroundPlane.h"

Collision
GroundPlane::
collide(Ray ray) {
  Collision col;
  float denom = dot(normalize(normal), normalize(ray.direction));
  if(denom <= 1e-6)
    return col;
  glm::vec3 p0l0 = normalize(position) - ray.position;//normalize position?
  float t = dot(p0l0, normalize(normal))/denom;
  if(t < 0)
    return col;
  col.S = t;
  col.position = ray.position + t * ray.direction;
  col.normal = normal;
  col.material = material;
  return col;
}
