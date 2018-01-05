#pragma once


#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "heightmapHandler.hh"
#include "waterRenderer.hh"
#include "shaderHandler.hh"
#include "camera.hh"

class DrawHandler
{
public:

    DrawHandler(void);
    void draw(Camera* camera, uint width, uint height);

private:

    unsigned int vbo_;
    unsigned int vao_;
    
    Shader waterShader_;
    Shader heightmapShader_;

    HeightmapHandler heightmap_;
    WaterRenderer waterRenderer_;

};