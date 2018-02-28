#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
  eyeX = 0;
  eyeY = 10;
  eyeZ = 30;

  centerX = 0;
  centerY = 0;
  centerZ = 0;

  upX = 0;
  upY = 1;
  upZ = 0;
}

void
Camera::
reset() {
  g_theta = 0.f;
  eyeX = 0;
  eyeY = 0;
  eyeZ = 20;

  centerX = 0;
  centerY = 0;
  centerZ = 0;

  upX = 0;
  upY = 1;
  upZ = 0;
}
