#pragma once

#include <string>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include "stb_image.h"

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

unsigned int load_texturegl(const std::string& path);