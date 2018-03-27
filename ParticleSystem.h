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

using namespace std;

struct Particle { // Particle struct type made up of two glm::vec3s to store position + velocity info
  glm::vec3 position;
  glm::vec3 velocity;
  glm::vec3 color;
  int time;
  int maxTime;
};

  static default_random_engine generator;
//uniform_real_distribution<float>* xdistribution;
//uniform_real_distribution<float>* ydistribution;
//uniform_real_distribution<float>* zdistribution;

//uniform_real_distribution<float>* vdistribution;

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
    // Transformation variables
    glm::vec4 position; // for translation
    glm::vec4 direction; // for rotation
    glm::vec4 size; // for scale

  public:
    ///Constructors
    ParticleSystem();
    ParticleSystem(string filename);

    ~ParticleSystem() {}


    ///Functions
    Particle genParticle();
    glm::vec3 genPosition();
    glm::vec3 genVelocity();
    glm::vec3 genColor(int time);

    float getPosition(int i) {return position[i];}
    float getRotation(int i) {return direction[i];}
    float getScale(int i) {return size[i];}

    int genTime();
    void update();
    void draw();
    void print();
    void printData();

    //Getters
    const vector<Particle>* getData() {return &data;}
    const Particle* getParticle(int i) {return &data.at(i);}
    float pos(int i, int j) {return data.at(i).position[j];}
    int getNumParticles() {return numParticles;}

};

#endif
