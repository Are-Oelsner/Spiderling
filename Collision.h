#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Ray.h"
#include "Material.h"
#include <memory>


using namespace std;

class Collision {
  public:
    /// Variables
    glm::vec3 position; // Position of collision
    glm::vec3 normal;   // Normal at position
    float S;            // S value, distance along ray to collision
    shared_ptr<Material> material;      // Material of collision object

    /// Constructor
    Collision();
};

#endif
