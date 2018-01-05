#include "heightmapHandler.hh"

#include <vector>

HeightmapHandler::HeightmapHandler(Shader shader, std::string path)
    : renderScale_(glm::vec3(1.0f, 1.0f, 1.0f)),
      vbo_(0),
      ebo_(0),
      indices_(std::vector<uint>()),
      data_(std::vector<float>()),
      shader_(shader)
{
    std::cout << "initializing heighmap handler..." << std::endl;
    if (LoadHeightMapFromImage(path) == 1)
        std::cout << "failed to load file" << std::endl;
}

int HeightmapHandler::LoadHeightMapFromImage(std::string image_path)
{
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    FIBITMAP* dib(0);

    fif = FreeImage_GetFileType(image_path.c_str(), 0); // Check the file signature and deduce its format

    if(fif == FIF_UNKNOWN) // If still unknown, try to guess the file format from the file extension
        fif = FreeImage_GetFIFFromFilename(image_path.c_str());

    if(fif == FIF_UNKNOWN) // If still unknown, return failure
        return 1;

    if(FreeImage_FIFSupportsReading(fif)) // Check if the plugin has reading capabilities and load the file
        dib = FreeImage_Load(fif, image_path.c_str());
    if(!dib)
        return 1;

    BYTE* bDataPointer = FreeImage_GetBits(dib); // Retrieve the image data
    rows_ = FreeImage_GetHeight(dib);
    cols_ = FreeImage_GetWidth(dib);
    // We also require our image to be either 24-bit (classic RGB) or 8-bit (luminance)
    if(bDataPointer == NULL || rows_ == 0 || cols_ == 0 || (FreeImage_GetBPP(dib) != 24 && FreeImage_GetBPP(dib) != 8))
        return 1;

    // How much to increase data pointer to get to next pixel data
    uint ptr_inc = FreeImage_GetBPP(dib) == 24 ? 3 : 1;
    // Length of one row in data FIXME
    uint row_step = ptr_inc * cols_;

    std::vector< std::vector< glm::vec3> >
    vertex_data(rows_, std::vector<glm::vec3>(cols_));
    std::vector< std::vector< glm::vec2> >
    coords_data(rows_, std::vector<glm::vec2>(cols_));

    float textureU = static_cast<float>(cols_) * 0.1f;
    float textureV = static_cast<float>(rows_) * 0.1f;
    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
        {
            float scaleC = static_cast<float>(j) / static_cast<float>(cols_ - 1);
            float scaleR = static_cast<float>(i) / static_cast<float>(rows_ - 1);
            float vertex_height = static_cast<float>
                                  (*(bDataPointer + row_step * i + j * ptr_inc)) / 10;
            vertex_data[i][j] = glm::vec3(i,
                                          vertex_height, j);
            data_.push_back(i);
            data_.push_back(vertex_height);
            data_.push_back(j);
            coords_data[i][j] = glm::vec2(textureU * scaleC,
                                          textureV * scaleR);
        }

    // Normals are here - the heightmap contains ( (iRows-1)*(iCols-1) quads, each one containing 2 triangles, therefore array of we have 3D array)
    std::vector< std::vector<glm::vec3> > normals[2];
    for(uint i = 0; i < 2; ++i)
        normals[i] = std::vector< std::vector<glm::vec3> >(rows_- 1,
                     std::vector<glm::vec3>(cols_ - 1));

    for(uint i = 0; i < rows_ - 1; ++i)
        for(uint j = 0; j < cols_ - 1; ++j)
        {
            glm::vec3 triangle0[] =
            {
                vertex_data[i][j],
                vertex_data[i+1][j],
                vertex_data[i+1][j+1]
            };
            glm::vec3 triangle1[] =
            {
                vertex_data[i+1][j+1],
                vertex_data[i][j+1],
                vertex_data[i][j]
            };

            glm::vec3 triangleNorm0 = glm::cross(triangle0[0] - triangle0[1],
                                                 triangle0[1] - triangle0[2]);
            glm::vec3 triangleNorm1 = glm::cross(triangle1[0]-triangle1[1],
                                                 triangle1[1] - triangle1[2]);

            normals[0][i][j] = glm::normalize(triangleNorm0);
            normals[1][i][j] = glm::normalize(triangleNorm1);
        }

    std::vector< std::vector<glm::vec3> > final_normals =
        std::vector< std::vector<glm::vec3> >(rows_, std::vector<glm::vec3>(cols_));
    for (uint i = 0; i < rows_; ++i)
        for(uint j = 0; j < cols_; ++j )
        {
            // Now we wanna calculate final normal for [i][j] vertex. We will have a look at all triangles this vertex is part of, and then we will make average vector
            // of all adjacent triangles' normals

            glm::vec3 final_normal = glm::vec3(0.0f, 0.0f, 0.0f);

            // Look for upper-left triangles
            if (j != 0 && i != 0)
                for(uint k; k < 2; ++k)
                    final_normal += normals[k][i-1][j-1];
            // Look for upper-right triangles
            if(i != 0 && j != cols_ - 1)
                final_normal += normals[0][i-1][j];
            // Look for bottom-right triangles
            if (i != rows_ - 1 && j != cols_ - 1)
                for(uint k = 0; k < 2; ++k)
                    final_normal += normals[k][i][j];
            // Look for bottom-left triangles
            if (i != rows_ - 1 && j != 0)
                final_normal += normals[1][i][j-1];

            final_normal = glm::normalize(final_normal);

            final_normals[i][j] = final_normal; // Store final normal of j-th vertex in i-th row
        }



    /*vbo_.CreateVBO(rows_ * cols_ *
                   (2 * sizeof (glm::vec3) + sizeof (glm::vec2)));
    for(uint i = 0; i < rows_; ++i)
    {
        for (uint j = 0; j < cols_; ++j)
        {
            vbo_.AddData(&vertex_data[i][j], sizeof (glm::vec3)); // Add vertex
            vbo_.AddData(&coords_data[i][j], sizeof (glm::vec2)); // Add tex. coord
            vbo_.AddData(&final_normals[i][j], sizeof (glm::vec3)); // Add normal
        }
    }
    */
    /*
    for (uint i = 0; i < rows_; ++i)
    {
        for (uint j = 0; j < cols_; ++j)
            data_.push_back(vertex_data[i][j]);
    }*/

    initIndices(rows_);
    glGenVertexArrays(1, &vao_);

    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);


    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, data_.size() * sizeof(float), &data_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(uint), &indices_[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (float), 0);
    glEnableVertexAttribArray(0);
    /*glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
                          2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)sizeof(glm::vec3));
    // Normal vectors
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
                          2 * sizeof(glm::vec3) + sizeof(glm::vec2), (void*)(sizeof(glm::vec3)+sizeof(glm::vec2)));
    */


    // Vertex positions
    //glEnableVertexAttribArray(0);
    //ebo_.BindVBO(GL_ELEMENT_ARRAY_BUFFER);
    //ebo_.UploadDataToGPU(GL_STATIC_DRAW);
    std::cout << "heightmap initialized" << std::endl;
    return 0;
}

void HeightmapHandler::RenderHeightmap(glm::mat4 projection_mat,
                                       glm::mat4 view_mat)
{
    shader_.use();

    shader_.setMat4("projection", projection_mat);
    shader_.setMat4("view", view_mat);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f));
    shader_.setMat4("model", model);
    /*
    shader_.setFloat("fRenderHeight", renderScale_.y);
    shader_.setFloat("fMaxTextureU", float(cols_) * 0.1f);
    shader_.setFloat("fMaxTextureV", float(rows_) * 0.1f);

    shader_.setMat4("HeightmapScaleMatrix", glm::scale(glm::mat4(1.0), glm::vec3(renderScale_)));
    */
    // Now we're ready to render - we are drawing set of triangle strips using one call, but we g otta enable primitive restart
    glBindVertexArray(vao_);
    //glEnable(GL_PRIMITIVE_RESTART);
    //glPrimitiveRestartIndex(rows_ * cols_);

    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, 0);
}

void HeightmapHandler::initIndices(int size)
{
    for (int z = 0; z < size - 1; ++z)
    {
        for (int x = 0; x < size - 1; ++x)
        {
            int start = x + z * size;
            indices_.push_back(start);
            indices_.push_back(start + 1);
            indices_.push_back(start + size);
            indices_.push_back(start + 1);
            indices_.push_back(start + 1 + size);
            indices_.push_back(start + size);
        }
    }
}
