#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "shader.hpp"
#include "string"
#include "camera.hpp"

class Mesh {
public:
    virtual void draw() = 0;
    virtual void setupMesh() = 0;
    virtual void updateShaderBindings(Camera cam, glm::vec3 lightPos, unsigned int depthMap) = 0;

    unsigned int VAO, VBO, EBO;
};
#endif