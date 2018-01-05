#include "drawHandler.hh"

//#include <glad/glad.h>

float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

DrawHandler::DrawHandler()
  : heightmap_(HeightmapHandler(Shader("shaders/water.vs", "shaders/water.fs"), "assets/height_map.jpg")),
  waterRenderer_(WaterRenderer(Shader("shaders/heightmap.vs", "shaders/heightmap.fs"), heightmap_.getCols(), heightmap_.getRows())),
  skybox_(Skybox(Shader("shaders/skybox.vs", "shaders/skybox.fs")))
{}

void DrawHandler::draw(Camera* camera, uint width, uint height)
{
  glm::mat4 view = camera->get_view_matrix();
  glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()),
						static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
  skybox_.RenderSkybox(projection, glm::mat4(glm::mat3(view)));
  heightmap_.RenderHeightmap(projection, view);
  waterRenderer_.RenderWater(projection, view);
  

}