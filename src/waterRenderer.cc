#include "waterRenderer.hh"

float vertices2[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

WaterRenderer::WaterRenderer(Shader shader)
:     vbo_(0),
      ebo_(0),
      indices_(std::vector<uint>()),
      data_(std::vector<float>()),
      shader_(shader)
{

  rows_ = 10;
  cols_ = 10;
  std::vector<float> vertex_data;
  for (uint i = 0; i < rows_; ++i)
      for (uint j = 0; j < cols_; ++j)
        {
            
            //float scaleC = static_cast<float>(j) / static_cast<float>(cols_ - 1);
            //float scaleR = static_cast<float>(i) / static_cast<float>(rows_ - 1);
            data_.push_back(i);
            data_.push_back(3);
            data_.push_back(j);
        }

  
  initIndices(rows_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, data_.size(), &data_[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size(), &indices_[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), 0);
  glEnableVertexAttribArray(0);
}

void WaterRenderer::RenderWater(glm::mat4 projection_mat,
                                       glm::mat4 view_mat)
{
    shader_.use();

    shader_.setMat4("projection", projection_mat);
    shader_.setMat4("view", view_mat);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f));
    shader_.setMat4("model", model);
    /*
    shader_.setFloat("fRenderHeight", renderScale_.y);
    shader_.setFloat("fMaxTextureU", float(cols_) * 0.1f);
    shader_.setFloat("fMaxTextureV", float(rows_) * 0.1f);

    shader_.setMat4("HeightmapScaleMatrix", glm::scale(glm::mat4(1.0), glm::vec3(renderScale_)));
    */
    // Now we're ready to render - we are drawing set of triangle strips using one call, but we g otta enable primitive restart
    glBindVertexArray(vao_);
    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(rows_ * cols_);

    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
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