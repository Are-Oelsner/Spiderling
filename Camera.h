#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera {
  protected:
    ///Private Variables
    float g_theta;

  public:
    ///Constructors
    Camera();
    Camera(float theta);
    
    ///Functions
    //Getters
    float theta();

    //Setters
    void theta(float theta);

    // Increments g_theta by inc
    void incTheta(float inc);
  

};
#endif
