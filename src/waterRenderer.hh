#pragma once

#include <glad/glad.h>
#include <vector>
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include "shaderHandler.hh"
#include "tools.hh"

class WaterRenderer
{

public:

    WaterRenderer(Shader shader);

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
};