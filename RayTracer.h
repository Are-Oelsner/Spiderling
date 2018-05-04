#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

#include "Ray.h"
#include "WindowClass.h"
#include "Camera.h"
#include "Obj.h"
#include "Light.h"
#include <memory>
#include <vector>

using namespace std;

class RayTracer {
  private:
    ///Private Variables
    shared_ptr<WindowClass> window;
    shared_ptr<Camera> camera;
    unique_ptr<glm::vec4[]> pixelColors;// = make_unique<glm::vec4[]>(g_width*g_height); 
    size_t maxDepth = 10;

    /// Objects
    // Lights
    vector<unique_ptr<Light>> lights;
    // Objects <spheres and groundplane>
    vector<shared_ptr<Obj>> objs;

    // can access with
    // glm::vec4 color = pixelColors[i*g_width + j] // access to pixelColors[i][j]

  public:
    /// Constructors
    // Default Constructor
    RayTracer();

    RayTracer(string file, shared_ptr<WindowClass> win, shared_ptr<Camera> cam);

    /// Functions
    void computeImage();
    glm::vec4 computePixel(Ray ray);
    void draw();
    glm::vec4 rayTrace(Ray ray, Collision col, size_t maxDepth); // Returns pixel color
    glm::vec4 getPixel(int i, int j) {return pixelColors[i * window->width() + j];}
    void setPixel(int i, int j, glm::vec4 color) {pixelColors[i * window->width() + j] = color;}


};

#endif
