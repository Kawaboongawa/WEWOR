#include "waterRenderer.hh"

#include <iostream>

WaterRenderer::WaterRenderer(Shader shader, uint cols, uint rows)
:     rows_(rows),
      cols_(cols),
      indices_(std::vector<uint>()),
      data_(std::vector<float>()),
      shader_(shader),
      textures_(std::vector<uint>())
{

  for (uint z = 0; z < rows_; ++z)
        for (uint x = 0; x < cols_; ++x)
        {
            data_.push_back(static_cast<float>(x));
            data_.push_back(10);
            data_.push_back(static_cast<float>(z));
            data_.push_back(static_cast<float>(x));
            data_.push_back(static_cast<float>(z));
        }
  /*TEXTURE Initialization*/
  textures_.push_back(loadTexturegl("assets/water.jpg"));
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures_[0]);
   

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

}

void WaterRenderer::RenderWater(glm::mat4 projection_mat,
                                       glm::mat4 view_mat)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures_[0]);

    shader_.use();

    shader_.setMat4("projection", projection_mat);
    shader_.setMat4("view", view_mat);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f));
    shader_.setMat4("model", model);
 
  //Water
  shader_.setInt("texture1", 0);

  glBindVertexArray(vao_);

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