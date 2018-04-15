#include "Obj.h"
#include <sstream>
#include <string.h>
#include <stdexcept>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Constructors 
Obj::
Obj(string input) {
  char* tmp = (char*)input.c_str();
  char* filename = parseInput(tmp);
  loadOBJ(filename);
  constructData();
  initTransforms();
}

////////////////////////////////////////////////////////////////////////////////
///Functions
const vector<VEC8>&
Obj::getData() {
  return data;
}

const vector<unsigned int>&
Obj::getIndices() {
  return indices;
}

const vector<glm::vec3>
Obj::getVertices() {
  return vertices;
}

const vector<unsigned int>
Obj::getVertexIndices() {
  return vertexIndices;
}

const vector<glm::vec2>
Obj::getUvs() {
  return uvs;
}

const vector<unsigned int>
Obj::getUvIndices() {
  return uvIndices;
}

const vector<glm::vec3>
Obj::getNormals() {
  return normals;
}

const vector<unsigned int>
Obj::getNormalIndices() {
  return normalIndices;
}

void
Obj::
setMode(int m) {
  mode = m;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Loads obj file
/// @param path file path to read from 
/// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
///
/// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
void
Obj::
loadOBJ(const char *filename) {
  // Temp storage for contents of obj file
  vector<unsigned int> vertexIndexList, uvIndexList, normalIndexList;
  std::vector<glm::vec3> tmp_vertices;
  std::vector<glm::vec2> tmp_uvs;
  std::vector<glm::vec3> tmp_normals;
  FILE *file = fopen(filename, "r");
  int tmp;
  if(file == NULL) {
    printf("Cannot open the file !\n");
    return;
  }
  while(true) {
    char lineHeader[256];
    int res = fscanf(file, "%s", lineHeader);
    // if end of file is reached, break
    if(res == EOF)
      break;
    // Mtllib
    if(strcmp(lineHeader, "mtllib") == 0) {
      char mtl[100];
      tmp = fscanf(file, "%s\n", mtl);
      loadMTL(mtl);
      printf("%s\n", mtl);
    }
    // Vertices
    if(strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      tmp=fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // reads in vertex coordinates
      vertices.push_back(vertex);
    }
    // Vertex Textures -- Don't need for now TODO
    else if(strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      tmp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
      uvs.push_back(uv);
    }
    // Vertex Normals
    else if(strcmp(lineHeader, "vn") == 0) {
      glm::vec3 normal;
      tmp = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
      normals.push_back(normal);
    }
    // Faces
    else if(strcmp(lineHeader, "f") == 0) {
      unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
      if((matches % 3) !=  0) {
        printf("Error: File cannot be read, an incorrect number of vertices, uvs, and normals was provided\n");
        return;
      }

      if(matches == 9) {
        vertexIndexList.push_back(vertexIndex[0]);
        vertexIndexList.push_back(vertexIndex[1]);
        vertexIndexList.push_back(vertexIndex[2]);
        uvIndexList.push_back(uvIndex[0]);
        uvIndexList.push_back(uvIndex[1]);
        uvIndexList.push_back(uvIndex[2]);
        normalIndexList.push_back(normalIndex[0]);
        normalIndexList.push_back(normalIndex[1]);
        normalIndexList.push_back(normalIndex[2]);
        setMode(3);
      }
      else if(matches == 12) {
        vertexIndexList.push_back(vertexIndex[0]);
        vertexIndexList.push_back(vertexIndex[1]);
        vertexIndexList.push_back(vertexIndex[2]);
        vertexIndexList.push_back(vertexIndex[3]);
        uvIndexList.push_back(uvIndex[0]);
        uvIndexList.push_back(uvIndex[1]);
        uvIndexList.push_back(uvIndex[2]);
        uvIndexList.push_back(uvIndex[3]);
        normalIndexList.push_back(normalIndex[0]);
        normalIndexList.push_back(normalIndex[1]);
        normalIndexList.push_back(normalIndex[2]);
        normalIndexList.push_back(normalIndex[3]);
        setMode(4);
      }


    }
  }
  fclose(file);
  /// Indexing
  // Vertex Indexing
  for(unsigned int i = 0; i < vertexIndexList.size(); i++) {
    unsigned int vertexIndex = vertexIndexList[i];
    vertexIndices.push_back(vertexIndex-1); 
  }
  // UV indexing
  for(unsigned int i = 0; i < uvIndexList.size(); i++) {
    unsigned int uvIndex = uvIndexList[i];
    uvIndices.push_back(uvIndex-1);
  }
  // Normal indexing
  for(unsigned int i = 0; i < normalIndexList.size(); i++) {
    unsigned int normalIndex = normalIndexList[i];
    normalIndices.push_back(normalIndex-1); 
  }
}

void
Obj::
loadMTL(const char* filename) {
  FILE *file = fopen(filename, "r");
  int tmp;
  if(file == NULL) {
    printf("Cannot open the file !\n");
    return;
  }
  while(true) {
    char lineHeader[256];
    int res = fscanf(file, "%s", lineHeader);
    // if end of file is reached, break
    if(res == EOF)
      break;
    // map_Ka / map_Kd
    if(strcmp(lineHeader, "map_Ka") == 0 || strcmp(lineHeader, "map_Kd") == 0) {
      tmp = fscanf(file, "%s\n", &material.map_Kd);
      printf("%s\n", material.map_Kd);
    }
    // Ka TODO start here
    if(strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      tmp=fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // reads in vertex coordinates
      vertices.push_back(vertex);
    }
    // Vertex Textures -- Don't need for now TODO
    else if(strcmp(lineHeader, "vt") == 0) {
      glm::vec2 uv;
      tmp = fscanf(file, "%f %f\n", &uv.x, &uv.y);
      uvs.push_back(uv);
    }
  fclose(file);
}


char*
Obj::
parseInput(char* input) {
  char* filename = strtok(input, " ");
  char* tmp;
  float x, y, z;
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  setPosition(x, y, z); // Sets position transform
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  setRotation(x, y, z); // Sets rotation transform
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  setScale(x, y, z); // Sets scale transform
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  setColor(x, y, z); // Sets object color
  return filename;
}

void
Obj::
print(bool debug) {
  printf("mode: %u\t#vertices: %lu\t#uvs: %lu\t#normals: %lu\n#faces: %lu\t#vertIndices: %lu\ndata: %lu\tindices:%lu\n\n", mode, vertices.size(), uvs.size(), normals.size(), vertices.size()/mode, vertexIndices.size(), data.size(), indices.size());
  if(debug) {
    for(int i = 0; i < (int)indices.size(); i++) {
      printf("%u\t(%f,%f)\t(%f,%f)\t(%f,%f)\n", indices[i], data[indices[i]].vert[0], data[indices[i]].norm[0], data[indices[i]].vert[1], data[indices[i]].norm[1], data[indices[i]].vert[2], data[indices[i]].norm[2]);
    }
    printf("Data: %lu\n", data.size());
    for(int i = 0; i < (int)data.size(); i++) {
      printf("%u\t(%f,%f)\t(%f,%f)\t(%f,%f)\n", i, data[i].vert[0], data[i].norm[0], data[i].vert[1], data[i].norm[1], data[i].vert[2], data[i].norm[2]);
    }
  }
}

void
Obj::
constructData() {
  pair<unsigned int, unsigned int> ind; // pair of vertex index / corresponding normal index
  unsigned int index = 0;               // index of new indices 
  VEC8 tmp;                             // VEC8 of vertex/normal/texture info to be pushed back to data

  for(int i = 0; i < (int)vertexIndices.size(); i++) {
    ind = pair<unsigned int, unsigned int>(vertexIndices[i], normalIndices[i]);
    // If pair is not already in list, adds it
    try{indexMap.at(ind);} catch (const std::out_of_range& oor) { 
      indexMap.emplace(ind, index);
      indices.push_back(index);   
      tmp.vert = vertices[ind.first];
      tmp.norm = normals[ind.second];
      tmp.text = uvs[uvIndices[i]];
      data.push_back(tmp);
      index++;
      continue;
    }
    indices.push_back(indexMap.at(ind));

  }
}

void
Obj::
initTransforms() {
  m_translation = Vec::constructIdentityMatrix();
  m_rotation = Vec::constructIdentityMatrix();
  m_scale = Vec::constructIdentityMatrix();
}

glm::vec4
Obj::
translate(float tx, float ty, float tz) {
  float tdata[16] = {
    1., 0., 0., tx,
    0., 1., 0., ty,
    0., 0., 1., tz,
    0., 0., 0., 1.};
  m_translation = glm::make_mat4(tdata);
  m_tran = glm::vec3(tx, ty, tz);
  return m_translation * position;
}


glm::vec4
Obj::
rotate(int i, float theta) {
  float x1, x2, x3, y1, y2, y3, z1, z2, z3;
  switch(i) {
    case 0: { // X-axis
              x1 = 1.;          x2 = 0.;          x3 = 0.;
              y1 = 0.;          y2 = cos(theta);  y3 = sin(theta);
              z1 = 0.;          z2 = -sin(theta); z3 = cos(theta);
            }
            break;
    case 1: { // Y-axis
              x1 = cos(theta);  x2 = 0.;          x3 = -sin(theta);
              y1 = 0.;          y2 = 1.;          y3 = 0.;        
              z1 = sin(theta);  z2 = 0.;          z3 = cos(theta);
            }
            break;
    case 2: { // Z-axis
              x1 = cos(theta);  x2 = -sin(theta); x3 = 0.;
              y1 = sin(theta);  y2 = cos(theta);  y3 = 0.;        
              z1 = 0.;          z2 = 0.;          z3 = 1.;
            }
            break;
    default: printf("Error: rotation() i: %u\n", i);
             break;
  }
  float rdata[16] = {
    x1, x2, x3, 0.,
    y1, y2, y3, 0.,
    z1, z2, z3, 0.,
    0., 0., 0., 1.};
  m_rotation = glm::make_mat4(rdata);
  return m_rotation * position;
}

glm::vec4
Obj::
scale(float sx, float sy, float sz) {
  float sdata[16] = {
    sx, 0., 0., 0.,
    0., sy, 0., 0.,
    0., 0., sz, 0.,
    0., 0., 0., 1.};
  m_scale = glm::make_mat4(sdata);
  return m_scale * position;
}
