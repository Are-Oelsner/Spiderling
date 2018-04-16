#ifndef __OBJ_H__
#define __OBJ_H__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using namespace std;

class Light {
  protected:
    glm::vec4 position;  // x,y,z position and 0 if directional or 1 for spot
    glm::vec3 direction(0.f, 0.f, -1.f); // position the light is facing
    glm::vec4 ambient(0.f, 0.f, 0.f, 1.f);   //Default to black
    glm::vec4 diffuse(1.f, 1.f, 1.f, 1.f);    // Default to white
    glm::vec4 specular(1.f, 1.f, 1.f, 1.f);    // Default to white
    float constantAttenuation = 1.;   // constant attenuation away from spotlight
    float linearAttenuation = 0.;     // linear attenuation away from spotlight
    float quadraticAttenuation = 0.;  // quadratic attenuation away from spotlight
    float angularAttenuation = 0.; // angular attenuation exponent between [0, 128]
    float angularLimit = 180.;  // conical angle from direction in degrees, defaults to point light

  public:
    ///Constructors
    // Default Constructor
    Light();

    // File Constructor 
    Light(char* input);

    // Point Light Constructor
    Light(glm::vec4 pos, glm::vec3 dir, glm::vec4 amb, glm::vec4 diff,
        glm::vec4 spec, float aLim, float cAtten, float lAtten, float qAtten);

    // Directional Light Constructor
    Light(glm::vec4 pos, glm::vec3 dir, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec); 

    ///Functions
    void draw();

    ///Getters
    int getType() {return position[3];}             // returns 0 for directional or 1 for spot
    glm::vec4& getPosition() {return &position;}    // returns position vector
    glm::vec3& getDirection() {return &direction;}  // returns position vector
    glm::vec4& Ambient() {return &ambient;}         // returns position vector
    glm::vec4& Diffuse() {return &diffuse;}         // returns position vector
    glm::vec4& Specular() {return &specular;}       // returns position vector
    float getCAtten() {return constantAttenuation;} //returns constant attenuation
    float getLAtten() {return linearAttenuation;}   //returns linear attenuation
    float getQAtten() {return quadraticAttenuation;}//returns quadratic attenuation
    float getAAtten() {return angularAttenuation;}  //returns angular attenuation
    float getAngularLimit() {return angularLimit;}  //returns angular attenuation

  private:
    ///Helper Functions
    // Parse Light info  
    char* parseInput(char* input);
};

#endif
