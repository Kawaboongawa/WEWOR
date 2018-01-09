#pragma once

#include <FreeImage.h>
#include <iostream>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include "shaderHandler.hh"
#include "tools.hh"
#include "vertexBufferObject.hh"

class HeightmapHandler
{
public:

    HeightmapHandler(Shader shader, std::string path);

    int LoadHeightMapFromImage(std::string sImagePath);

    void RenderHeightmap( glm::mat4 projection_mat,
				 glm::mat4 view_mat, glm::vec4 plane);

    void initIndices(int size);

    uint getRows(void);

    uint getCols(void);
    float getHeight(int x, int y);

private:

    uint rows_;
    uint cols_;

    glm::vec3 renderScale_;

    uint vao_;
    uint vbo_;
    uint ebo_;

    std::vector<uint> indices_;
    std::vector<float> data_;

    Shader shader_;

    float maxHeight_;

    std::vector<uint> textures_;

   

};
