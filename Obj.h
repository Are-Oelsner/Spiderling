#ifndef __OBJ_H__
#define __OBJ_H__

#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include <vector>
#include <sstream>
#include <string.h>
#include <map>
#include <stdexcept>

using namespace std;

struct VEC6 { // VEC6 struct type made up of two glm::vec3s to store vertex + normal info
  glm::vec3 vert;
  glm::vec3 norm;
  //int vertex_index
};

class Obj {
  protected:
    ///Private Variables
    int mode = 3;   // 3 GL_TRIANGLES, 4 GL_QUADS

    // Final Data
    // Vertex-Normal Pairs
    vector<VEC6> data;
    vector<double> rdata;
    // Final index list
    vector<unsigned int> indices;

    // Map with key as vertex/normal pair and value as index number
    map<pair<unsigned int, unsigned int>, unsigned int> indexMap; 


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

    bool constructData();

    void setMode(int m);

    void print();

    //Getters
    vector<VEC6>* getData();
    vector<double>* getrData() {return &rdata;}
    vector<unsigned int>* getIndices();

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
