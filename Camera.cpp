#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
  eye[0] = 0;
  eye[1] = 10;
  eye[2] = 30;

  center[0] = 0;
  center[1] = 0;
  center[2] = 0;

  up[0] = 0;
  up[1] = 1;
  up[2] = 0;
}

void
Camera::
reset() {
  g_theta = 0.f;
  eye[0] = 0;
  eye[1] = 0;
  eye[2] = 20;

  center[0] = 0;
  center[1] = 0;
  center[2] = 0;

  up[0] = 0;
  up[1] = 1;
  up[2] = 0;
}


