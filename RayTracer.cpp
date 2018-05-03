#include "RayTracer.h"

RayTracer::
RayTracer() {
}

RayTracer::
RayTracer(WindowClass* win) {
  window = win;
  pixelColors = make_unique<glm::vec4[]>(window->width() * window->height());
}

