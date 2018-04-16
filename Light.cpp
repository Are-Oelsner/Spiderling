// Default Constructor
Light::
Light() {
  position = new glm::vec4(0.f, 0.f, 100.f, 0.f); // Directional default behind camera
}

Light::
Light(char* input) {
  parseInput(input);
}

// Point Light Constructor
Light::
Light(glm::vec4 pos, glm::vec3 dir, glm::vec4 amb, glm::vec4 diff, glm::vec4
    spec, float cAtten, float lAtten, float qAtten, float aAtten, float aLim) {
  position = pos;
  direction = dir;
  ambient = amb;
  diffuse = diff;
  specular = spec;
  constantAttenuation = cAtten;
  linearAttenuation = lAtten;
  quadraticAttenuation = qAtten;
  angularAttenuation = aAtten;
  angularLimit = aLim;
}

// Directional Light Constructor
Light::
Light(glm::vec4 pos, glm::vec3 dir, glm::vec4 amb, glm::vec4 diff, glm::vec4 spec) {
  position = pos;
  direction = dir;
  ambient = amb;
  diffuse = diff;
  specular = spec;
}

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

char*
Light::
parseInput(char* input) {
  char* filename = strtok(input, " ");
  char* tmp;
  float x, y, z, t;
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  position = glm::vec4(x, y, z, t); // Sets position
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  direction = glm::vec3(x, y, z); // Sets direction
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  ambient = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  diffuse = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL)
    x = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    y = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    z = atof(tmp);
  if((tmp = strtok(NULL, " ")) != NULL)
    t = atof(tmp);
  specular = glm::vec4(x, y, z, t); // Sets Ambient
  if((tmp = strtok(NULL, " ")) != NULL) // The following only happen for spot/point lights
   constantAttenuation = atof(tmp); // Sets constant Attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    linearAttenuation = atof(tmp);  // Sets linear attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    quadraticAttenuation = atof(tmp);// sets quadratic attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularAttenuation = atof(tmp);  // sets angular attenuation
  if((tmp = strtok(NULL, " ")) != NULL)
    angularLimit = atof(tmp);       // sets angular Limit
  return filename;
}

