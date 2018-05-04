#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Obj.h"

class Sphere : public Obj {
  private:
    ///Variables
    float radius = 3;

  public:
    /// Contructors
    Sphere();
    Sphere(glm::vec3 pos, float rad);
    ~Sphere() {};

    /// Functions
    // Getters
    const float getRadius() {return radius;}
    Collision collide(Ray ray);
};

#endif
