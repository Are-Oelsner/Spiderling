#ifndef __OBJ_H__
#define __OBJ_H__

// GL
#if   defined(OSX) 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#endif

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include "Vec.h"
#include "Ray.h"
#include "Collision.h"
#include "Material.h"

using namespace std;

class Obj {
  protected:
    ////////////////////////////////////////////////////////////////////////////////
    ///Private Variables
    glm::vec3 position = glm::vec3(0.f, 0.f, 0.f);

    // Material info
    shared_ptr<Material> material;

    // Transformations
    glm::vec4 translation;
    glm::vec4 orientation;
    glm::vec4 size;

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;

    glm::vec4 m_color;

  public:
    virtual ~Obj() {}
    virtual Collision collide(Ray ray) =0;

    ///Constructors
  //virtual Obj() {}
  //virtual Obj(string filename, string dir);


    ///Functions
  //virtual void draw();
  //virtual void print();

    //Getters
    shared_ptr<Material> getMaterial() {return material;}

  //float* getKa()  {return &material.Ka[0];}        // returns ambient vector
  //float* getKd()  {return &material.Kd[0];}        // returns diffuse vector
  //float* getKs()  {return &material.Ks[0];}       // returns specular vector
  //float* getNs()  {return &material.Ns;}

    glm::vec4 getTranslation() {return translation;}
    void setTranslation(glm::vec4 vec) {translation = vec;}
    void setTranslation(float x, float y, float z) {translation = glm::vec4(x, y, z, 1);}
    glm::vec4 getRotation() {return orientation;}
    void setRotation(glm::vec4 vec) {orientation = vec;}
    void setRotation(float x, float y, float z) {orientation = glm::vec4(x, y, z, 1);}
    glm::vec4 getScale() {return size;}
    void setScale(glm::vec4 vec) {size = vec;}
    void setScale(float x, float y, float z) {size = glm::vec4(x, y, z, 1);}

  //glm::mat4 getTranslationM() {return m_translation;}
  //glm::mat4 getRotationM() {return m_rotation;}
  //glm::mat4 getScaleM() {return m_scale;}

  //glm::vec4 translate(float tx, float ty, float tz);
  //glm::vec4 rotate(int i, float theta);
  //glm::vec4 scale(float sx, float sy, float sz);

    glm::vec4 getColor() {return m_color;}

  protected:
    ////////////////////////////////////////////////////////////////////////////////
    /// Helper Functions
    //virtual void loadOBJ(const char *filename, const char* directory);
    //virtual void loadMTL(const char *filename, const char* directory);


    //virtual char* parseInput(char* input);

    //virtual void constructData();
    //virtual void initTransforms();
};

#endif
