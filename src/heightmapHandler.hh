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

    // static void ReleaseTerrainShaderProgram();

    int LoadHeightMapFromImage(std::string sImagePath);
   // void ReleaseHeightmap();

    void RenderHeightmap( glm::mat4 projection_mat,
				 glm::mat4 view_mat);

    //void SetRenderSize(float fQuadSize, float fHeight);
    //void SetRenderSize(float fRenderX, float fHeight, float fRenderZ);

    //int GetNumHeightmapRows();
    //int GetNumHeightmapCols();

    void initIndices(int size);

    static Shader* GetShaderProgram();



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

    //static CShader shTerrainShaders[NUMTERRAINSHADERS];
};