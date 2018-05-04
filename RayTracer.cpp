#include "RayTracer.h"

RayTracer::
RayTracer() {
}

RayTracer::
RayTracer(string file, shared_ptr<WindowClass> win, shared_ptr<Camera> cam) {
  window = win;
  camera = cam;
  pixelColors = make_unique<glm::vec4[]>(window->width() * window->height());
}


void
RayTracer::
computeImage() {
  glm::vec4 color;
  glm::vec3 dir = glm::normalize(camera->getDestination().xyz() - camera->getPosition().xyz());
  Ray ray = Ray(camera->getPosition().xyz(), dir);
  for(int i = 0; i < window->width(); i++) {
    for(int j = 0; j < window->height(); j++) {
      color = computePixel(ray); //matrix inverse-view?
    }
  }
}

glm::vec4 
RayTracer::
computePixel(Ray ray) {
  Collision col;
  glm::vec4 color = rayTrace(ray, col, 0);
  return color;
}

glm::vec4
RayTracer::
rayTrace(Ray ray, Collision lastCol, size_t depth) {
  if(depth >= maxDepth) { // Base case
    glm::vec4 color;//TODO
    return color;
  }
  Collision col;
  Collision firstCol;
  firstCol.S = 9999;
  for(int i = 0; i < objs.size(); i++) {
    col = objs.collide(ray);
    if(col.S >= 0) { // If there was a collision
      if(col.S < firstCol.S) { // If it was earlier than the previous best
        firstCol = col; // update first collision
      }
    }
  }
  if(firstCol.S < 9999) {
    glm::vec3 newDirection = ray.direction - 2.f * dot(ray.direction, firstCol.normal) * firstCol.normal;
    Ray reflection = Ray(firstCol.position, newDirection);
    rayTrace(reflection, depth+1);
  }
}
