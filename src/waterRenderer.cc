#include "waterRenderer.hh"

#include <iostream>

const int WaterRenderer::waterHeight_ = 15;
const float WaterRenderer::waveSpeed_ = 0.03;

WaterRenderer::WaterRenderer(Shader shader, uint cols, uint rows,
                             uint width, uint height)
    :     rows_(rows),
          cols_(cols),
          indices_(std::vector<uint>()),
          data_(std::vector<float>()),
          shader_(shader),
          windowWidth_(width),
          WindowHeight_(height),
          moveFactor_(0)
{

    for (uint z = 0; z < rows_; ++z)
        for (uint x = 0; x < cols_; ++x)
        {
            data_.push_back(static_cast<float>(x));
            data_.push_back(waterHeight_);
            data_.push_back(static_cast<float>(z));
            data_.push_back(static_cast<float>(x));
            data_.push_back(static_cast<float>(z));
        }



    initIndices(rows_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, data_.size() * sizeof (float), &data_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof (uint), &indices_[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof (float), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), (void *)(sizeof (float) * 3));
    glEnableVertexAttribArray(1);

    /*FRAMEBUFFERS Creation*/

    //fboReflec

    glGenFramebuffers(1, &fboReflec_);
    glBindFramebuffer(GL_FRAMEBUFFER, fboReflec_);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glGenTextures(1, &reflecTexture_);
    glBindTexture(GL_TEXTURE_2D, reflecTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, reflectionWidth_, reflectionHeight_,
                 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, reflecTexture_, 0);

    glGenRenderbuffers(1, &reflecDepthBuffer_);
    glBindRenderbuffer(GL_RENDERBUFFER, reflecDepthBuffer_);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, reflectionWidth_, reflectionHeight_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, reflecDepthBuffer_);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "error while binding reflection framebuffer" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);

    //fboRefrac

    glGenFramebuffers(1, &fboRefrac_);
    glBindFramebuffer(GL_FRAMEBUFFER, fboRefrac_);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    glGenTextures(1, &refracTexture_);
    glBindTexture(GL_TEXTURE_2D, refracTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, refractionWidth_, refractionHeight_,
                 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, refracTexture_, 0);

    glGenTextures(1, &refracDepthTexture_);
    glBindTexture(GL_TEXTURE_2D, refracDepthTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, refractionWidth_, refractionHeight_,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, refracDepthTexture_, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "error while binding reflection framebuffer" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);

    /*TEXTURE Initialization*/
    dudvTexture_ = loadTexturegl("assets/water-dudv.jpg");
    normalTexture_ = loadTexturegl("assets/water-normal.jpg");
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflecTexture_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refracTexture_);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dudvTexture_);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normalTexture_);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, refracDepthTexture_);

}

void WaterRenderer::RenderWater(glm::mat4 projection_mat,
                                glm::mat4 view_mat,
                                glm::vec4 plane,
                                glm::vec3 camera_pos)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, reflecTexture_);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, refracTexture_);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, dudvTexture_);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, normalTexture_);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, refracDepthTexture_);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader_.use();

    moveFactor_ += waveSpeed_ * Input::deltaTime;
    if (moveFactor_ > 1.0f)
        moveFactor_ = 0.0f;
    shader_.setFloat("moveFactor", moveFactor_);
    shader_.setMat4("projection", projection_mat);
    shader_.setMat4("view", view_mat);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f));
    shader_.setMat4("model", model);
    shader_.setVec4("plane", plane);
    //Water
    shader_.setInt("reflecTexture", 0);
    shader_.setInt("refracTexture", 1);
    shader_.setInt("dudvMap", 2);
    shader_.setInt("normalMap", 3);
    shader_.setInt("depthMap", 4);
    shader_.setVec3("cameraPosition", camera_pos);
    glBindVertexArray(vao_);

    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);

    glDisable(GL_BLEND);
}

WaterRenderer::~WaterRenderer()
{
    glDeleteFramebuffers(1, &fboRefrac_);
    glDeleteFramebuffers(1, &fboRefrac_);
}

void WaterRenderer::bindReflectionFrameBuffer()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fboReflec_);
    glViewport(0, 0, reflectionWidth_, reflectionHeight_);
}

void WaterRenderer::bindRefractionFrameBuffer()
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, fboRefrac_);
    glViewport(0, 0, refractionWidth_, refractionHeight_);
}

void WaterRenderer::unbindCurrentFrameBuffer(uint width, uint height)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, width, height);
}

void WaterRenderer::initIndices(int size)
{
    for (int z = 0; z < size - 1; ++z)
    {
        for (int x = 0; x < size - 1; ++x)
        {
            int start = x + z * size;
            indices_.push_back(start);
            indices_.push_back(start + 1);
            indices_.push_back(start + size);
            indices_.push_back(start + 1);
            indices_.push_back(start + 1 + size);
            indices_.push_back(start + size);
        }
    }
}

/**
 * GETTERS/SETTERS
 **/

uint WaterRenderer::getWaterHeight()
{
    return waterHeight_;
}
