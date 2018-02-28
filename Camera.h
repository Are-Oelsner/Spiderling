#ifndef __CAMERA_H__
#define __CAMERA_H__

class Camera {
  protected:
    ///Private Variables
    float g_theta;

    // Specifies position of eye point
    double eyeX;
    double eyeY;
    double eyeZ;

    // Specifies poition of the reference point
    double centerX;
    double centerY;
    double centerZ;
    
    // Specifies the direction of the up vector
    double upX;
    double upY;
    double upZ;



  public:
    ///Constructors
    Camera();
    
    ///Functions
    void reset();
    //Setters
    void theta(float theta);

    //Getters
    float theta() {return g_theta;}

    double eX() {return eyeX;}
    double eY() {return eyeY;}
    double eZ() {return eyeZ;}

    double cX() {return centerX;}
    double cY() {return centerY;}
    double cZ() {return centerZ;}
    
    double uX() {return upX;}
    double uY() {return upY;}
    double uZ() {return upZ;}

    // Incrementers
    void incTheta(float inc) {g_theta += inc;}

    void eX(double c) {eyeX += c;}
    void eY(double c) {eyeY += c;}
    void eZ(double c) {eyeZ += c;}
                         
    void cX(double c) {centerX += c;}
    void cY(double c) {centerY += c;}
    void cZ(double c) {centerZ += c;}

    void uX(double c) {upX += c;}
    void uY(double c) {upY += c;}
    void uZ(double c) {upZ += c;}

};
#endif
