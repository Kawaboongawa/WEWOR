#include <glm/glm.hpp>

#include "waterRenderer.hh"
#include "fish.hh"

// probability to have a tree on a tile in percent
#define FISH_PROBA 1

Fish::Fish(std::string const &path, HeightmapHandler heightMapHandler,
    Shader shader, bool gamma)
  : path_(path),
  heightMapHandler_(heightMapHandler),
  shader_(shader),
  model_(Model(path_, shader_))
{
  uint rows = heightMapHandler.getRows();
  uint cols = heightMapHandler.getCols();
  for (uint i = 0; i < rows; ++i)
    for (uint j = 0; j < cols; ++j)
    {
      float randValue = (rand() % 10000) / 100.0;
      float height = heightMapHandler.getHeight(i, j);
      if (height < WaterRenderer::getWaterHeight() && randValue < FISH_PROBA)
      {
        pos_.push_back(glm::vec3(i, WaterRenderer::getWaterHeight() - 1, j));
        float scaleValue = (rand() % 20) / 10.0 + 0.5;
        scaleValue = 0.06f - (rand() % 5) / 100.0f;
        scale_.push_back(glm::vec3(scaleValue, scaleValue, scaleValue));
        float randAngle = (rand() % 360) * M_PI / 180.0f;
        float dirX = abs(cos(randAngle));
        float dirY = abs(sin(randAngle));
        float newX = 1 / (dirX / dirY + 1);
        float newY = 1 / (dirY / dirX + 1);
        newX /= 10.0f + rand() % 20;
        newY /= 10.0f + rand() % 20;
        dir_.push_back(glm::vec3(newX, 0.0f, newY));
      }
    }
}

void Fish::draw(glm::mat4 projection_mat, glm::mat4 view_mat, glm::vec4 plane)
{
  for (size_t i = 0; i < pos_.size(); ++i)
  {
    glm::vec3 newPos = pos_[i] + dir_[i];
    if (newPos.x >= 0 && newPos.x < 256
        && newPos.z >= 0 && newPos.z < 256
        && heightMapHandler_.getHeight(newPos.x, newPos.z) < WaterRenderer::getWaterHeight() - 1)
      {
        pos_[i] = newPos;
      }
      else
      {
        dir_[i].x = -dir_[i].x;
        dir_[i].z = -dir_[i].z;
      }
    model_.draw(projection_mat, view_mat, plane, pos_[i], scale_[i], dir_[i]);
  }
}
