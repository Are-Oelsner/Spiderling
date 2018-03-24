#include "ParticleSystem.h"

ParticleSystem::
ParticleSystem() {
}

ParticleSystem::
ParticleSystem(int numParticles, int _lifetime, int _gravity) {
  lifetime = _lifetime;
  gravity = _gravity;
  for(int i = 0; i < numParticles; i++) {
    data.emplace_back(genParticle());
  }
}

ParticleSystem::
ParticleSystem(string filename) {
  FILE *file = fopen(filename.c_str(), "r");
  if(file == NULL) {
    printf("Cannot open the file !\n");
    return;
  }
  int numParticles = 0;
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
      int tmp = fscanf(file, "%u\n", &life); // reads in lifetime  
    else if(strcmp(lineHeader, "g") == 0)
      int tmp = fscanf(file, "%f\n", &grav); // reads in lifetime  
    else if(strcmp(lineHeader, "n") == 0)
      int tmp = fscanf(file, "%u\n", &numParticles); // reads in lifetime  
    else if(strcmp(lineHeader, "a") == 0)
      int tmp = fscanf(file, "%f\n", &angle); // reads in lifetime  
    else if(strcmp(lineHeader, "p") == 0)
      int tmp = fscanf(file, "%f %f %f %f %f %f\n", &xmin, &xmax, &ymin, &ymax, &zmin, &zmax); // gen cube
    else if(strcmp(lineHeader, "t") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &position.x, &position.y, &position.z); // translation
    else if(strcmp(lineHeader, "r") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &direction.x, &direction.y, &direction.z); // translation
    else if(strcmp(lineHeader, "s") == 0)
      int tmp = fscanf(file, "%f %f %f\n", &size.x, &size.y, &size.z); // translation
  }
  fclose(file);
  
  lifetime = life;
  gravity = grav;
  for(int i = 0; i < numParticles; i++) {
    data.emplace_back(genParticle());
  }
}

void
ParticleSystem::
init(int numParticles, int _lifetime, int _gravity) {
  lifetime = _lifetime;
  gravity = _gravity;
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
  p.time = 0;
  return p; //TODO return reference?
}

glm::vec3 
ParticleSystem::
genPosition() {
  return glm::vec3(0., 0., 0.); //TODO randomly generate
}

glm::vec3 
ParticleSystem::
genVelocity() {
  return glm::vec3(0., 1., 0.); //TODO randomly generate
}

void 
ParticleSystem::
update() {
  for(int i = 0; i < data.size(); i++) {
    data[i].position = data[i].position + data[i].velocity; //TODO include timestep
    data[i].velocity += gravity;
  }
}

void 
ParticleSystem::
print() {
}
