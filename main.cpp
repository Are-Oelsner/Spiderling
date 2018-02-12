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
Camera m_camera;

////////////////////////////////////////////////////////////////////////////////
// Object from .obj file specified by argv[1] in main
Obj obj1;


// Frame rate
const unsigned int FPS = 60;
float g_frameRate{0.f};
std::chrono::high_resolution_clock::time_point g_frameTime{
  std::chrono::high_resolution_clock::now()};
float g_delay{0.f};
float g_framesPerSecond{0.f};

// Vertex Array Object, Vertex Buffer Object (vertices, normals, vertex indices, normal indices)
GLuint vao, vbo[1], ebo[1];


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
  gluLookAt(10*std::sin(m_camera.theta()), m_camera.getEyeY(), m_camera.getEyeZ()*std::cos(m_camera.theta()),
      0.f, 0.f, 0.f, 0.f, 1.f, 0.f);
//gluLookAt(10*std::sin(m_camera.theta()), 0.f, 10*std::cos(m_camera.theta()),
//    0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

  glColor3f(0.6f, 0.f, 0.f);

  //////////////////////////////////////////////////////////////////////////////
  // TODO my code
  glBegin(GL_TRIANGLES);
  int j = 0;
  glm::vec3 tmp;
  for(int i = 0; i < obj1.getNumVertexIndices(); i += 3) {        //For each triangle
    tmp = obj1.getNormals()->at(obj1.getNormalIndices()->at(j));    //Triangle Normal
    glNormal3f(tmp[0], tmp[1], tmp[2]);

    tmp = obj1.getVertices()->at(obj1.getVertexIndices()->at(i));   //First point
    glVertex3f(tmp[0], tmp[1], tmp[2]);
    tmp = obj1.getVertices()->at(obj1.getVertexIndices()->at(i+1)); //Second Point
    glVertex3f(tmp[0], tmp[1], tmp[2]);
    tmp = obj1.getVertices()->at(obj1.getVertexIndices()->at(i+2)); //Third point
    glVertex3f(tmp[0], tmp[1], tmp[2]);
    j++;
  }

  glEnd();



//glBindVertexArray(vao);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]); // Bind EBO
//glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // Bind VBO
//glDrawElements(GL_TRIANGLES, obj1.getNumVertices(), GL_UNSIGNED_INT, 0);

  //////////////////////////////////////////////////////////////////////////////
  // Show
  glutSwapBuffers();

  //////////////////////////////////////////////////////////////////////////////
  // Record frame time
  high_resolution_clock::time_point time = high_resolution_clock::now();
  g_frameRate = duration_cast<duration<float>>(time - g_frameTime).count();
  g_frameTime = time;
  g_framesPerSecond = 1.f/(g_delay + g_frameRate);
  printf("FPS: %6.2f\n", g_framesPerSecond);
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
    case 106:
      std::cout << "Model Display: Filled" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
    case 107:
      std::cout << "Model Display: Wireframe" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case 108:
      std::cout << "Model Display: Points" << std::endl;
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      break;
    case 111:
      m_camera.incrementZ(0.5);
      break;
    case 105:
      m_camera.incrementZ(-0.5);
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
      m_camera.incTheta(-0.1);
      break;
    case GLUT_KEY_RIGHT:
      m_camera.incTheta(0.1);
      break;
    case GLUT_KEY_UP:
      m_camera.incrementY(0.5);
      break;
    case GLUT_KEY_DOWN:
      m_camera.incrementY(-0.5);
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
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  /// Final Approach
  ////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////
  /// Element Buffer Object
  ////////////////////////////////////////////////////////////////////////////
  glGenBuffers(1, ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
  //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*obj1.getVertices()) + sizeof(*obj1.getNormals()), NULL GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*obj1.getVertices()), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(*obj1.getVertices()), obj1.getVertices());
  //glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*obj1.getVertices()), sizeof(*obj1.getNormals()) , obj1.getNormals());


  ////////////////////////////////////////////////////////////////////////////
  /// Vertex Array Object
  ////////////////////////////////////////////////////////////////////////////
//glGenVertexArrays(1, &vao); 
//glBindVertexArray(vao);     // Bind VAO


  ////////////////////////////////////////////////////////////////////////////
  /// Vertex Buffer Object
  ////////////////////////////////////////////////////////////////////////////
  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(*obj1.getVertices()) + sizeof(*obj1.getNormals()), NULL, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*obj1.getVertices()), obj1.getVertices());
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(*obj1.getVertices()), sizeof(*obj1.getNormals()) , obj1.getNormals());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);//TODO may not be GL_FLOAT since glm::vec3
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid *)sizeof(*obj1.getVertices()));
  glEnableVertexAttribArray(0); // Enables attribute index 0 as being used
  glEnableVertexAttribArray(1); // Enables attribute index 1 as being used
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
  if(_argc != 2) { 
    std::cout << "Error: incorrect number of arguments, usage is\n ./spiderling filename.obj" << std::endl; 
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

  // Constructs Obj from .obj file. 
  obj1.loadOBJ(_argv[1]); 

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
