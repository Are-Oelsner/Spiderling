#include "Camera.h"

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

Camera::
Camera() {
  g_theta = 0.f;
  m_eye[0] = 0;
  m_eye[1] = 20;
  m_eye[2] = 40;

  c_theta[0] = 0;
  c_theta[1] = 0;
  c_theta[2] = 0;

  m_at[0] = 0;
  m_at[1] = 0;
  m_at[2] = 0;

  m_up[0] = 0;
  m_up[1] = 1;
  m_up[2] = 0;
}

glm::vec4
Camera::
translate(float tx, float ty, float tz) {
  float tdata[16] = {
    1., 0., 0., tx,
    0., 1., 0., ty,
    0., 0., 1., tz,
    0., 0., 0., 1.};
  m_translation = glm::make_mat4(tdata);
  //m_at = m_translation * m_at;
  m_at = m_translation * m_at;
  return m_eye = m_translation * m_eye;
}

void
Camera::
draw() {
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eye(0), eye(1), eye(2), at(0), at(1), at(2), getUp(0), getUp(1), getUp(2)); 
  //gluLookAt(cam.eX()*std::sin(cam.theta(), cam.eY(), cam.eZ()*std::cos(cam.theta()),
  //gluLookAt(10*std::sin(cam.theta()), 0.f, 10*std::cos(cam.theta()), 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
}


void
Camera::
reset() {
  g_theta = 0.f;
  m_eye[0] = 0;
  m_eye[1] = 20;
  m_eye[2] = 60;

  m_at[0] = 0;
  m_at[1] = 15;
  m_at[2] = 0;

  c_theta[0] = 0;
  c_theta[1] = 0;
  c_theta[2] = 0;

  m_up[0] = 0;
  m_up[1] = 1;
  m_up[2] = 0;
}


void 
Camera::
hLook(float angle) {
  glm::vec4 diff = m_at - m_eye;
  c_theta[0] += angle;
  m_at[0] = abs(glm::distance(m_eye, m_at)) *std::cos((M_PI/2)+c_theta[0]) + m_eye[0];
  c_theta[1] += angle;
  m_at[1] = abs(glm::distance(m_eye, m_at)) * std::sin(c_theta[1]) + m_eye[1];
}
void 
Camera::
vLook(float angle) {
}


