#ifndef __LIGHT_H__
#define __LIGHT_H__

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>

using namespace std;

class Light {
  protected:
    //Light variables
    glm::vec4 position = glm::vec4(0.f, 0.f, 1.f, 0.f);  // 0 if directional or 1 for spot
    glm::vec3 direction = glm::vec3(0.f, 0.f, -1.f); // position the light is facing
    glm::vec4 ambient = glm::vec4(0.f, 0.f, 0.f, 1.f);   //Default to black
    glm::vec4 diffuse = glm::vec4(1.f, 1.f, 1.f, 1.f);    // Default to white
    glm::vec4 specular = glm::vec4(1.f, 1.f, 1.f, 1.f);    // Default to white
    float constantAttenuation = 1.;   // constant attenuation away from spotlight
    float linearAttenuation = 0.;     // linear attenuation away from spotlight
    float quadraticAttenuation = 0.;  // quadratic attenuation away from spotlight
    float angularAttenuation = 0.; // angular attenuation exponent between [0, 128]
    float angularLimit = 180.;  // conical angle from direction in degrees, defaults to point light

    //Gl Light identifier
    unsigned int lightNum;

    //Transformation variables
    glm::vec3 translation = glm::vec3(0.f, 0.f, 0.f); 
    glm::vec3 rotation = glm::vec3(0.f, 0.f, 0.f); 
    glm::vec3 scale = glm::vec3(0.f, 0.f, 0.f); 

  public:
    ///Constructors
    // Default Constructor
    Light();

    // File Constructor 
    Light(string input, unsigned int lightNumber);

    ///Functions
    void draw();
    void print();

    ///Getters
    int getType() {return position[3];}               // returns 0 for directional or 1 for spot
    float* getPosition() {return &position[0];}       // returns position vector
    float* getDirection(){return &direction[0];}      // returns direction vector
    float* getAmbient()  {return &ambient[0];}        // returns ambient vector
    float* getDiffuse()  {return &diffuse[0];}        // returns diffuse vector
    float* getSpecular() {return &specular[0];}       // returns specular vector
    float* getCAtten() {return &constantAttenuation;}   // returns constant attenuation
    float* getLAtten() {return &linearAttenuation;}     // returns linear attenuation
    float* getQAtten() {return &quadraticAttenuation;}  // returns quadratic attenuation
    float* getAAtten() {return &angularAttenuation;}    // returns angular attenuation
    float* getAngularLimit() {return &angularLimit;}    // returns angular limit
    unsigned int getLight() {return lightNum;}        // returns offset from glLight0
    glm::vec3& getTranslation() {return translation;} // returns translation vector
    glm::vec3& getRotation()    {return rotation;}    // returns rotation vector
    glm::vec3& getScale()       {return scale;}       // returns scale vector

  private:
    ///Helper Functions
    // Parse Light info  
    char* parseInput(char* input);
};

#endif
