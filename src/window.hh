#pragma once

#include "drawHandler.hh"
#include "camera.hh"
#include "input.hh"

class Window
{
  public:
    Window(int width, int height);
    ~Window();
    int init_render(void);
    int render_loop(void);
    
  private:

    const int screenWidth_;
    const int screenHeight_;
    DrawHandler* d_;
    GLFWwindow* window_;
    Camera* camera_;
};