#include "skybox.hh"

float skyboxVertices[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


Skybox::Skybox(Shader shader)
: indices_(std::vector<uint>()),
  data_(std::vector<float>()),
  shader_(shader),
  texture_(0)
{

  std::vector<std::string> faces
  {
    "assets/skybox/sky-right.jpg",
    "assets/skybox/sky-left.jpg",
    "assets/skybox/sky-top.jpg",
    "assets/skybox/sky-bottom.jpg",
    "assets/skybox/sky-back.jpg",
    "assets/skybox/sky-front.jpg"
  };
  texture_ = loadCubemap(faces);
  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glBindVertexArray(vao_);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  shader_.use();
  glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
}

 void Skybox::RenderSkybox(glm::mat4 projection_mat,
				 glm::mat4 view_mat)
{
  //glm::mat4 view = glm::mat4(glm::mat3(view_mat);
  glDepthMask(GL_FALSE);

  shader_.use();
  shader_.setMat4("view", view_mat);
	shader_.setMat4("projection", projection_mat);
  shader_.setInt("skybox", 0);
  glBindVertexArray(vao_);
  
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
	glDrawArrays(GL_TRIANGLES, 0, 36);
  //glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}
