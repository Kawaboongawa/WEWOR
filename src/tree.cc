#include <glm/glm.hpp>

#include "waterRenderer.hh"
#include "tree.hh"

// probability to have a tree on a tile in percent
#define TREE_PROBA 0.05
#define SEAWEED_PROBA 0.1

Tree::Tree(std::string const &path, std::string const &path2,
    HeightmapHandler heightMapHandler, Shader shader, bool gamma)
  : path_(path),
  path2_(path2),
  shader_(shader),
  model_(Model(path_, shader_)),
  model2_(Model(path2_, shader_))
{
  uint rows = heightMapHandler.getRows();
  uint cols = heightMapHandler.getCols();
  for (uint i = 0; i < rows; ++i)
    for (uint j = 0; j < cols; ++j)
    {
      float randValue = (rand() % 10000) / 100.0;
      float height = heightMapHandler.getHeight(i, j);
      if (height > WaterRenderer::getWaterHeight() && randValue < TREE_PROBA)
      {
        pos_.push_back(glm::vec3(i, height, j));
        float scaleValue = (rand() % 20) / 10.0 + 0.5;
        scale_.push_back(glm::vec3(scaleValue, scaleValue, scaleValue));
      }
      if (height < WaterRenderer::getWaterHeight() && randValue < SEAWEED_PROBA)
      {
        pos2_.push_back(glm::vec3(i, height, j));
        float scaleValue = (rand() % 20) / 10.0 + 0.5;
        scale2_.push_back(glm::vec3(scaleValue, scaleValue, scaleValue));
      }
    }
}

void Tree::draw(glm::mat4 projection_mat, glm::mat4 view_mat, glm::vec4 plane)
{
  for (size_t i = 0; i < pos_.size(); ++i)
  {
    model_.draw(projection_mat, view_mat, plane, pos_[i], scale_[i]);
  }
  for (size_t i = 0; i < pos2_.size(); ++i)
  {
    model2_.draw(projection_mat, view_mat, plane, pos2_[i], scale2_[i]);
  }
}
