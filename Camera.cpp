#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
  m_eye[0] = 0;
  m_eye[1] = 0;
  m_eye[2] = 10;

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

  m_up[0] = 0;
  m_up[1] = 1;
  m_up[2] = 0;
}


void 
Camera::
hLook(float angle) {
  m_at[0] += std::cos((PI/2)+angle);
  m_at[2] += std::sin(angle);
}
void 
Camera::
vLook(float angle) {
}


void 
Camera::
eye(int i, double c) {
  m_eye[i] += c;
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





