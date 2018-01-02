#include <iostream>
#define GLFW_INCLUDE_NONE

#include "drawHandler.hh"

int render()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr,
                                          nullptr); // Windowed
    //GLFWwindow *window = glfwCreateWindow(
    //                         800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr); // Fullscreen
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
                                                                                           
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))                                   
    {                                                                                          
            std::cout << "Failed to initialize GLAD" << std::endl;                             
            return 1;                                                                       
    }                                                                                          
                    
    DrawHandler d;
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        d.draw();
    }
    glfwTerminate();
    return 0;
}

int main()
{

    return render();

}
