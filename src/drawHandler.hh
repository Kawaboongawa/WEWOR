#pragma once


#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "heightmapHandler.hh"
#include "waterRenderer.hh"
#include "skybox.hh"
#include "shaderHandler.hh"
#include "camera.hh"

class DrawHandler
{
public:

    DrawHandler(void);
    void draw(Camera* camera, uint width, uint height);

private:

    HeightmapHandler heightmap_;
    WaterRenderer waterRenderer_;
    Skybox skybox_;
};