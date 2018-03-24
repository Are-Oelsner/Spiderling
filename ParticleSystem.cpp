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
