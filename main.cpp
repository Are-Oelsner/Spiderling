/* Author: Are Oelsner
 * CMSC 335 Graphics Engine - Project 1
 */
////////////////////////////////////////////////////////////////////////////////
/// @file
/// @brief Contains main function to create a window and run engine
///
/// Basic support for directional light, depth buffer, setting up 3d projection,
/// setting up a 3d camera, drawing a cube model, and running a set fixed frame
/// rate.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Includes

// My Files
#include "Obj.h"
#include "WindowClass.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Light.h"

// STL
#include <cmath>
#include <chrono>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <memory>

// SOIL
#include "SOIL.h"

// GL
#if   defined(OSX) 
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#elif defined(LINUX)
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glx.h>
#endif

// GLM - included in Obj
// Qt  - included in Obj

////////////////////////////////////////////////////////////////////////////////
/// Spiderling Objects
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Window
WindowClass m_window;

////////////////////////////////////////////////////////////////////////////////
// Camera
Camera cam;

////////////////////////////////////////////////////////////////////////////////
// Object from .obj file specified by argv[1] in main
vector<unique_ptr<Obj>> objs;
vector<GLuint> ebos, vbos;
// Particle Systems
vector<unique_ptr<ParticleSystem>> ps;
// Repulsors
vector<struct Repulsor> repulsors;
int rep = 0;
// Lights
vector<unique_ptr<Light>> lights;

// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};


////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize() {
  glClearColor(0.329f, 0.419f, 0.670f, 0.f);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback for resize of window
///
/// Responsible for setting window size (viewport) and projection matrix.
void
resize(GLint _w, GLint _h) {
  m_window.width(_w);
  m_window.height(_h);

  // Viewport
  glViewport(0, 0, m_window.width(), m_window.height());

  // Projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.f, GLfloat(m_window.width())/m_window.height(), 0.01f, 1000.f);
}


////////////////////////////////////////////////////////////////////////////////
/// @brief Timer function to fix framerate in a GLUT application
/// @param _v Value (not used here)
///
/// Note, this is rudametary and fragile.
void
timer(int _v) {
  if(m_window.window() != 0) {
    glutPostRedisplay();

    g_delay = std::max(0.f, 1.f/FPS - g_frameRate);
    glutTimerFunc((unsigned int)(1000.f*g_delay), timer, 0);
  }
  else
    exit(0);
}



////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
void
keyPressed(GLubyte _key, GLint _x, GLint _y) {
  switch(_key) {
    // Escape key : quit application
    case 27:
      std::cout << "Destroying window: " << m_window.window() << std::endl;
      glutDestroyWindow(m_window.window());
      m_window.window(0);
      break;
    case 106:       // j    display filled shape
      std::cout << "Model Display: Filled" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case 107:       // k    display wireframe
      std::cout << "Model Display: Wireframe" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case 108:       // l    display points
      std::cout << "Model Display: Points" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      break;
    case 121:       // y    switch to next repulsor/attractor
      //cam.hLook(.2);
      rep = (rep+1) % repulsors.size();
      printf("%u\n", rep);
      break;
    case 117:       // u    move repulsor left
      //cam.hLook(.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[0] -= 1;
      break;
    case 105:       // i    move repulsor down
      //cam.hLook(-.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[1] -= 1;
      break;
    case 111:       // o    move repulsor up
      //cam.hLook(.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[1] += 1;
      break;
    case 112:       // p    move repulsor right
      //cam.hLook(.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[0] += 1;
      break;
    case 91:       // [    move repulsor closer
      //cam.hLook(.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[2] += 1;
      break;
    case 93:       // ]    move repulsor further away
      //cam.hLook(.2);
      if(repulsors.size() > rep)
        repulsors[rep].position[2] -= 1;
      break;
    case 119:       // w    look up
      cam.at(1, 0.5);
      break;
    case 115:       // s    look down
      cam.at(1, -0.5);
      break;
    case 97:        // a    look left
      cam.at(0, -0.5);
      break;
    case 100:       // d    look right
      cam.at(0, 0.5);
      break;
    case 114:       // r    reset camera
      cam.reset();
      break;
    case 113:       // q    zoom out
      cam.eye(2, 0.5);
      cam.at(2, 0.5);
      break;
    case 101:       // e    zoom in
      cam.eye(2, -0.5);
      cam.at(2, -0.5);
      break;
      //case 116:       // t    test transform
      //  cam.mTransform();
      //  break;
      // Unhandled
    default:
      std::cout << "Unhandled key: " << (int)(_key) << std::endl;
      break;
  }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Callback function for keyboard presses of special keys
/// @param _key Key
/// @param _x X position of mouse
/// @param _y Y position of mouse
void
specialKeyPressed(GLint _key, GLint _x, GLint _y) {
  switch(_key) {
    // Arrow keys
    case GLUT_KEY_LEFT:
      //cam.translate(-.1, 0, 0);
      cam.eye(0, -.1);
      cam.at(0, -0.1);
      break;
    case GLUT_KEY_RIGHT:
      //cam.translate(.1, 0, 0);
      cam.eye(0, 0.1);
      cam.at(0, 0.1);
      break;
    case GLUT_KEY_UP:
      cam.eye(1, 0.3);
      cam.at(1, 0.3);
      break;
    case GLUT_KEY_DOWN:
      cam.eye(1, -0.3);
      cam.at(1, -0.3);
      break;
      // Unhandled
    default:
      std::cout << "Unhandled special key: " << _key << std::endl;
      break;
  }
}

Repulsor 
makeRepulsor(string filename) {
  struct Repulsor repulsor;
  char* input = (char*) filename.c_str();
  char* tmp = strtok(input, " ");
  if((tmp = strtok(NULL, " ")) != NULL)
    repulsor.position[0] = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    repulsor.position[1] = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    repulsor.position[2] = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    repulsor.mass = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    repulsor.state = atoi(tmp);
  return repulsor;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Draw function for single frame
void
draw() {
  using namespace std::chrono;

  //////////////////////////////////////////////////////////////////////////////
  // Clear
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  //////////////////////////////////////////////////////////////////////////////
  // Draw

  // Camera
  cam.draw();

  glEnable(GL_LIGHTING);
  glPointSize(30);
  glColor3f((GLfloat) 1., (GLfloat) 1., (GLfloat) 1.);
  // Lights
  //glBegin(GL_POINTS);
  for(int i = 0; i < lights.size(); i++) {
    glPushMatrix();

    glEnable(GL_LIGHT0 + lights[i]->getLight()); // Enables light i
    glLightfv(GL_LIGHT0 + lights[i]->getLight(), GL_AMBIENT, lights[i]->getAmbient());
    glLightfv(GL_LIGHT0 + lights[i]->getLight(), GL_DIFFUSE, lights[i]->getDiffuse());
    glLightfv(GL_LIGHT0 + lights[i]->getLight(), GL_SPECULAR, lights[i]->getSpecular());
    glLightfv(GL_LIGHT0 + lights[i]->getLight(), GL_POSITION, lights[i]->getPosition());

    if(lights[i]->getType() == 1) { // Spotlight/Pointlight exclusive
      glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_SPOT_DIRECTION, lights[i]->getDirection());
      glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_SPOT_CUTOFF, lights[i]->getAngularLimit());
      glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_SPOT_EXPONENT, lights[i]->getAAtten());
      if(*lights[i]->getAngularLimit() == 180.f) { // Pointlight exclusive
        glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_CONSTANT_ATTENUATION, lights[i]->getCAtten());
        glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_LINEAR_ATTENUATION, lights[i]->getLAtten());
        glLightfv(GL_LIGHT0+lights[i]->getLight(), GL_QUADRATIC_ATTENUATION, lights[i]->getQAtten());
      }
    }
    glPopMatrix();
  }
  
  glPointSize(5);

  // Objects
  for(int i = 0; i < objs.size(); i++) {
    //objs[i]->draw();
    glPushMatrix();
    //Translation
    glTranslatef((GLfloat) objs[i]->getPosition()[0], (GLfloat)
        objs[i]->getPosition()[1], (GLfloat) objs[i]->getPosition()[2]);
    // Rotation
    // Rotate X
    glRotatef((GLfloat) objs[i]->getRotation()[0], (GLfloat) 1, (GLfloat) 0,(GLfloat) 0);
    // Rotate Y
    glRotatef((GLfloat) objs[i]->getRotation()[1], (GLfloat) 0, (GLfloat) 1,(GLfloat) 0);
    // Rotate Z
    glRotatef((GLfloat) objs[i]->getRotation()[2], (GLfloat) 0, (GLfloat) 0,(GLfloat) 1);
    // Scale 
    glScalef((GLfloat) objs[i]->getScale()[0], (GLfloat) objs[i]->getScale()[1],
        (GLfloat) objs[i]->getScale()[2]);


    //glActiveTexture(GL_TEXTURE0);// + (unsigned int)i);
    // Get Data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]); // Bind EBO
    glBindBuffer(GL_ARRAY_BUFFER, vbos[i]); // Bind VBO
    if(objs[i]->getBuffer() > 0 && objs[i]->getBuffer() < objs.size()) {
      // Texture
      glEnable(GL_TEXTURE_2D);
      glColor3f((GLfloat) 1., (GLfloat) 1., (GLfloat) 1.);
      glBindTexture(GL_TEXTURE_2D, objs[i]->getBuffer()); // Bind texture
      glMaterialfv(GL_FRONT, GL_AMBIENT,   objs[i]->getKa());
      glMaterialfv(GL_FRONT, GL_DIFFUSE,   objs[i]->getKd());
      glMaterialfv(GL_FRONT, GL_SPECULAR,  objs[i]->getKs());
      glMaterialfv(GL_FRONT, GL_EMISSION,  objs[i]->getKs());
      glMaterialfv(GL_FRONT, GL_SHININESS, objs[i]->getKs());
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_FLOAT, sizeof(VEC8), (GLvoid*)(2*sizeof(glm::vec3)));
    }
    else {//if(objs[i]->getBuffer() <= 0 || objs[i]->getBuffer() > objs.size()) {
      // Color
      glColor3f(objs[i]->getColor()[0], objs[i]->getColor()[1], objs[i]->getColor()[2]);
      glMaterialfv(GL_FRONT, GL_AMBIENT,   objs[i]->getKa());
      glMaterialfv(GL_FRONT, GL_DIFFUSE,   objs[i]->getKd());
      glMaterialfv(GL_FRONT, GL_SPECULAR,  objs[i]->getKs());
      glMaterialfv(GL_FRONT, GL_EMISSION,  objs[i]->getKs());
      glMaterialfv(GL_FRONT, GL_SHININESS, objs[i]->getKs());
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(VEC8), (GLvoid*)NULL);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(VEC8), (GLvoid*)(sizeof(glm::vec3)));

    
    // Draw
    if(objs[i]->getMode() == 4) // Quads
      glDrawElements(GL_QUADS, objs[i]->getIndices().size(), GL_UNSIGNED_INT, 0);
    else                        // Triangles
      glDrawElements(GL_TRIANGLES, objs[i]->getIndices().size(), GL_UNSIGNED_INT, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }

  glColor3f(0.3f, 0.f, 1.f);
  // Particle Systems
  for(int i = 0; i < ps.size(); i++) {
    ps[i]->draw();
    ps[i]->update(repulsors);
  }

  // Repulsors/Attractors
  glPointSize(20);
  glBegin(GL_POINTS);
  for(int i = 0; i < repulsors.size(); i++) {
    glColor3f((GLfloat) repulsors.at(i).state, (GLfloat) repulsors.at(i).state, (GLfloat) repulsors.at(i).state);
    glVertex3f((GLfloat) repulsors.at(i).position[0], (GLfloat) repulsors.at(i).position[1], (GLfloat) repulsors.at(i).position[2]);
  }
  glEnd();

  //////////////////////////////////////////////////////////////////////////////
  // Show
  glutSwapBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Record frame time
  high_resolution_clock::time_point time = high_resolution_clock::now();
  g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
  g_frameTime = time;
  g_framesPerSecond = 1.f/(g_delay + g_frameRate);
  //printf("FPS: %6.2f\n", g_framesPerSecond);
}

void parse(const char* file, const char* directory) {
  ifstream objFile;
  objFile.open(file);
  string filename;
  string dir = directory;
  size_t foundobj; // found object
  size_t foundpar; // found particle system
  size_t foundrep; // found repulsor
  size_t foundlgt; // found light
  printf("################################################################################");
  while(getline(objFile, filename)) {
    printf("\n");
    foundobj = filename.find(".obj");
    foundpar = filename.find(".par");
    foundrep = filename.find(".rep");
    foundlgt = filename.find("light");
    if(foundrep == string::npos && foundobj == string::npos && foundpar != string::npos && foundlgt == string::npos) {
      filename.insert(0, 1, '/');
      filename.insert(0, dir);
      ps.emplace_back(new ParticleSystem(filename));
      printf("Particle System: %s\n", filename.c_str());
      ps.back()->print();
    }
    else if(foundobj != string::npos && foundpar == string::npos && foundrep == string::npos && foundlgt == string::npos)  {
      filename.insert(0, 1, '/');
      filename.insert(0, dir);
      objs.emplace_back(new Obj(filename, dir));
      printf("Object: %s\n", filename.c_str());
      objs.back()->print(false);
    }
    else if(foundrep != string::npos && foundobj == string::npos && foundpar == string::npos && foundlgt == string::npos)  {
      repulsors.emplace_back(makeRepulsor(filename));
      printf("Repulsor: %s\n", filename.c_str());
      //repulsors.back()->print();
    }
    else if(foundlgt != string::npos && foundobj == string::npos && foundpar == string::npos && foundrep == string::npos) {
      lights.emplace_back(new Light(filename, lights.size()));
      printf("Light: %s\n", filename.c_str());
      lights.back()->print();
    }
  }
  printf("################################################################################\n");
  objFile.close();
}

void
constructBuffers() {
    for(int i = 0; i < objs.size(); i++) {
      ////////////////////////////////////////////////////////////////////////////
      /// Element Buffer Object
      ////////////////////////////////////////////////////////////////////////////
      GLuint ebo;
      glGenBuffers(1, &ebo);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*objs[i]->getIndices().size(), objs[i]->getIndices().data(), GL_STATIC_DRAW);
      ebos.emplace_back(ebo);


      ////////////////////////////////////////////////////////////////////////////
      /// Vertex Array Object
      ////////////////////////////////////////////////////////////////////////////
      //glGenVertexArrays(1, &vao); 
      //glBindVertexArray(vao);     // Bind VAO


      ////////////////////////////////////////////////////////////////////////////
      /// Vertex Buffer Object
      ////////////////////////////////////////////////////////////////////////////
      GLuint vbo;
      glGenBuffers(1, &vbo);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);
      glBufferData(GL_ARRAY_BUFFER, sizeof(VEC8)*objs[i]->getData().size(), objs[i]->getData().data(), GL_STATIC_DRAW);
      vbos.emplace_back(vbo);



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
      
      const char * c = (const char*)objs[i]->getMTL().map_Kd.c_str();
      cout << c << endl;
      cout << objs[i]->getMode() << endl;
      GLuint tex_2d = SOIL_load_OGL_texture(c, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
      if(tex_2d == 0) {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        objs[i]->setBuffer(-1);
      }
      else{
        objs[i]->setBuffer(tex_2d);
        printf("texture id = %u\t i = %u\n", tex_2d, i);


        //glActiveTexture(GL_TEXTURE0 + (unsigned int)i);
        //GLuint text = *objs[i]->getBuffer();
        //glGenTextures(1, &text);
        //glBindTexture(GL_TEXTURE_2D, text);
        glBindTexture(GL_TEXTURE_2D, tex_2d);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //target, level, internalFormat, width, height, border, format, type, *data
        //GLenum, GLint, GLint,       GLsizei, GLsizei, GLint, GLenum, GLenum, constGLvoid*
        //TODO TODO start here
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, objs[i]->getMTL().texture->width(), objs[i]->getMTL().texture->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, objs[i]->getMTL().texture);//TODO check

      }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Main

////////////////////////////////////////////////////////////////////////////////
/// @brief main
/// @param _argc Count of command line arguments
/// @param _argv Command line arguments
/// @return Application success status
int
main(int _argc, char** _argv) {
  //////////////////////////////////////////////////////////////////////////////
  // Initialize GLUT Window
  std::cout << "Initializing GLUTWindow" << std::endl;
  // GLUT
  glutInit(&_argc, _argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50, 100);
  glutInitWindowSize(m_window.width(), m_window.height()); // HD size
  m_window.window(glutCreateWindow("Spiderling: A Rudimentary Game Engine"));

  // Input Error
  if(_argc != 3) { 
    std::cout << "Error: incorrect number of arguments, usage is\n ./spiderling <filename.dat> <file directory>" << std::endl; 
  }

  // GL
  initialize();

  //////////////////////////////////////////////////////////////////////////////
  // Assign callback functions
  std::cout << "Assigning Callback functions" << std::endl;
  glutReshapeFunc(resize);
  glutDisplayFunc(draw);
  glutKeyboardFunc(keyPressed);
  glutSpecialFunc(specialKeyPressed);
  glutTimerFunc(1000/FPS, timer, 0);

  //////////////////////////////////////////////////////////////////////////////
  // Parses File and Constructs Objs
  parse(_argv[1], _argv[2]);

  constructBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Start application
  std::cout << "Starting Application" << std::endl;
  glutMainLoop();

  return 0;
}

#if   defined(OSX)
#pragma clang diagnostic pop
#endif
