#include "Light.h"

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
#include <iostream>
#include <glm/glm.hpp>

// Default Constructor
Light::
Light() {
  position = glm::vec4(0.f, 0.f, 100.f, 0.f); // Directional default behind camera
}

Light::
Light(string input, unsigned int lightNumber) {
  char* data = (char*)input.c_str();
  parseInput(data);
  lightNum = lightNumber;
}

void
Light::
draw() {
  glPushMatrix();
  // Translation
  glTranslatef((GLfloat) getTranslation()[0], (GLfloat)
      getTranslation()[1], (GLfloat) getTranslation()[2]);
  // Rotation
  // Rotate X
  glRotatef((GLfloat) getRotation()[0], (GLfloat) 1, (GLfloat) 0,(GLfloat) 0);
  // Rotate Y
  glRotatef((GLfloat) getRotation()[1], (GLfloat) 0, (GLfloat) 1,(GLfloat) 0);
  // Rotate Z
  glRotatef((GLfloat) getRotation()[2], (GLfloat) 0, (GLfloat) 0,(GLfloat) 1);
  // Scale 
  glScalef((GLfloat) getScale()[0], (GLfloat) getScale()[1],
      (GLfloat) getScale()[2]);

  // TODO old light stuff
  //static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
  //static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  //static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  glEnable(GL_LIGHTING);
  //find glLight_0 and then set the rest as the offset from that since glLight0 is not 0 TODO

  glEnable(GL_LIGHT0 + getLight()); // Enables light i
  glLightfv(GL_LIGHT0 + getLight(), GL_POSITION, getPosition());
  glLightfv(GL_LIGHT0 + getLight(), GL_AMBIENT, getAmbient());
  glLightfv(GL_LIGHT0 + getLight(), GL_DIFFUSE, getDiffuse());
  glLightfv(GL_LIGHT0 + getLight(), GL_SPECULAR, getSpecular());

  if(getType() == 1) { // Spotlight/Pointlight exclusive
    glLightfv(GL_LIGHT0+getLight(), GL_SPOT_DIRECTION, getDirection());
    glLightfv(GL_LIGHT0+getLight(), GL_SPOT_CUTOFF, getAngularLimit());
    glLightfv(GL_LIGHT0+getLight(), GL_SPOT_EXPONENT, getAAtten());
    if(*getAngularLimit() == 180.f) { // Pointlight exclusive
      glLightfv(GL_LIGHT0+getLight(), GL_CONSTANT_ATTENUATION, getCAtten());
      glLightfv(GL_LIGHT0+getLight(), GL_LINEAR_ATTENUATION, getLAtten());
      glLightfv(GL_LIGHT0+getLight(), GL_QUADRATIC_ATTENUATION, getQAtten());
    }
  }

  //glDisable(GL_LIGHT0 + getLight()); // Disables light i
  glPopMatrix();
}

void 
Light::
print() {
  printf("light#: %u\t type: %f\tposition: (%f, %f, %f)\tdirection: (%f, %f, %f)\n", lightNum, position[3], position[0], position[1], position[2], direction[0], direction[1], direction[2]);
}


char*
Light::
parseInput(char* input) {
  char* filename = strtok(input, " ");
  char* tmp;
  float x, y, z, t;
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  position = glm::vec4(x, y, z, t); // Sets position
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  direction = glm::normalize(glm::vec3(x, y, z)); // Sets direction
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  ambient = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  diffuse = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  specular = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL) // The following only happen for spot/point lights
    constantAttenuation = atof(tmp); // Sets constant Attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    linearAttenuation = atof(tmp);  // Sets linear attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    quadraticAttenuation = atof(tmp);// sets quadratic attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularAttenuation = atof(tmp);  // sets angular attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularLimit = atof(tmp);       // sets angular Limit
  return filename;
}

