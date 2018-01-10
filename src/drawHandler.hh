#pragma once


#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "heightmapHandler.hh"
#include "waterRenderer.hh"
#include "skybox.hh"
#include "shaderHandler.hh"
#include "camera.hh"
#include "tree.hh"
#include "fish.hh"

class DrawHandler
{
public:

    DrawHandler(uint width, uint height);
    ~DrawHandler(void);
    void draw(Camera* camera, glm::vec4 plane, bool render_water = false);

/**
 * GETTERS/SETTERS
**/

WaterRenderer& getWaterRenderer();

private:

    HeightmapHandler heightmap_;
    WaterRenderer waterRenderer_;
    //Skybox skybox_;
    Tree tree_;
    Fish fish_;
    uint screenWidth_;
    uint screenHeight_;
};
