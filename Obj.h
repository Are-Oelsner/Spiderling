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
    // Vertices, should be read in triangles of three vertices. 
    vector<glm::vec3> vertices;
    vector<unsigned int> vertexIndices;
    vector<glm::vec2> uvs;
    vector<unsigned int> uvIndices;
    vector<glm::vec3> normals;
    vector<unsigned int> normalIndices;

  public:
    ///Constructors
    Obj() {}
    Obj(const char *filename);

    ~Obj();

    ///Functions

    ////////////////////////////////////////////////////////////////////////////////
    /// @brief Loads obj file
    /// @param path file path to read from 
    /// @param out_vertices references to obj vertices
    /// @param out_uvs references to obj uvs
    /// @param out_normals references to obj normals
    /// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
    ///
    /// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
    bool loadOBJ(const char *filename);

    //Getters
    vector<glm::vec3>* getVertices();
    vector<unsigned int>* getVertexIndices();
    vector<glm::vec2>* getUvs();
    vector<unsigned int>* getUvIndices();
    vector<glm::vec3>* getNormals();
    vector<unsigned int>* getNormalIndices();
};

#endif
