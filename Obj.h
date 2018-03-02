#ifndef __OBJ_H__
#define __OBJ_H__

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <sstream>
#include <string.h>
#include <map>
#include <stdexcept>

#include "Vec.h"

using namespace std;

struct VEC6 { // VEC6 struct type made up of two glm::vec3s to store vertex + normal info
  glm::vec3 vert;
  glm::vec3 norm;
};

class Obj {
  protected:
    ////////////////////////////////////////////////////////////////////////////////
    ///Private Variables
    int mode = 3;   // 3 GL_TRIANGLES, 4 GL_QUADS

    // Final Data
    // Vertex-Normal Pairs
    vector<VEC6> data;
    // Final index list
    vector<unsigned int> indices;

    // Map with key as vertex/normal pair and value as index number
    map<pair<unsigned int, unsigned int>, unsigned int> indexMap; 

    // Transformations
    glm::vec4 position;

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

    // Stats
    unsigned int numVertexIndices = 0;
    unsigned int numVertices = 0;
    unsigned int numUVs = 0;
    unsigned int numNormals = 0;
    unsigned int numFaces = 0;

  public:
    ///Constructors
    Obj() {}
    Obj(const char *filename);

    ~Obj();


    ///Functions

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief Loads obj file
    /// @param path file path to read from 
    /// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
    ///
    /// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
    bool loadOBJ(const char *filename);

    void constructData();

    void initTransforms();

    void setMode(int m);

    void print(bool debug);

    //Getters
    vector<VEC6>* getData();
    vector<unsigned int>* getIndices();

    glm::vec4* getPosition() {return &position;}
    void setPosition(glm::vec4 vec) {position = vec;}

    glm::mat4* getTranslation() {return &m_translation;}
    glm::mat4* getRotation() {return &m_rotation;}
    glm::mat4* getScale() {return &m_scale;}

    glm::vec3* getTran() {return &m_tran;}

    glm::vec4 translate(float tx, float ty, float tz);
    glm::vec4 rotate(int i, float theta);
    glm::vec4 scale(float sx, float sy, float sz);

    int getMode() {return mode;}

    glm::vec4 getColor() {return m_color;}
    float getColor(int i) {return m_color[i];}
    void setColor(float r, float g, float b) {m_color = glm::vec4(r, g, b, 0);}
    void setColor(glm::vec4 color) {m_color = color;}


  protected:
    ////////////////////////////////////////////////////////////////////////////////
    /// Helper Functions
    vector<glm::vec3>* getVertices();
    vector<unsigned int>* getVertexIndices();
    vector<glm::vec2>* getUvs();
    vector<unsigned int>* getUvIndices();
    vector<glm::vec3>* getNormals();
    vector<unsigned int>* getNormalIndices();

    unsigned int getNumVertices() {return numVertices;}
    unsigned int getNumUVs() {return numUVs;}
    unsigned int getNumNormals() {return numNormals;}
    unsigned int getNumFaces() {return numFaces;}
    unsigned int getNumVertexIndices() {return numVertexIndices;}
};

#endif
