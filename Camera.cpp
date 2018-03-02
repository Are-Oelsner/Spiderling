#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
  m_eye[0] = 0;
  m_eye[1] = 20;
  m_eye[2] = 20;

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
reset() {
  g_theta = 0.f;
  m_eye[0] = 0;
  m_eye[1] = 10;
  m_eye[2] = 20;

  m_at[0] = 0;
  m_at[1] = 0;
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
  m_at[0] = abs(glm::distance(m_eye, m_at)) *std::cos((PI/2)+c_theta[0]) + m_eye[0];
  c_theta[1] += angle;
  m_at[1] = abs(glm::distance(m_eye, m_at)) * std::sin(c_theta[1]) + m_eye[1];
}
void 
Camera::
vLook(float angle) {
}



//void 
//Camera::
//eye(int i, double c) {
//  if(i == 0) {
//    glm::vec4 c = Vec::cross(m_eye-m_at, m_up);
//
//    glm::mat4 mat = Vec::constructIdentityMatrix();
//    mat *= glm::normalize(c);
//    mat += eye;
//    eye = Vec::mToVec4(mat);
//
//    // eye += glm::normalize(c);
//  }
//}





