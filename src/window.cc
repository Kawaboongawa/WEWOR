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


void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
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
    glfwSetFramebufferSizeCallback(window_, framebufferSizeCallback);
    glfwSetCursorPosCallback(window_, &Input::mouse_callback);
    glfwSetScrollCallback(window_, &Input::scroll_callback);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    camera_ = new Camera(glm::vec3(0.0f, 50.0f, 0.0f),
                         glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 0.f);
    auto& input = Input::get_instance();
    input.init(camera_, screenWidth_, screenWidth_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return 1;
    }

    glEnable(GL_DEPTH_TEST);  

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

        //draw
    	glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_->draw(camera_, screenWidth_, screenHeight_);
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
