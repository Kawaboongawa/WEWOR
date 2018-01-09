#pragma once

#include <glad/glad.h>

#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include <vector>

#include "shaderHandler.hh"
#include "tools.hh"
#include "input.hh"

class WaterRenderer
{

public:

    WaterRenderer(Shader shader, uint cols, uint rows,
                  uint width, uint height);

    ~WaterRenderer();

    void RenderWater( glm::mat4 projection_mat,
                      glm::mat4 view_mat, 
                      glm::vec4 plane,
                      glm::vec3 camera_pos);

    void initIndices(int size);

    void bindReflectionFrameBuffer();

    void bindRefractionFrameBuffer();

    void unbindCurrentFrameBuffer(uint width, uint height);
    
    /**
     * GETTERS/SETTERS
     **/

    static uint getWaterHeight();

private:

    uint rows_;
    uint cols_;

    uint vao_;
    uint vbo_;
    uint ebo_;

    std::vector<uint> indices_;
    std::vector<float> data_;

    Shader shader_;

    uint fboReflec_;
    uint reflecTexture_;
    uint reflecDepthBuffer_;

    uint fboRefrac_;
    uint refracTexture_;
    uint refracDepthTexture_;
    uint dudvTexture_;
    uint normalTexture_;

    uint windowWidth_;
    uint WindowHeight_;

    float moveFactor_;

    const int reflectionWidth_ = 320;
    const int reflectionHeight_ = 180;

    const int refractionWidth_ = 1280;
    const int refractionHeight_ = 720;

    static const int waterHeight_ = 10;

    const float waveSpeed_ = 0.03f;


};
