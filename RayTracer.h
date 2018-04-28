#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include "Ray.h"
#include "Collision.h"
#include "glm"

using namespace std;

class RayTracer {
  private:
    ///Private Variables
    unique_ptr<glm::vec4[]> pixelColors = make_unique<glm::vec4[]>(g_width*g_height); // 4 colors for alpha channel
    // can access with
    // glm::vec4 color = pixelColors[i*g_width + j] // access to pixelColors[i][j]

  public:
    /// Constructors
    // Default Constructor
    RayTracer();


};

#endif
