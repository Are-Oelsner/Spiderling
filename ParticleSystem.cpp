#include "ParticleSystem.h"

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

#include <string.h>

ParticleSystem::
ParticleSystem() {
}

ParticleSystem::
ParticleSystem(string filename) {
  FILE *file = fopen(filename.c_str(), "r");
  if(file == NULL) {
    printf("Cannot open the file !\n");
    return;
  }
  glm::vec3 pos;
  glm::vec3 vel;
  glm::vec3 col;
  int life;
  float grav;

  while(true) {
    char lineHeader[256];
    int res = fscanf(file, "%s", lineHeader);
    // if end of file is reached, break
    if(res == EOF)
      break;
    if(strcmp(lineHeader, "l") == 0)
      int tmp = fscanf(file, "%u %u\n", &tmin, &tmax); // reads in lifetime  
    else if(strcmp(lineHeader, "g") == 0)
      int tmp = fscanf(file, "%f\n", &gravity); // reads in gravity  
    else if(strcmp(lineHeader, "i") == 0)
      int tmp = fscanf(file, "%f\n", &airResistance); // reads in air resistance 
    else if(strcmp(lineHeader, "w") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &wind[0], &wind[1], &wind[2]); // reads in wind vector  
    else if(strcmp(lineHeader, "n") == 0)
      int tmp = fscanf(file, "%u\n", &numParticles); // reads in number of particles  
    else if(strcmp(lineHeader, "a") == 0)
      int tmp = fscanf(file, "%f\n", &angle); // reads in angle for generation  
    else if(strcmp(lineHeader, "p") == 0)
      int tmp = fscanf(file, "%f %f %f %f %f %f\n", &xmin, &xmax, &ymin, &ymax, &zmin, &zmax); // gen cube
    else if(strcmp(lineHeader, "v") == 0)
      int tmp = fscanf(file, "%f %f\n", &vmin, &vmax); // generates initial velocity magnitude
    else if(strcmp(lineHeader, "t") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z); // translation
    else if(strcmp(lineHeader, "r") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &direction.x, &direction.y, &direction.z); // rotation
    else if(strcmp(lineHeader, "s") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &size.x, &size.y, &size.z); // scale
  }
  fclose(file);

  for(int i = 0; i < numParticles; i++) {
    data.emplace_back(genParticle());
  }
}

Particle 
ParticleSystem::
genParticle() {
  Particle p;
  p.position = genPosition(); //TODO maybe pass reference?
  p.velocity = genVelocity();
  p.maxTime  = genTime();
  p.color    = glm::vec3(.89, .35, .13);
  p.time     = 0;
  return p; //TODO return reference?
}

glm::vec3 
ParticleSystem::
genPosition() {
  uniform_real_distribution<float> xdistribution(xmin, xmax);
  uniform_real_distribution<float> ydistribution(ymin, ymax);
  uniform_real_distribution<float> zdistribution(zmin, zmax);
  return glm::vec3(xdistribution(generator), ydistribution(generator), zdistribution(generator));
}

glm::vec3 
ParticleSystem::
genVelocity() {
  uniform_real_distribution<float> vdistribution(vmin, vmax);
  uniform_real_distribution<float> rdistribution(0, angle);
  uniform_real_distribution<float> adistribution(0, 2*M_PI);
  float r = rdistribution(generator);
  float a = adistribution(generator);
  float x = r*cos(a);
  float z = r*sin(a);
  return glm::vec3(x, vdistribution(generator), z); //TODO add random direction
}

glm::vec3 
ParticleSystem::
genColor(int time) {
  float r = .89;
  float g = .35;
  float b = .13;
  if(time == 0)
    time = 1;
  time /= 2.0;
  r *= (1/(float)time);
  g *= (1/(float)time);
  b *= (1/(float)time);
  return glm::vec3(r, g, b);
}

int
ParticleSystem::
genTime() {
  uniform_real_distribution<float> tdistribution((float)tmin, (float)tmax);
  return (int)tdistribution(generator);
}

void 
ParticleSystem::
update(const vector<Repulsor> repulsors) {
  glm::vec3 netRepulsorForces(0.f, 0.f, 0.f);
  glm::vec3 dir;
  float r;
  float F;
  for(int i = 0; i < data.size(); i++) {
    if(data[i].time >= data[i].maxTime)
      data[i] = genParticle();
    else {
      for(int j = 0; j < repulsors.size(); j++) {// Get sum repulsor forces 
        // TODO add attractor if statement
        if(repulsors[j].state == 1)
          dir = data[i].position - repulsors[j].position;// TODO switch order?
        else if(repulsors[j].state == 0)
          dir = repulsors[j].position - data[i].position;// TODO switch order?
        r = length(dir);
        F = (.5 * repulsors[j].mass)/(r*r);
        netRepulsorForces += (F * normalize(dir));// TODO normalize right function?
      }
      data[i].velocity += netRepulsorForces;
      data[i].velocity[1] += gravity;
      data[i].velocity += wind;
      glm::vec3 airRes = normalize(data[i].velocity)*airResistance;
      data[i].velocity += airRes;

      data[i].position = data[i].position + data[i].velocity; //TODO include timestep TODO move to bottom?
      // TODO add if statement for exceeding a max velocity
      data[i].color = genColor(data[i].time);
      data[i].time++;
    }
  }
}

void
ParticleSystem::
draw() {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  // Translate
  glTranslatef((GLfloat) getPosition()[0], (GLfloat) getPosition()[1], (GLfloat) getPosition()[2]);
  // Rotation
  // Rotate X
  glRotatef((GLfloat) getRotation()[0], (GLfloat) 1, (GLfloat) 0,(GLfloat) 0);
  // Rotate Y
  glRotatef((GLfloat) getRotation()[1], (GLfloat) 0, (GLfloat) 1,(GLfloat) 0);
  // Rotate Z
  glRotatef((GLfloat) getRotation()[2], (GLfloat) 0, (GLfloat) 0,(GLfloat) 1);
  // Scale
  glScalef((GLfloat) getScale()[0], (GLfloat) getScale()[1], (GLfloat) getScale()[2]);
  //printData();
  glBegin(GL_POINTS);
  for(int j = 0; j < numParticles; j++) {
    glColor3f((GLfloat)data.at(j).color[0], (GLfloat)data.at(j).color[1], (GLfloat)data.at(j).color[2]);
    glVertex3f((GLfloat)data.at(j).position[0], (GLfloat)data.at(j).position[1], (GLfloat)data.at(j).position[2]);
  }
  glEnd();
  glPopMatrix();
}

void 
ParticleSystem::
print() {
  printf("#particles:\t%lu\tnumParticles:\t%u\tangle:\t%f\tgravity:\t%f\n", data.size(), numParticles, angle, gravity);
  printf("tmin:\t\t%u\ttmax:\t\t%u\tvmin:\t%f\tvmax:\t\t%f\n", tmin, tmax, vmin, vmax);
  printf("xmin:\t\t%.2f\txmax:\t\t%.2f\tymin:\t%.2f\t\tymax:\t\t%.2f\tzmin:\t%.2f\tzmax:\t%.2f\n\n", xmin, xmax, ymin, ymax, zmin, zmax);
}

void
ParticleSystem::
printData() {
  for(int i = 0; i < data.size(); i++) {
    printf("Particle %u:\n\tposition:\t%f\t%f\t%f\n\tvelocity:\t%f\t%f\t%f\n\tcolor:\t\t%f\t%f\t%f\n\tlifetime:\t%u\n", i, data[i].position[0], data[i].position[1], data[i].position[2], data[i].velocity[0], data[i].velocity[1], data[i].velocity[2], data[i].color[0], data[i].color[1], data[i].color[2], data[i].time);
  }
}
