#include "Vec.h"

///////////////////////////////////////////////////
/// GLM manipulation functions
// converts mat4 to vec3 along diagonal
glm::vec4
Vec::
mToVec4(glm::mat4 _mat) {
  printf("%f\t%f\t%f\t%f\n", _mat[0][0], _mat[1][1], _mat[2][2], _mat[3][3]);
  return glm::vec4(_mat[0][0], _mat[1][1], _mat[2][2], _mat[3][3]);
}


// constructs matrix from vec3/vec4 (overloaded)
glm::mat4
Vec::
constructMatrix(glm::vec3 vec) {
  float r_data[16] = {vec[0], 0., 0., 0., 0., vec[1], 0., 0., 0., 0., vec[2], 0., 0., 0., 0., 0.};
  glm::mat4 r_mat = glm::make_mat4(r_data);
  return r_mat;
}

// constructs matrix from vec3/vec4 (overloaded)
glm::mat4
Vec::
constructMatrix(glm::vec4 vec) {
  float r_data[16] = {vec[0], 0., 0., 0., 0., vec[1], 0., 0., 0., 0., vec[2], 0., 0., 0., 0., vec[3]};
  glm::mat4 r_mat = glm::make_mat4(r_data);
  return r_mat;
}

// returns identity matrix
glm::mat4
Vec::
constructIdentityMatrix() {
  float r_data[16];
  return glm::make_mat4(r_data);
}

// converts vec4 to vec3 removing last value
glm::vec3
Vec::
toVec3(glm::vec4 vec) {
  return glm::vec3(vec[0], vec[1], vec[2]);
}

///////////////////////////////////////////////////
/// Math
glm::vec4
Vec::
cross(glm::vec4 va, glm::vec4 vb) {
  glm::vec3 a = toVec3(va);
  glm::vec3 b = toVec3(vb);
  return glm::vec4(glm::cross(a, b), 0);
}
