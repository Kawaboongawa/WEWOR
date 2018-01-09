#include <glm/glm.hpp>

#include "waterRenderer.hh"
#include "tree.hh"

// probability to have a tree on a tile in percent
#define TREE_PROBA 0.1

Tree::Tree(std::string const &path, HeightmapHandler heightMapHandler, Shader shader, bool gamma)
  : path_(path),
  shader_(shader),
  model_(Model(path_, shader_))
{
  uint rows = heightMapHandler.getRows();
  uint cols = heightMapHandler.getCols();
  for (uint i = 0; i < rows; ++i)
    for (uint j = 0; j < cols; ++j)
    {
      float randValue = (rand() % 10000) / 100.0;
      if (randValue < TREE_PROBA)
      {
        float height = heightMapHandler.getHeight(i, j);
        if (height > WaterRenderer::getWaterHeight())
          pos_.push_back(glm::vec3(i, height, j));
      }
    }
}

void Tree::draw(glm::mat4 projection_mat, glm::mat4 view_mat, glm::vec4 plane)
{
  for (auto &elt : pos_)
  {
    model_.draw(projection_mat, view_mat, plane, elt);
  }
}
