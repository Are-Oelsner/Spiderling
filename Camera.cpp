#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
  eye[0] = 0;
  eye[1] = 0;
  eye[2] = -1;

  c_offset[0] = 0.; 
  c_offset[1] = 0.;
  c_offset[2] = 1.;

  center[0] = eye[0] + c_offset[0];
  center[1] = eye[1] + c_offset[1];
  center[2] = eye[2] + c_offset[2];

  c_theta[0] = 0.;
  c_theta[1] = 0.;
  c_theta[2] = 0.;

  up[0] = 0;
  up[1] = 1;
  up[2] = 0;
}

void
Camera::
mTransform() {
  //glm::vec4 c = glm::vec4(center, 1.0);
  glm::mat4 Model = glm::mat4(1.0);
  Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
  glm::vec4 center = mat * center;// Model Transform?
}

void
Camera::
reset() {
  g_theta = 0.f;
  eye[0] = 0;
  eye[1] = 10;
  eye[2] = 20;

  center[0] = 0;
  center[1] = 0;
  center[2] = 0;

  c_theta[0] = 0.;
  c_theta[0] = 0.;
  c_theta[0] = 0.;

  up[0] = 0;
  up[1] = 1;
  up[2] = 0;
}


void 
Camera::
hLook(float angle) {
  center[0] += std::cos((PI/2)+c_theta[0]);
  center[2] += std::sin(c_theta[0]);
}
void 
Camera::
vLook(float angle) {
}


void 
Camera::
at(int i, double c) {
  eye[i] += c;
}



//void 
//Camera::
//at(int i, double c) {
//  if(i == 0) {
//    glm::vec4 c = Vec::cross(eye-center, up);
//
//    glm::mat4 mat = Vec::constructIdentityMatrix();
//    mat *= glm::normalize(c);
//    mat += eye;
//    eye = Vec::mToVec4(mat);
//
//    // eye += glm::normalize(c);
//  }
//}





