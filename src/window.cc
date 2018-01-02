#include "window.hh"

#include <iostream>

Window::Window(int width, int height)
    : screenWidth_(width),
      screenHeight_(height)
{}

Window::~Window()
{
    delete d_;
    delete camera_;
    glfwDestroyWindow(window_);
}

int Window::init_render()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(screenWidth_, screenHeight_, "OpenGL", nullptr,
                               nullptr); // Windowed
    //GLFWwindow *window = glfwCreateWindow(
    //                         800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
    if (window_ == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window_);

    camera_ = new Camera(glm::vec3(0.0f, 50.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.f);
    auto& input = Input::get_instance();
    input.init(camera_, screenWidth_, screenWidth_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }
    d_ = new DrawHandler();
    return 0;
}

int Window::render_loop(void)
{
    auto& input = Input::get_instance();
    while (!glfwWindowShouldClose(window_))
    {
        if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window_, GL_TRUE);

        // per-frame time logic
        float currentFrame = glfwGetTime();
        Input::deltaTime = currentFrame - Input::lastFrame;
        Input::lastFrame = currentFrame;

        // input
        input.process_input(window_);
        d_->draw();
        glfwSwapBuffers(window_);
        glfwPollEvents();

    }
    glfwTerminate();
    return 0;
}