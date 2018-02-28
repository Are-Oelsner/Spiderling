#ifndef __CAMERA_H__
#define __CAMERA_H__

#include<glm/vec3.hpp>

class Camera {
  protected:
    ///Private Variables
    float g_theta;

    // Specifies position of eye point
    glm::vec3 eye;

    // Specifies poition of the reference point
    glm::vec3 center;
    
    // Specifies the direction of the up vector
    glm::vec3 up;

  public:
    ///Constructors
    Camera();
    
    ///Functions
    void reset();
    //Setters
    void theta(float theta);

    //Getters
    float theta() {return g_theta;}

    glm::vec3 at(int i) {if(i >= 0 && i <= 2) return eye[i];}
    glm::vec3 c(int i) {if(i >= 0 && i <= 2) return center[i];}
    glm::vec3 up(int i) {if(i >= 0 && i <= 2) return up[i];}

    // Incrementers
    void incTheta(float inc) {g_theta += inc;}
    void at(int i, double c) {eye[i] += c;}
    void c( int i, double c) {center[i] += c;}
    void up(int i, double c) {up[i] += c;}

    // Look around functions
    void DO THIS
};
#endif
