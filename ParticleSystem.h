#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string.h>

using namespace std;

struct Particle { // Particle struct type made up of two glm::vec3s to store position + velocity info
  glm::vec3 position;
  glm::vec3 velocity;
  //glm::vec3 color;
  int time;
};

class ParticleSystem {
  protected:
    ////////////////////////////////////////////////////////////////////////////////
    ///Private Variables
    // Particles
    vector<Particle> data;
    int lifetime;
    // Generator variables
    float xmin, xmax, ymin, ymax, zmin, zmax;
    float angle;
    // Update variables
    float gravity;
    // Transformation variables
    glm::vec4 position; // for translation
    glm::vec4 direction; // for rotation
    glm::vec4 size; // for scale

  public:
    ///Constructors
    ParticleSystem();
    ParticleSystem(int numParticles, int _lifetime, int _gravity);
    ParticleSystem(string filename);

    ~ParticleSystem() {}


    ///Functions
    void init(int numParticles, int _lifetime, int _gravity);
    Particle genParticle();
    glm::vec3 genPosition();
    glm::vec3 genVelocity();
    void update();
    void print();

    //Getters
    const vector<Particle>& getData() {return data;}
    Particle getParticle(int i) {return data[i];}

};

#endif
