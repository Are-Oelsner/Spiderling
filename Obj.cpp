#include "Obj.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Constructors 
Obj::
Obj(const char *filename) {
  loadOBJ(filename);
}

Obj::
~Obj() {
}

////////////////////////////////////////////////////////////////////////////////
///Functions
vector<glm::vec3>*
Obj::getVertices() {
  return &vertices;
}

vector<unsigned int>*
Obj::getVertexIndices() {
  return &vertexIndices;
}

vector<glm::vec2>*
Obj::getUvs() {
  return &uvs;
}

vector<unsigned int>*
Obj::getUvIndices() {
  return &uvIndices;
}

vector<glm::vec3>*
Obj::getNormals() {
  return &normals;
}

vector<unsigned int>*
Obj::getNormalIndices() {
  return &normalIndices;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Loads obj file
/// @param path file path to read from 
/// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
///
/// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool 
Obj::
loadOBJ(const char *filename) {
  // Temp storage for contents of obj file
  vector<unsigned int> vertexIndexList, uvIndexList, normalIndexList;
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
      vertices.push_back(vertex);
      numVertices++;
    }
    // Vertex Textures -- Don't need for now TODO
    else if(strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      int tmp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
      uvs.push_back(uv);
      numUVs++;
    }
    // Vertex Normals
    else if(strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      int tmp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      normals.push_back(normal);
      numNormals++;
    }
    // Faces
    else if(strcmp(lineHeader, "f") == 0) {
      std::string vertex1, vertex2, vertex3; //TODO what is this for?
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
      if(matches != 9) {
        printf("Error: File cannot be read, an incorrect number of vertices, uvs, and normals was provided\n");
        return false;
      }
      vertexIndexList.push_back(vertexIndex[0]);
      vertexIndexList.push_back(vertexIndex[1]);
      vertexIndexList.push_back(vertexIndex[2]);
      uvIndexList.push_back(uvIndex[0]);
      uvIndexList.push_back(uvIndex[1]);
      uvIndexList.push_back(uvIndex[2]);
      normalIndexList.push_back(normalIndex[0]);
      normalIndexList.push_back(normalIndex[1]);
      normalIndexList.push_back(normalIndex[2]);
      numFaces++;
    }
  }
  /// Indexing
  // Vertex Indexing
  for(unsigned int i = 0; i < vertexIndexList.size(); i++) {
    unsigned int vertexIndex = vertexIndexList[i];
    vertexIndices.push_back(vertexIndex); //TODO vertexIndex-1?
    printf("%u\n", vertexIndex);
  }
  // UV indexing
  for(unsigned int i = 0; i < uvIndexList.size(); i++) {
    unsigned int uvIndex = uvIndexList[i];
    uvIndices.push_back(uvIndex);
  }
  // Normal indexing
  for(unsigned int i = 0; i < normalIndexList.size(); i++) {
    unsigned int normalIndex = normalIndexList[i];
    normalIndices.push_back(normalIndex); //TODO normalIndex-1?
  }
}

void
Obj::
print() {
  printf("#vertices: %u\n#uvs: %u\n#normals: %u\n", numVertices, numUVs, numNormals);
}
