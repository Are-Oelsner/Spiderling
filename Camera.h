#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera {
  protected:
    ///Private Variables
    float g_theta;
    double eyeY;
    double eyeZ = 10;

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

    double getEyeY() {return eyeY;}
    double getEyeZ() {return eyeZ;}
    void incrementY(double inc) {eyeY += inc;}
    void incrementZ(double inc) {eyeZ += inc;}
  

};
#endif
