#ifndef __RAY_H__
#define __RAY_H__

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Vec.h"

using namespace std;

class Ray {
  private:
    /// Private Variables
    glm::vec3 position;
    glm::vec3 origin; 
    glm::vec3 direction;
};

#endif
