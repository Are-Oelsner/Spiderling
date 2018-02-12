#include "Camera.h"

Camera::
Camera() {
  g_theta = 0.f;
}

Camera::
Camera(float theta) {
  g_theta = theta;
}

float
Camera::
theta() {
  return g_theta;
}

void
Camera::
theta(float theta) {
  g_theta = theta;
}

void
Camera::
incTheta(float inc) {
  g_theta += inc;
}
