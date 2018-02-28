#include "Obj.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Constructors 
Obj::
Obj(const char *filename) {
  loadOBJ(filename);
  constructData();
}

Obj::
~Obj() {
}

////////////////////////////////////////////////////////////////////////////////
///Functions
vector<VEC6>*
Obj::getData() {
  return &data;
}

vector<unsigned int>*
Obj::getIndices() {
  return &indices;
}

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
      int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2], &vertexIndex[3], &uvIndex[3], &normalIndex[3]);
      if((matches % 3) !=  0) {
        printf("Error: File cannot be read, an incorrect number of vertices, uvs, and normals was provided\n");
        return false;
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
        numFaces++;
        numVertexIndices += 3;
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
        numFaces++;
        numVertexIndices += 4;
        setMode(4);
      }


    }
  }
  /// Indexing
  // Vertex Indexing
  for(unsigned int i = 0; i < vertexIndexList.size(); i++) {
    unsigned int vertexIndex = vertexIndexList[i];
    vertexIndices.push_back(vertexIndex-1); //TODO vertexIndex-1?
  }
  // UV indexing
  for(unsigned int i = 0; i < uvIndexList.size(); i++) {
    unsigned int uvIndex = uvIndexList[i];
    uvIndices.push_back(uvIndex-1);
  }
  // Normal indexing
  for(unsigned int i = 0; i < normalIndexList.size(); i++) {
    unsigned int normalIndex = normalIndexList[i];
    normalIndices.push_back(normalIndex-1); //TODO normalIndex-1?
  }
}

void
Obj::
print() {
  printf("vec3: %lu\tvec6: %lu\n\n", sizeof(glm::vec3), sizeof(VEC6));
  printf("#vertices: %u\t#uvs: %u\t#normals: %u\n#faces: %u\t#vertIndices: %u\ndata: %lu\tindices:%lu\nrdata: %lu, %lu", numVertices, numUVs, numNormals, numFaces, numVertexIndices, data.size(), indices.size(), rdata.size(), rdata.size()*sizeof(double));
  for(int i = 0; i < indices.size(); i++) {
    printf("%u\t(%f,%f)\t(%f,%f)\t(%f,%f)\n", indices[i], data[indices[i]].vert[0], data[indices[i]].norm[0], data[indices[i]].vert[1], data[indices[i]].norm[1], data[indices[i]].vert[2], data[indices[i]].norm[2]);
  }
  printf("Data: %lu\n", data.size());
  for(int i = 0; i < data.size(); i++) {
    printf("%u\t(%f,%f)\t(%f,%f)\t(%f,%f)\n", i, data[i].vert[0], data[i].norm[0], data[i].vert[1], data[i].norm[1], data[i].vert[2], data[i].norm[2]);
  }
}
bool
Obj::
constructData() {
  pair<unsigned int, unsigned int> ind; // pair of vertex index / corresponding normal index
  unsigned int index = 0;               // index of new indices 
  VEC6 tmp;                             // VEC6 of vertex/normal info to be pushed back to data

  for(int i = 0; i < vertexIndices.size(); i++) {
    ind = pair<unsigned int, unsigned int>(vertexIndices[i], normalIndices[i]);
    // If pair is not already in list, adds it
    try{indexMap.at(ind);} catch (const std::out_of_range& oor) { 
      indexMap.emplace(ind, index);
      indices.push_back(index);   
      rdata.push_back(vertices[ind.first][0]);
      rdata.push_back(vertices[ind.first][1]);
      rdata.push_back(vertices[ind.first][2]);
      rdata.push_back(normals[ind.second][0]);
      rdata.push_back(normals[ind.second][1]);
      rdata.push_back(normals[ind.second][2]);
      data.push_back(tmp);
      index++;
      continue;
    }
    indices.push_back(indexMap.at(ind));

  }
}

//bool
//Obj::
//constructData() {
//  pair<unsigned int, unsigned int> ind; // pair of vertex index / corresponding normal index
//  unsigned int index = 0;               // index of new indices 
//  VEC6 tmp;                             // VEC6 of vertex/normal info to be pushed back to data
//
//  for(int i = 0; i < vertexIndices.size(); i++) {
//    ind = pair<unsigned int, unsigned int>(vertexIndices[i], normalIndices[i]);
//    // If pair is not already in list, adds it
//    try{indexMap.at(ind);} catch (const std::out_of_range& oor) { 
//      indexMap.emplace(ind, index);
//      indices.push_back(index);   
//      tmp.vert = vertices[ind.first];
//      tmp.norm = normals[ind.second];
//      data.push_back(tmp);
//      index++;
//      continue;
//    }
//    indices.push_back(indexMap.at(ind));
//
//  }
//}
