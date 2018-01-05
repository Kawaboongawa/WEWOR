#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include "stb_image.h"



typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

uint loadTexturegl(const std::string& path);

uint loadCubemap(std::vector<std::string> faces);