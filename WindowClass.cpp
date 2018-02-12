#include "WindowClass.h"

WindowClass::
WindowClass() {
  g_width = 1360;
  g_height = 768;
  g_window = 0;
}

WindowClass::
WindowClass(int t_width, int t_height, int t_window) {
  g_width = t_width;
  g_height = t_height;
  g_window = t_window;
}


int WindowClass::width() {return g_width;}
int WindowClass::height() {return g_height;}
int WindowClass::window() {return g_window;}

void WindowClass::width(int width) { g_width = width;}
void WindowClass::height(int height) {g_height = height;}
void WindowClass::window(int window) {g_window = window;}
