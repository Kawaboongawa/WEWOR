CXX = g++
CXXFLAGS = -Wall -std=c++14 -pedantic  -g
LDFLAGS = -lglfw3 -lGL -lm -ldl -lXinerama -lXrandr -lXi \
-lXcursor -lX11 -lXxf86vm -lpthread -lglut -lGL -lGLU -lfreeimage -lassimp

DIR = src
SOURCE = ${addprefix ${DIR}/, glad.c main.cc drawHandler.cc shaderHandler.cc \
window.cc camera.cc input.cc heightmapHandler.cc vertexBufferObject.cc \
tools.cc waterRenderer.cc skybox.cc mesh.cc model.cc tree.cc}

INC_DIR = inc/
OBJ = $(SOURCE:%.cc=%.o)
OBJc = $(SOURCE:%.c=%.o)

BIN = water

all: $(OBJc) $(OBJ)
	$(CXX) $(CXXFLAGS) -o ${BIN} $(OBJ) $(LDFLAGS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INC_DIR)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I$(INC_DIR)

clean:
	$(RM) $(DIR)/*.o $(BIN)

.PHONY: all clean
