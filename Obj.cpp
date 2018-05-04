#include "Obj.h"

#include <sstream>
#include <string.h>
#include <stdexcept>

// SOIL
#include "SOIL.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
///Constructors 
/* 
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
*/
