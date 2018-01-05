#include "drawHandler.hh"

//#include <glad/glad.h>

float vertices[] = {
     0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
};

DrawHandler::DrawHandler()
  : vbo_(0),
  vao_(0),
  basicShader_("shaders/basic.vs", "shaders/basic.fs"),
  heightmapShader_("shaders/heightmap.vs", "shaders/heightmap.fs"),
  heightmap_(HeightmapHandler(heightmapShader_, "assets/height_map.jpg")),
  waterRenderer_(WaterRenderer(heightmapShader_))
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  int posattrib = glGetAttribLocation(basicShader_.ID, "position");
  glEnableVertexAttribArray(posattrib);
  glVertexAttribPointer(posattrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), 0);
  basicShader_.use();
  /*int colattrib = glGetAttribLocation(basicShader_.ID, "color");
  glEnableVertexAttribArray(colattrib);
  glVertexAttribPointer(colattrib, 3, GL_FLOAT, GL_FALSE, 
  5 * sizeof (float), (void*) (2 * sizeof (float)));
  basicShader_.use();*/

}

void DrawHandler::draw(Camera* camera, uint width, uint height)
{
  //basicShader_.use();
  /*glm::mat4 view = camera->get_view_matrix();
  glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()),
						static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
  glm::mat4 model;
  model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(0.0f), 
  glm::vec3(1.0f, 0.0f, 0.0f));
  basicShader_.setMat4("projection", projection);
  basicShader_.setMat4("view", view);
  basicShader_.setMat4("model", model);

  glDrawArrays(GL_TRIANGLES, 0, 3);*/
  // activate shader for map mesh ! !
  glm::mat4 view = camera->get_view_matrix();
  glm::mat4 projection = glm::perspective(glm::radians(camera->get_zoom()),
						static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
  //std::cout << glm::to_string(view) << " " << glm::to_string(projection) << std::endl;
  heightmap_.RenderHeightmap(projection, view);
  waterRenderer_.RenderWater(projection, view);
}