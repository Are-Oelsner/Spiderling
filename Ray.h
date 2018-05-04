#ifndef __RAY_H__
#define __RAY_H__

#define GLM_SWIZZLE
#include <glm/glm.hpp>
//#include <glm/gtc/swizzle.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "Vec.h"

using namespace std;

class Ray {
  public:
    /// Variables
    glm::vec3 position;
    glm::vec3 direction;

    /// Constructors
    Ray();
    Ray(glm::vec3 pos, glm::vec3 dir); 
};

#endif
