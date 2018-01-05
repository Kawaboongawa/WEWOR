#pragma once

#include <vector>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "tools.hh"



class VertexBufferObject
{
public:
	
  VertexBufferObject();
  ~VertexBufferObject();

  void CreateVBO(int size = 0);
	/*void* MapBufferToMemory(int iUsageHint);
	void* MapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength);
	void UnmapBuffer();
  */
	void BindVBO(int buffer_type);
	void UploadDataToGPU(int draw_type);
	
	void AddData(void* ptr_data, uint data_size);

	void* GetDataPointer();
	uint GetBufferID();

	int GetCurrentSize();

private:
	uint buffer_;
	int size_;
	int index_;
	int bufferType_;
	std::vector<uchar> data_;

	bool bDataUploaded;
};