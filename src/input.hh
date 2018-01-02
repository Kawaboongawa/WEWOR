#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.hh"

class Input
{

public:
    static Input& get_instance();
    static void process_input(GLFWwindow *window);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset,
				double yoffset);
    void init(Camera *camera, unsigned int width, unsigned int height);
    Camera *get_camera();

private:
    Input() { };
    Input(Input const&) = delete;
    void operator=(const Input&) = delete;

    Camera *camera_;

public:
  
    static float lastX_;
    static float lastY_;
    static float deltaTime;
    static float lastFrame;
    static bool first_mouse_;
    static bool terminate_;
};