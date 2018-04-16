#ifndef __OBJ_H__
#define __OBJ_H__

#include <QtGui/QImageReader>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <map>
#include <string>

#include "Vec.h"

using namespace std;

struct VEC8 { // VEC8 struct type made up of two glm::vec3s to store vertex + normal info and a vec2
  glm::vec3 vert;
  glm::vec3 norm;
  glm::vec2 text;
};

struct MTL { // Struct to store values from mtl file
  glm::vec3 Ka;
  glm::vec3 Kd;
  glm::vec3 Ks;
  float d; // transparency of the material/ also represented as Tr
  float Ns; // shininess of the material
  unsigned int illum; // represents illumination model 1:flat 2:specular highlights
  char* map_Kd; // file containing texture map ex. .jpg
  unsigned int texture; // refers to glImage of texture GLuint
};


class Obj {
  protected:
    ////////////////////////////////////////////////////////////////////////////////
    ///Private Variables
    int mode = 3;   // 3 GL_TRIANGLES, 4 GL_QUADS

    // Final Data
    // Vertex-Normal Pairs
    vector<VEC8> data;
    // Final index list
    vector<unsigned int> indices;
    // Material info
    MTL material;

    // Map with key as vertex/normal pair and value as index number
    map<pair<unsigned int, unsigned int>, unsigned int> indexMap; 

    // Transformations
    glm::vec4 position;
    glm::vec4 orientation;
    glm::vec4 size;

    glm::mat4 m_translation;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;

    glm::vec3 m_tran;

    glm::vec4 m_color;

    ////////////////////////////////////////////////////////////////////////////////
    // Original Data
    vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec3> normals;

    // Original Indices
    vector<unsigned int> vertexIndices;
    vector<unsigned int> uvIndices;
    vector<unsigned int> normalIndices;

  public:
    ///Constructors
    Obj() {}
    Obj(string filename);


    ///Functions

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief Loads obj file
    /// @param path file path to read from 
    /// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
    ///
    /// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
    void loadOBJ(const char *filename);
    void loadMTL(const char *filename);

    void print(bool debug);

    //Getters
    const vector<VEC8>& getData();
    const vector<unsigned int>& getIndices();

    glm::vec4 getPosition() {return position;}
    void setPosition(glm::vec4 vec) {position = vec;}
    void setPosition(float x, float y, float z) {position = glm::vec4(x, y, z, 1);}

    glm::vec4 getRotation() {return orientation;}
    void setRotation(glm::vec4 vec) {orientation = vec;}
    void setRotation(float x, float y, float z) {orientation = glm::vec4(x, y, z, 1);}

    glm::vec4 getScale() {return size;}
    void setScale(glm::vec4 vec) {size = vec;}
    void setScale(float x, float y, float z) {size = glm::vec4(x, y, z, 1);}

    glm::mat4 getTranslationM() {return m_translation;}
    glm::mat4 getRotationM() {return m_rotation;}
    glm::mat4 getScaleM() {return m_scale;}

    glm::vec3 getTran() {return m_tran;}

    glm::vec4 translate(float tx, float ty, float tz);
    glm::vec4 rotate(int i, float theta);
    glm::vec4 scale(float sx, float sy, float sz);

    int getMode() {return mode;}

    glm::vec4 getColor() {return m_color;}
    void setColor(float r, float g, float b) {m_color = glm::vec4(r, g, b, 0);}
    void setColor(glm::vec4 color) {m_color = color;}


  protected:
    ////////////////////////////////////////////////////////////////////////////////
    /// Helper Functions
    const vector<glm::vec3> getVertices();
    const vector<unsigned int> getVertexIndices();
    const vector<glm::vec2> getUvs();
    const vector<unsigned int> getUvIndices();
    const vector<glm::vec3> getNormals();
    const vector<unsigned int> getNormalIndices();

    char* parseInput(char* input);

    void constructData();

    void initTransforms();

    void setMode(int m);
};

#endif
