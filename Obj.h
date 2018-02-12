#ifndef __OBJ_H__
#define __OBJ_H__

#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include <vector>
#include <sstream>
#include <string.h>

using namespace std;

class Obj {
  protected:
    ///Private Variables
    vector<glm::vec3> vertices;
    vector<unsigned int> vertexIndices;
    vector<glm::vec2> uvs;
    vector<unsigned int> uvIndices;
    vector<glm::vec3> normals;
    vector<unsigned int> normalIndices;

  private:
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

    void print();

    //Getters
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
};

#endif
