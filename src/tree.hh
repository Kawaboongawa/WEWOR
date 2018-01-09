#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "model.hh"
#include "heightmapHandler.hh"
#include "shaderHandler.hh"

class Tree
{
  public:
    Tree(std::string const &path, std::string const &path2,
        HeightmapHandler heightMapHandler, Shader shader, bool gamma = false);
    void draw(glm::mat4 projection_mat, glm::mat4 view_mat, glm::vec4 plane);
  private:
    std::string const &path_;
    std::string const &path2_;
    Shader shader_;
    Model model_;
    Model model2_;
    std::vector<glm::vec3> pos_;
    std::vector<glm::vec3> pos2_;
    std::vector<glm::vec3> scale_;
    std::vector<glm::vec3> scale2_;
};
