#pragma once

#include <glad/glad.h>

#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include <vector>
#include "shaderHandler.hh"
#include "tools.hh"

class WaterRenderer
{

public:

    WaterRenderer(Shader shader, uint cols, uint rows,
     uint width, uint height);

    ~WaterRenderer();

    void RenderWater( glm::mat4 projection_mat,
                          glm::mat4 view_mat);

    void initIndices(int size);

private:
    
    uint rows_;
    uint cols_;

    uint vao_;
    uint vbo_;
    uint ebo_;
    uint fboRefrac_;
    uint fboReflec_;

    std::vector<uint> indices_;
    std::vector<float> data_;

    Shader shader_;
    std::vector<uint> textures_;

    uint windowWidth_;
    uint WindowHeight_;

    const int reflectionWidth_ = 320;
    const int reflectionHeight_ = 180;
     
    const int refractionWidth_ = 1280;
    const int refractionHeight_ = 720;
 
};