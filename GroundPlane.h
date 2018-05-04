#ifndef __GROUNDPLANE_H__
#define __GROUNDPLANE_H__

#include "Obj.h"

using namespace std;

class GroundPlane : public Obj {
  private:
    /// Private Variables
    glm::vec3 normal = glm::vec3(0.f, 1.f, 0.f);

  public:
    ~GroundPlane() {}

    /// Functions
    Collision collide(Ray ray); 
};

#endif
