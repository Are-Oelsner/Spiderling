#ifndef __VEC_H__
#define __VEC_H__

#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Vec {

  ///////////////////////////////////////////////////
  /// GLM manipulation functions
  // converts mat4 to vec3 along diagonal
  glm::vec4 mToVec4(glm::mat4 _mat);

  // constructs matrix from vec3/vec4 (overloaded)
  glm::mat4 constructMatrix(glm::vec3 vec);

  // constructs matrix from vec3/vec4 (overloaded)
  glm::mat4 constructMatrix(glm::vec4 vec);

  // returns identity matrix
  glm::mat4 constructIdentityMatrix();

  // converts vec4 to vec3 removing last value
  glm::vec3 toVec3(glm::vec4 vec);

  ///////////////////////////////////////////////////
  /// Math
  glm::vec4 cross(glm::vec4 va, glm::vec4 vb);
}

#endif
