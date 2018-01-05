#include "vertexBufferObject.hh"

VertexBufferObject::VertexBufferObject()
: buffer_(0)
{}

VertexBufferObject::~VertexBufferObject()
{
  glDeleteBuffers(1, &buffer_);
	data_.clear();
}

void VertexBufferObject::CreateVBO(int size)
{
  glGenBuffers(1, &buffer_);
	data_.reserve(size_);
	size_ = size;
	index_ = 0;
}

void VertexBufferObject::BindVBO(int buffer_type)
{
 	bufferType_ = buffer_type;
	glBindBuffer(bufferType_, buffer_);
}

void VertexBufferObject::UploadDataToGPU(int draw_type)
{
	glBufferData(buffer_, data_.size(), &data_[0], draw_type);
	data_.clear();
}

void VertexBufferObject::AddData(void* ptr_data, uint data_size)
{
	data_.insert(data_.end(), (uchar*)ptr_data, (uchar*)ptr_data + data_size);
	index_ += data_size;
}