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

// STL
#include <cmath>
#include <chrono>
#include <iostream>
#include <fstream>

#include <string>
#include <string.h>
#include <vector>
#include <sstream>


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

// My Files
#include "Obj.h"
#include "WindowClass.h"
#include "Camera.h"

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
vector<Obj> objs;


// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

// Vertex Array Object, Vertex Buffer Object (vertices, normals, vertex indices, normal indices)
GLuint vao, vbo[1], ebo[1];
//vector<GLuint> vbo;
//vector<GLuint> ebo;


////////////////////////////////////////////////////////////////////////////////
// Functions

////////////////////////////////////////////////////////////////////////////////
/// @brief Initialize GL settings
void
initialize() {
  glClearColor(0.f, 0.f, 0.4f, 0.f);
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
  gluPerspective(45.f, GLfloat(m_window.width())/m_window.height(), 0.01f, 100.f);
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
    case 111:       // o    zoom out
      cam.eye(2, 0.5);
      cam.at(2, 0.5);
      break;
    case 105:       // i    zoom in
      cam.eye(2, -0.5);
      cam.at(2, -0.5);
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
  //case 116:       // t    test transform
  //  cam.mTransform();
  //  break;
    case 117:       // u    test hLook
      cam.hLook(.1);
      break;
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
      cam.eye(0, -0.1);
      cam.at(0, -0.1);
      break;
    case GLUT_KEY_RIGHT:
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

////////////////////////////////////////////////////////////////////////////////
/// @brief constructBuffers
void
constructBuffers() {
  glGenBuffers(objs.size(), ebo);
  glGenBuffers(objs.size(), vbo);
  for(int i = 0; i < objs.size(); i++) {
    ////////////////////////////////////////////////////////////////////////////
    /// Element Buffer Object
    ////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*objs[i].getIndices()->size(), objs[i].getIndices()->data(), GL_STATIC_DRAW);


    ////////////////////////////////////////////////////////////////////////////
    /// Vertex Array Object
    ////////////////////////////////////////////////////////////////////////////
    //glGenVertexArrays(1, &vao); 
    //glBindVertexArray(vao);     // Bind VAO


    ////////////////////////////////////////////////////////////////////////////
    /// Vertex Buffer Object
    ////////////////////////////////////////////////////////////////////////////
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VEC6)*objs[i].getData()->size(), objs[i].getData()->data(), GL_STATIC_DRAW);



    //glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(glm::vec3)*objs[i].getData()->size(), objs[i].getData()->data());

    /// For without VAO
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glVertexPointer(3, GL_FLOAT, 0, NULL);

    //glBufferSubData(GL_ARRAY_BUFFER, sizeof(*objs[i].getVertices()), sizeof(*objs[i].getNormals()) , objs[i].getNormals());
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(*objs[i].getVertices()));
    //glEnableVertexAttribArray(1); // Enables attribute index 1 as being used
  }
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

  // Single directional light
  static GLfloat lightPosition[] = { 0.5f, 1.0f, 1.5f, 0.0f };
  static GLfloat whiteLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  static GLfloat darkLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, darkLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);

  // Camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cam.eye(0), cam.eye(1), cam.eye(2), cam.at(0), cam.at(1), cam.at(2), cam.getUp(0), cam.getUp(1), cam.getUp(2)); //change to pan for center TODO
  //gluLookAt(cam.eX()*std::sin(cam.theta(), cam.eY(), cam.eZ()*std::cos(cam.theta()),
  //gluLookAt(10*std::sin(cam.theta()), 0.f, 10*std::cos(cam.theta()), 0.f, 0.f, 0.f, 0.f, 1.f, 0.f);


  //glColor3f(0.6f, 0.f, 0.f);
  glPointSize(10);



  for(int i = 0; i < objs.size(); i++) {
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    //float mat[16];
    //glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    //printf("Modelview: \n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n%f\t%f\t%f\t%f\n\n", mat[0], mat[1], mat[2], mat[3], mat[4], mat[5], mat[6], mat[7], mat[8], mat[9], mat[10], mat[11], mat[12], mat[13], mat[14], mat[15]);

    //glPushMatrix();
    //glTranslatef((GLfloat) 0, (GLfloat) 0, (GLfloat) 0);

    glColor3f(objs[i].getColor(0), objs[i].getColor(1), objs[i].getColor(2));



    //glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[i]); // Bind EBO
    //glEnableClientState(GL_INDEX_ARRAY);


    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]); // Bind VBO

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(objs[i].getMode(), GL_FLOAT, sizeof(VEC6), (GLvoid*)NULL);

    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(VEC6), (GLvoid*)(sizeof(glm::vec3)));

    if(objs[i].getMode() == 4) 
      glDrawElements(GL_QUADS, objs[i].getIndices()->size(), GL_UNSIGNED_INT, 0);
    else 
      glDrawElements(GL_TRIANGLES, objs[i].getIndices()->size(), GL_UNSIGNED_INT, 0);
    //glPopMatrix();
  }


  //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);//TODO may not be GL_FLOAT since glm::vec3
  //glEnableVertexAttribArray(0); // Enables attribute index 0 as being used

  //glDrawRangeElements(GL_QUADS, 0, objs[i].getIndices()->size()-1, objs[i].getIndices()->size()/4, GL_UNSIGNED_INT, 0);
  // For unindexed 
  //glDrawArrays(GL_POINTS, 0, objs[i].getNumVertices());


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
  if(_argc > 3) { 
    std::cout << "Error: incorrect number of arguments, usage is\n ./spiderling <0/1 debug>" << std::endl; 
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

  ifstream objFile;
  objFile.open(_argv[1]);
  string filename;
  Obj* obj;
  while(getline(objFile, filename)) {
    obj = new Obj(filename.c_str());
    printf("Object: %s\n", filename.c_str());
    obj->print(atoi(_argv[2]));
    objs.push_back(*obj);
  }
  objFile.close();

  for(int i = 0; i < objs.size(); i++) {
    objs[i].setPosition(glm::vec4(i*2, i*2, i*2, 1.));
    objs[i].setColor((double)(rand()/(RAND_MAX)), (double)rand()/(RAND_MAX), (double)rand()/(RAND_MAX));
  }

  //////////////////////////////////////////////////////////////////////////////
  // Construct Buffers
  constructBuffers();

  // Start application
  std::cout << "Starting Application" << std::endl;
  glutMainLoop();

  return 0;
}

#if   defined(OSX)
#pragma clang diagnostic pop
#endif
