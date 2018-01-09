#include "drawHandler.hh"

//#include <glad/glad.h>

float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

DrawHandler::DrawHandler(uint width, uint height)
  : heightmap_(HeightmapHandler(Shader("shaders/heightmap.vs", "shaders/heightmap.fs"), "assets/height_map.jpg")),
  waterRenderer_(WaterRenderer(Shader("shaders/water.vs", "shaders/water.fs"), 
  heightmap_.getCols(), heightmap_.getRows(), width, height)),
  //skybox_(Skybox::getSkybox()),
  screenWidth_(width),
  screenHeight_(height)
{}

DrawHandler::~DrawHandler(void)
{}

void DrawHandler::draw(Camera* camera, glm::vec4 plane, bool render_water)
{
  glm::mat4 view = camera->get_view_matrix();
  glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()),
						static_cast<float>(screenWidth_) / static_cast<float>(screenHeight_), 0.1f, 1000.0f);
  
  Skybox::getSkybox().RenderSkybox(projection, glm::mat4(glm::mat3(view)));
  heightmap_.RenderHeightmap(projection, view, plane);
  if (render_water)
    waterRenderer_.RenderWater(projection, view, plane, camera->get_view_pos());
}

/**
 * GETTERS/SETTERS
**/

WaterRenderer& DrawHandler::getWaterRenderer()
{
    return waterRenderer_;
}