#include "Obj.h"

using namespace std;

Obj::
Obj(const char *filename) {
  loadOBJ(filename);
}

Obj::
~Obj() {
}

///Functions
vector<glm::vec3>*
Obj::getVertices() {
  return &vertices;
}

vector<glm::vec2>*
Obj::getUvs() {
  return &uvs;
}

vector<glm::vec3>*
Obj::getNormals() {
  return &normals;
}

bool 
Obj::
loadOBJ(const char *filename) {
  // Temp storage for contents of obj file
  std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
  std::vector<glm::vec3> tmp_vertices;
  std::vector<glm::vec2> tmp_uvs;
  std::vector<glm::vec3> tmp_normals;
  FILE *file = fopen(filename, "r");
  if(file == NULL) {
    printf("Cannot open the file !\n");
    return false;
  }
  while(true) {
    char lineHeader[256];
    int res = fscanf(file, "%s", lineHeader);
    // if end of file is reached, break
    if(res == EOF)
      break;
    // Vertices
    if(strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      int tmp = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // reads in vertex coordinates
      tmp_vertices.push_back(vertex);
    }
    // Vertex Textures -- Don't need for now TODO
    else if(strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      int tmp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
      tmp_uvs.push_back(uv);
    }
    // Vertex Normals
    else if(strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      int tmp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      tmp_normals.push_back(normal);
    }
    // Faces
    else if(strcmp(lineHeader, "f") == 0) {
      std::string vertex1, vertex2, vertex3;
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if(matches != 9) {
        printf("Error: File cannot be read, an incorrect number of vertices, uvs, and normals was provided\n");
        return false;
      }
      vertexIndices.push_back(vertexIndex[0]);
      vertexIndices.push_back(vertexIndex[1]);
      vertexIndices.push_back(vertexIndex[2]);
      uvIndices.push_back(uvIndex[0]);
      uvIndices.push_back(uvIndex[1]);
      uvIndices.push_back(uvIndex[2]);
      normalIndices.push_back(normalIndex[0]);
      normalIndices.push_back(normalIndex[1]);
      normalIndices.push_back(normalIndex[2]);
    }
    /// Indexing
    // Vertex Indexing
    for(unsigned int i = 0; i < vertexIndices.size(); i++) {
      unsigned int vertexIndex = vertexIndices[i];
      glm::vec3 vertex = tmp_vertices[vertexIndex-1];
      vertices.push_back(vertex);
    }
    // UV indexing
    for(unsigned int i = 0; i < uvIndices.size(); i++) {
      unsigned int uvIndex = uvIndices[i];
      glm::vec2 uv = tmp_uvs[uvIndex-1];
      uvs.push_back(uv);
    }
    // Normal indexing
    for(unsigned int i = 0; i < normalIndices.size(); i++) {
      unsigned int normalIndex = normalIndices[i];
      glm::vec3 normal = tmp_normals[normalIndex-1];
      normals.push_back(normal);
    }
  }
}

void
Obj::
printVertices() {
  //for(vector<glm::vec3>::iterator it = vertices.begin(); it != vertices.end(); ++it) {
  //}
}

