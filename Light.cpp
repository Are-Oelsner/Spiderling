
void
Light::
draw() {
  glBegin(GL_POINTS);
  for(int j = 0; j < numParticles; j++) {
    glColor3f((GLfloat)data.at(j).color[0], (GLfloat)data.at(j).color[1], (GLfloat)data.at(j).color[2]); 
    glVertex3f((GLfloat)data.at(j).position[0], (GLfloat)data.at(j).position[1], (GLfloat)data.at(j).position[2]);
  }
  glEnd();
}

