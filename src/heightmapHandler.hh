#pragma once

#include <FreeImage.h>
#include <iostream>

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "shaderHandler.hh"
#include "tools.hh"


class HeightmapHandler 
{ 
public: 

   HeightmapHandler();
  
   static bool LoadTerrainShaderProgram(); 
   static void ReleaseTerrainShaderProgram(); 

   int LoadHeightMapFromImage(std::string sImagePath); 
   void ReleaseHeightmap(); 

   void RenderHeightmap(); 

   void SetRenderSize(float fQuadSize, float fHeight); 
   void SetRenderSize(float fRenderX, float fHeight, float fRenderZ); 

   int GetNumHeightmapRows(); 
   int GetNumHeightmapCols(); 

   static Shader* GetShaderProgram(); 

 

private: 
   uint vao_; 

   bool loaded_; 
   bool shaderProgramLoaded_; 
   int rows_; 
   int cols_; 

   glm::vec3 renderScale_; 

   uint heightmapDatavbo_; 
   uint heightmapIndicesvbo_; 

   static Shader spTerrain_; 
   //static CShader shTerrainShaders[NUMTERRAINSHADERS]; 
};