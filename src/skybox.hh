#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include "shaderHandler.hh"
#include "tools.hh"

class Skybox
{
public:

    static Skybox& getSkybox(void);

    void loadSkybox(void);

    void RenderSkybox(glm::mat4 projection_mat,
				 glm::mat4 view_mat);

    void changeSkybox(void);

private:

    Skybox(Shader shader);

    uint rows_;
    uint cols_;

    uint vao_;
    uint vbo_;
    uint ebo_;


    std::vector<uint> indices_;
    std::vector<float> data_;

    Shader shader_;

    uint texture_;

    uint nsky_;
};