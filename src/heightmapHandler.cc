#include "heightmapHandler.hh"

#include <vector>

HeightmapHandler::HeightmapHandler()
    : renderScale_(glm::vec3(1.0f, 1.0f, 1.0f))
{}

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
    // Length of one row in data
    uint row_step = ptr_inc * cols_;

    glGenBuffers(1, &heightmapDatavbo_);

    std::vector< std::vector< glm::vec3> >
    vertex_data(rows_, std::vector<glm::vec3>(cols_));
    std::vector< std::vector< glm::vec2> >
    coords_data(rows_, std::vector<glm::vec2>(cols_));

    float textureU = float(cols_) * 0.1f;
    float textureV = float(rows_) * 0.1f;

    for (uint i = 0; i < rows_; ++i)
        for (uint j = 0; j < cols_; ++j)
        {
            float scaleC = static_cast<float>(j) / static_cast<float>(cols_ - 1);
			      float scaleR = static_cast<float>(i) / static_cast<float>(rows_ - 1);
			      float vertex_height = static_cast<float>
			      (*(bDataPointer + row_step * i + j * ptr_inc)) / 255.0f;
            vertex_data[i][j] = glm::vec3(-0.5f + scaleC,
             vertex_height, -0.5f + scaleR);
            coords_data[i][j] = glm::vec2(textureU * scaleC, 
            textureV * scaleR);
        }

    return 0;
}

