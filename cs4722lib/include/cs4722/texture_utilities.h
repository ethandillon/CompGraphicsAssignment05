//
// Created by Ben on 11/11/2020.
//

#pragma once

#include <glad/gl.h>
#include <vector>
#include <string>
#include "cs4722/x11.h"

namespace cs4722 {

    /**
     * \brief
     * Create a texture from an image file and assign it to a designated texture unit.
     *
     * The image is loaded from a file and a texture is created from the image data.
     * This function cleans up the temporary data areas used in the process.
     *
     * @param path      Path to the image file
     * @param texture_unit  Texture unit to use for this texture
     * @returns   The texture identifier
     */
    GLuint initTextureFromFile(const char *path, const GLuint texture_unit);

    //GLuint init_textures_from_files(std::vector<std::string> paths, const GLuint start_unit);


    /**
     * \brief create a simple gradient texture.
     *
     * A simple texture is created as a gradient of two colors.
     *
     * @param texture_unit  The texture unit number to use for the texture
     * @param texture_size  Texture size in pixels, default 16
     * @param color1  One color to use in the gradient, default yellow
     * @param color2 Other color to use in the gradient, default blue
     * @returns   The texture identifier
     *
     */
    GLuint initGradientTexture(int texture_unit, int texture_size = 16,
                               cs4722::Color color1 = cs4722::X11::yellow,
                               cs4722::Color color2 = cs4722::X11::blue);

    /**
     * \brief create a simple gradient texture.
     *
     * A simple texture is created as a gradient of two colors.
     *
     * @param textureUnit  The texture unit number to use for the texture
     * @param textureSize  Texture size in pixels, default 16
     * @param color1  One color to use in the gradient, default yellow
     * @param color2 Other color to use in the gradient, default blue
     * @returns   The texture identifier
     *
     */
    GLuint initGradientTexture2(int textureUnit, int textureSize = 16,
                                 cs4722::Color color1 = cs4722::X11::yellow,
                                 cs4722::Color color2 = cs4722::X11::blue);



    /**
    * \brief create a checkerboard texture.
    *
    * A simple texture is created as a checkerboard pattern of gray.
    *
    * @param textureUnit  The texture unit number to use for the texture.
     *          This parameter is required to be provided since it does not have a default value.
    * @param gridSize  The number of squares in each direction in the pattern, default is 8.
    * @param gray0 Specifies the gray level of one set of squares.
     *      This is an integer value in the range from 0 to 255, inclusive.
     *      The default value is 0.
    * @param gray1 Specifies the gray level of one set of squares.
     *      This is an integer value in the range from 0 to 255, inclusive.
     *      The default value is 255.
     * @param textureSize  Specifies the number of pixels in each direction of the created texture.
     *      The default value is 2048.
    *
    */
    void initCheckerboardTexture(unsigned int textureUnit, unsigned int gridSize = 8,
                                     unsigned int gray0 = 0, unsigned int gray1 = 255, unsigned int textureSize = 2048);



    /**
     * \brief Create a cube texture from a list of paths to six image files for the six sides
     * of the cube.
     *
     *
     * @param paths List of six paths to image files
     * @param textureUnit   The texture unit number to use for the cube texture
     * @returns   The texture identifier
     */
    GLuint initCubeTextureFromFileList(std::vector<std::string> &paths, int textureUnit);

    /**
     * \brief Create a cube texture from the files located in the directory indicated by `base_path`.
     *
     * Create a cube texture from the files located in the directory indicated by `base_path`.
     * It is assumed that the files are named posx.*, negx.*, posy.*, ...
     *
     * All the images should be square and all should be the same size.
     * All the file names should be the same image type and have the same extension, either .jpg or .png.
     *
     * The base path should not end with '/' or '\', the separator will be added by the function.
     * The optional extension should not have a period, the separator will be added by the function.
     *
     * @param basePath Path to folder in which the six files are located.
     *          Do not include the trailing / or \ in this value.
     * @param textureUnit Texture unit to use for this texture.
     * @param ext Extension to add to the file name, defaults to png.
     *          Do not include the period in this value.
     * @returns   The texture identifier
     */
    GLuint initCubeTextureFromDirectory(const char* basePath, int textureUnit, const char* ext = "png");


    /**
     * This function must be used immediately after defining a texture.
     * It will always return the size of the last texture defined.
     * @param textureWidth
     * @param textureHeight
     */
    inline void get_texture_size(int &textureWidth, int &textureHeight) {
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);
    }

}