#include "Obj.h"

#include <sstream>
#include <string.h>
#include <stdexcept>

// SOIL
#include "SOIL.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Constructors 
Obj::
Obj(string input, string dir) {
  char* data = (char*)input.c_str();
  char* directory = (char*)dir.c_str();
  char* filename = parseInput(data);
  loadOBJ(filename, directory);
  constructData();
  initTransforms();
  constructBuffers();
  cout << "Constructed Buffers" << endl;
}

////////////////////////////////////////////////////////////////////////////////
///Functions
void
Obj::
draw() {
  glPushMatrix();
  //Translation
  glTranslatef((GLfloat) getPosition()[0], (GLfloat) getPosition()[1], (GLfloat) getPosition()[2]);
  // Rotation X, Y, Z
  glRotatef((GLfloat) getRotation()[0], (GLfloat) 1, (GLfloat) 0,(GLfloat) 0);
  glRotatef((GLfloat) getRotation()[1], (GLfloat) 0, (GLfloat) 1,(GLfloat) 0);
  glRotatef((GLfloat) getRotation()[2], (GLfloat) 0, (GLfloat) 0,(GLfloat) 1);
  // Scale 
  glScalef((GLfloat) getScale()[0], (GLfloat) getScale()[1], (GLfloat) getScale()[2]);

  // Get Data
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); // Bind EBO
  glBindBuffer(GL_ARRAY_BUFFER, vbo); // Bind VBO
  if(getBuffer() > 0 && getBuffer() < 1000) { // Texture
    glEnable(GL_TEXTURE_2D);
    glColor3f((GLfloat) 1., (GLfloat) 1., (GLfloat) 1.);
    glBindTexture(GL_TEXTURE_2D, getBuffer()); // Bind texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   getKa());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   getKd());
    glMaterialfv(GL_FRONT, GL_SPECULAR,  getKs());
    glMaterialfv(GL_FRONT, GL_SHININESS, getNs());
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(VEC8), (GLvoid*)(2*sizeof(glm::vec3)));
  } else {// Color
    glColor3f(getColor()[0], getColor()[1], getColor()[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT,   getKa());
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   getKd());
    glMaterialfv(GL_FRONT, GL_SPECULAR,  getKs());
    glMaterialfv(GL_FRONT, GL_SHININESS, getNs());
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, sizeof(VEC8), (GLvoid*)NULL);

  glEnableClientState(GL_NORMAL_ARRAY);
  glNormalPointer(GL_FLOAT, sizeof(VEC8), (GLvoid*)(sizeof(glm::vec3)));

  // Draw
  if(getMode() == 4) {// Quads
    glDrawElements(GL_QUADS, getIndices().size(), GL_UNSIGNED_INT, 0);
  } else {                        // Triangles
    glDrawElements(GL_TRIANGLES, getIndices().size(), GL_UNSIGNED_INT, 0);
  }
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}


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
/// @brief constructBuffers
void
Obj::
constructBuffers() {
  ////////////////////////////////////////////////////////////////////////////
  /// Element Buffer Object
  ////////////////////////////////////////////////////////////////////////////
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*getIndices().size(), getIndices().data(), GL_STATIC_DRAW);


  ////////////////////////////////////////////////////////////////////////////
  /// Vertex Array Object
  ////////////////////////////////////////////////////////////////////////////
  //glGenVertexArrays(1, &vao); 
  //glBindVertexArray(vao);     // Bind VAO


  ////////////////////////////////////////////////////////////////////////////
  /// Vertex Buffer Object
  ////////////////////////////////////////////////////////////////////////////
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VEC8)*getData().size(), getData().data(), GL_STATIC_DRAW);


  //glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(glm::vec3)*objs[i]->getData()->size(), objs[i]->getData()->data());

  /// For without VAO
  //glEnableClientState(GL_VERTEX_ARRAY);
  //glVertexPointer(3, GL_FLOAT, 0, NULL);

  //glBufferSubData(GL_ARRAY_BUFFER, sizeof(*objs[i]->getVertices()), sizeof(*objs[i]->getNormals()) , objs[i]->getNormals());
  //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(*objs[i]->getVertices()));
  //glEnableVertexAttribArray(1); // Enables attribute index 1 as being used

  ////////////////////////////////////////////////////////////////////////////
  /// Textures -- QOpenGLTexture object initialization
  ////////////////////////////////////////////////////////////////////////////

  const char * c = (const char*)getMTL().map_Kd.c_str();
  cout << c << endl;
  cout << getMode() << endl;
  GLuint tex_2d = SOIL_load_OGL_texture(c, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
  if(tex_2d == 0) {
    printf("SOIL loading error: '%s'\n", SOIL_last_result());
    setBuffer(-1);
  }
  else{
    setBuffer(tex_2d);
    printf("texture id = %u\n", tex_2d);
  }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief Loads obj file
/// @param path file path to read from 
/// v : vertex, vt : texture coordinate (TODO), vn : vertex normal, f : face. 
///
/// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
void
Obj::
loadOBJ(const char *filename, const char *directory) {
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
      string MTL = mtl;
      MTL.insert(0, 1, '/');
      MTL.insert(0, directory);
      loadMTL(MTL.c_str(), directory);
    }
    // Vertices
    if(strcmp(lineHeader, "v") == 0) {
      glm::vec3 vertex;
      tmp=fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z); // reads in vertex coordinates
      vertices.push_back(vertex);
    }
    // Vertex Textures
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
loadMTL(const char* filename, const char* directory) {
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
    // Ka 
    else if(strcmp(lineHeader, "Ka") == 0) {
      tmp=fscanf(file, "%f %f %f\n", &material.Ka.x, &material.Ka.y, &material.Ka.z);

    }
    // Kd
    else if(strcmp(lineHeader, "Kd") == 0) {
      tmp=fscanf(file, "%f %f %f\n", &material.Kd.x, &material.Kd.y, &material.Kd.z);
    }
    // Ks
    else if(strcmp(lineHeader, "Ks") == 0) {
      tmp=fscanf(file, "%f %f %f\n", &material.Ks.x, &material.Ks.y, &material.Ks.z);
    }
    // d
    else if(strcmp(lineHeader, "d") == 0) {
      tmp=fscanf(file, "%f\n", &material.d);
    }
    // Ns
    else if(strcmp(lineHeader, "Ns") == 0) {
      tmp=fscanf(file, "%f\n", &material.Ns);
    }
    // illum
    else if(strcmp(lineHeader, "illum") == 0) {
      tmp=fscanf(file, "%u\n", &material.illum);
    }
    // map_Kd
    else if(strcmp(lineHeader, "map_Kd") == 0) {
      char map[100];
      tmp = fscanf(file, "%s\n", map);
      material.map_Kd.insert(0, map);
      std::cout << "map_Kd:::  " << material.map_Kd << std::endl;
      material.map_Kd.insert(0, 1, '/');
      material.map_Kd.insert(0, directory);
      std::cout << "map_Kd:::  " << material.map_Kd << std::endl;
    }
  }
  fclose(file);
}


char*
Obj::
parseInput(char* input) {
  char* filename = strtok(input, " ");// gets obj filename
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
  printf("mode: %u\t#vertices: %lu\t#uvs: %lu\t#normals: %lu\n#faces: %lu\t#vertIndices: %lu\ndata: %lu\tindices:%lu\n", mode, vertices.size(), uvs.size(), normals.size(), vertices.size()/mode, vertexIndices.size(), data.size(), indices.size());
  printf("Material-- Ka: (%f, %f, %f)\tKd: (%f, %f, %f)\tKs: (%f, %f, %f)\n", material.Ka.x, material.Ka.y, material.Ka.z, material.Kd.x, material.Kd.y, material.Kd.z, material.Ks.x, material.Ks.y, material.Ks.z);
  printf("map_Kd: %s\td: %f\tNs: %f\tillum: %u\n", material.map_Kd.c_str(), material.d, material.Ns, material.illum);
  printf("vbo: %u\tebo: %u\n", vbo, ebo);
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
