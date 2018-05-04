#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Material { // Struct to store values from mtl file
  public:
    glm::vec3 Ka = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 Kd = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 Ks = glm::vec3(1.f, 1.f, 1.f);
    float Ns = 1.0f; // shininess of the material
    unsigned int illum = 2; // represents illumination model 1:flat 2:specular highlights
};

#endif
