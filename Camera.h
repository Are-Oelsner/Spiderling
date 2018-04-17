#ifndef __CAMERA_H__
#define __CAMERA_H__

#define _USE_MATH_DEFINES

#include <math.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

//#include "Vec.h"


class Camera {
  protected:
    ///Private Variables
    float g_theta;

    // Specifies position of eye point
    glm::vec4 m_eye;
    glm::mat4 m_translation;

    // Specifies poition of the reference point
    glm::vec4 m_at;
    glm::vec4 c_theta;

    // Specifies angle rotation from eye to at
    
    // Specifies the direction of the up vector
    glm::vec4 m_up;

  public:
    ///Constructors
    Camera();
    
    ///Functions
    void draw();
    void reset();

    glm::vec4 translate(float tx, float ty, float tz);

    //Setters
    void theta(float theta);

    //Getters
    float theta() {return g_theta;}

    float eye(int i) {if(i >= 0 && i <= 2) return m_eye[i];}
    float at(int i) {if(i >= 0 && i <= 2) return m_at[i];}
    float getUp(int i) {if(i >= 0 && i <= 2) return m_up[i];}

    // Incrementers
    void incTheta(const float inc) {g_theta += inc;}
    void eye(const int i, const double c) {m_eye[i] += c;}
    void at(const int i, const double c) {m_at[i] += c;}
    void upI(const int i, const double c) {m_up[i] += c;}

    // Look around functions
    void hLook(float angle);
    void vLook(float angle);
};
#endif
