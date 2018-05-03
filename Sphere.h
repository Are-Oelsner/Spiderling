#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <glm/vec4.hpp>

class Sphere {
  public:
    ///Variables
    glm::vec4 position;
    float radius = 1;

    Sphere();
    Sphere(glm::vec4 pos, float rad);
  //public ?void? collision(?);
};

#endif
