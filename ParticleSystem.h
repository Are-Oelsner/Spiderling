#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__

// GL
#if   defined(OSX) 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glx.h>
#endif

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string.h>
#include <random>
#include <math.h>

#define G 6.674e-11 // Defines gravitational constant

using namespace std;

struct Particle { // Particle struct type made up of two glm::vec3s to store position + velocity info
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 color;
  int time;
  int maxTime;
};

struct Repulsor { // Repulsor/Attractor struct
  glm::vec3 position;
  float mass;
  int state; // >0 for repulsor, <=0 for attractor state 
};


static default_random_engine generator;

class ParticleSystem {
  protected:
    ////////////////////////////////////////////////////////////////////////////////
    ///Private Variables
    // Particles
    vector<Particle> data;
    int numParticles = 0;
    int tmin, tmax;
    // Generator variables
    float xmin, xmax, ymin, ymax, zmin, zmax, vmin, vmax;
    float angle;
    // Update variables
    float gravity;
    float airResistance;
    glm::vec3 wind;
    // Transformation variables
    glm::vec4 position; // for translation
    glm::vec4 direction; // for rotation
    glm::vec4 size; // for scale

  public:
    ///Constructors
    ParticleSystem();
    ParticleSystem(string filename);

    ///Funtions
    glm::vec4 getPosition() {return position;}
    glm::vec4 getRotation() {return direction;}
    glm::vec4 getScale() {return size;}

    void update(const vector<Repulsor> repulsors);
    void draw();
    void print();
    void printData();

    //Getters
    const vector<Particle>& getData() {return data;}
    const Particle& getParticle(int i) {return data[i];}
    float pos(int i, int j) {return data[i].position[j];}
    int getNumParticles() {return numParticles;}

  private:
    ///Private Functions
    Particle genParticle();
    glm::vec3 genPosition();
    glm::vec3 genVelocity();
    glm::vec3 genColor(int time);
    int genTime();

};

#endif
