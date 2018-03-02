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

//void
//Camera::
//mTransform() {
//  //glm::vec4 c = glm::vec4(m_at, 1.0);
//  glm::mat4 Model = glm::mat4(1.0);
//  Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
//  glm::vec4 m_at = mat * m_at;// Model Transform?
//}

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





