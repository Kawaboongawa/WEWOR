#pragma once


#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>

#include "shaderHandler.hh"

class DrawHandler
{
public:

    DrawHandler(void);
    void draw(void);

private:

    unsigned int vbo_;
    unsigned int vao_;
    Shader basicShader_;
};