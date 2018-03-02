#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "Vec.h"


class Camera {
  protected:
    ///Private Variables
    float g_theta;

    // Specifies position of eye point
    glm::vec4 eye;

    // Specifies poition of the reference point
    glm::vec4 center;
    glm::vec4 c_offset;
    glm::vec4 c_theta;
    glm::mat4 mat;
    glm::mat3 mat3;
    // Specifies angle rotation from at to center
    
    // Specifies the direction of the up vector
    glm::vec4 up;
    double PI = 3.1415926535897;

  public:
    ///Constructors
    Camera();
    
    ///Functions
    void reset();

    void mTransform();
    //Setters
    void theta(float theta);

    //Getters
    float theta() {return g_theta;}

    float at(int i) {if(i >= 0 && i <= 2) return eye[i];}
    float c(int i) {if(i >= 0 && i <= 2) return center[i];}
    float getUp(int i) {if(i >= 0 && i <= 2) return up[i];}

    // Incrementers
    void incTheta(float inc) {g_theta += inc;}
    void at(int i, double c);
    void c( int i, double c) {center[i] += c;}
    void upI(int i, double c) {up[i] += c;}

    // Look around functions
    void hLook(float angle);
    void vLook(float angle);
};
#endif
