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

    WaterRenderer(Shader shader, uint cols, uint rows);

    void RenderWater( glm::mat4 projection_mat,
                          glm::mat4 view_mat);

    void initIndices(int size);

private:
    
    uint rows_;
    uint cols_;

    uint vao_;
    uint vbo_;
    uint ebo_;

    std::vector<uint> indices_;
    std::vector<float> data_;

    Shader shader_;
    std::vector<uint> textures_;
};