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
  basicShader_("shaders/basic.vs", "shaders/basic.fs")
{
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  int posattrib = glGetAttribLocation(basicShader_.ID, "position");
  glEnableVertexAttribArray(posattrib);
  glVertexAttribPointer(posattrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof (float), 0);

  int colattrib = glGetAttribLocation(basicShader_.ID, "color");
  glEnableVertexAttribArray(colattrib);
  glVertexAttribPointer(colattrib, 3, GL_FLOAT, GL_FALSE, 
  5 * sizeof (float), (void*) (2 * sizeof (float)));
  basicShader_.use();
}

void DrawHandler::draw(void)
{
  glDrawArrays(GL_TRIANGLES, 0, 3);
}